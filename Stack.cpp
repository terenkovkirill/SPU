#include <TXLib.h>
#include <assert.h>

#include "Stack.h"
#include "Checkout.h"   
/*
#define DBG
#ifdef DBG
    #define if (1)
#else
    #define if (0)
#endif 
*/    

void StackCtor(struct Stack_t *ad_stack, int capacity, const char* dmp_file ON_DEBUG(, const char* name, const char* file, int line))
{
    assert(ad_stack != NULL);       //убираю assert 
    ad_stack->size = 0;
    ad_stack->capacity = capacity;

    FILE* dump_file = fopen(dmp_file, "wb");

    ad_stack->dump_file = dump_file;
    ad_stack->c1 = STACK_CANARY;
    ad_stack->c2 = STACK_CANARY;
    
    int balance_for_align = 8 - (capacity * sizeof(StackElem_t)) % 8;
    Canary_t* ad_c1 = (Canary_t *)calloc(1, capacity * sizeof(StackElem_t) + 2 * sizeof(Canary_t) +  balance_for_align);
    //DBG printf("--%p\n", ad_c1);
    *ad_c1 = DATA_CANARY;
    //printf("%I64d data canary first fime \n", *ad_c1);

    ad_stack->data = (StackElem_t *)((char*)ad_c1 + sizeof(Canary_t));

    FillPoisonValue(ad_stack);

    Canary_t* ad_c2 = (Canary_t *)((char*)ad_stack->data + capacity * sizeof(StackElem_t) + balance_for_align);
    *ad_c2 = DATA_CANARY;
    //printf("%I64d data canary first time \n", *ad_c2);

    ad_stack->status = STACK_NO_ERROR;

    ON_DEBUG(ad_stack->name = name;) 
    ON_DEBUG(ad_stack->file = file;)                                          
    ON_DEBUG(ad_stack->line = line;)
    STACK_ASSERT(ad_stack);                                             
}


void StackPush(struct Stack_t *ad_stack, StackElem_t elem)
{
    STACK_ASSERT(ad_stack);

    if (ad_stack->size == ad_stack->capacity)
    {
        StackRealloc(ad_stack);
    }
    
    ad_stack->data[ad_stack->size] = elem;
    ad_stack->size++;

    STACK_ASSERT(ad_stack);           
}


void StackPop(struct Stack_t *ad_stack, StackElem_t* x)
{
    STACK_ASSERT(ad_stack);
    
    *x = ad_stack->data[ad_stack->size-1];
    ad_stack->size--;
    
    STACK_ASSERT(ad_stack);
}


void StackRealloc(struct Stack_t *ad_stack)
{
    STACK_ASSERT(ad_stack);
    
    ad_stack->capacity  = 2 * ad_stack->capacity;
    
    int balance_for_align = 8 - (ad_stack->capacity * sizeof(StackElem_t)) % 8;
    size_t realloc_memory = ad_stack->capacity * sizeof(StackElem_t) + 2 * sizeof(Canary_t) +  balance_for_align;

    //printf("%p %lu\n", ad_stack->data, realloc_memory);
    Canary_t* ad_c1 = (Canary_t *)realloc((char*)ad_stack->data - sizeof(Canary_t), realloc_memory);
    //printf("%p %p %lu\n", ad_c1, ad_stack->data, realloc_memory);    
    *ad_c1 = DATA_CANARY;   
    
    ad_stack->data = (StackElem_t *)((char*)ad_c1 + sizeof(Canary_t));

    FillPoisonValue(ad_stack);

    Canary_t* ad_c2 = (Canary_t *)((char*)ad_stack->data + ad_stack->capacity * sizeof(StackElem_t) + balance_for_align);
    *ad_c2 = DATA_CANARY;

    STACK_ASSERT(ad_stack);             
}

void FillPoisonValue(struct Stack_t *ad_stack)
{
    for (int i = ad_stack->size; i < ad_stack->capacity; i++) {
        ad_stack->data[i] = POISON_VALUE_FOR_DATA;
    }
}


void StackDestructor(struct Stack_t *ad_stack)
{
    assert(ad_stack != NULL);
    free(ad_stack->data);
    ad_stack->size = POISON_VALUE_FOR_SIZE;
    ad_stack->capacity = POISON_VALUE_FOR_CAPACITY;

    fclose(ad_stack->dump_file);
    ad_stack->dump_file = NULL;
}
