#include <TXLib.h>
#include <stdio.h>
#include <assert.h>

#include "Checkout.h"
#include "Stack.h"

void StackAssertFunc(struct Stack_t *ad_stack /*, const char* file, int line*/)         //фигово написано
{
    StackErr_t err = StackError(ad_stack);

    if (err != STACK_NULL) {
        ad_stack->status = err;
    }

    STACK_DUMP(ad_stack);
    /*
    if (err != STACK_NO_ERROR)
    {          
        assert(0);
    }
    */
}


StackErr_t StackError(struct Stack_t *ad_stack) 
{
    if (!ad_stack)
    {
        return STACK_NULL;
    }
    
    if (!ad_stack->data)
    {
        return STACK_DATA_NULL;
    }

    if (ad_stack->size < 0)
    {
        return STACK_SIZE_LESS_THAN_ZERO;
    }

    if (ad_stack->size > ad_stack->capacity)
    {
        return STACK_SIZE_MORE_THAN_CAPACITY;
    }

    if (*((Canary_t *)ad_stack->data - 1) != DATA_CANARY)
    {
        return LEFT_DATA_CANARY_BROKE;
    }

    if (*(Canary_t *)(ad_stack->data + ad_stack->capacity) != DATA_CANARY)
    {
        return RIGHT_DATA_CANARY_BROKE;
    }

    if (ad_stack->c1 != STACK_CANARY)
    {
        return LEFT_STACK_CANARY_BROKE;
    }

    if (ad_stack->c2 != STACK_CANARY)
    {
        return RIGHT_STACK_CANARY_BROKE;
    }

    return STACK_NO_ERROR;
}


StackErr_t StackDump(struct Stack_t *ad_stack, const char* file, int line)         //фигово написано
{
    if (ad_stack == NULL) 
    {
        printf("Null poiter of stack \n"
               "called from %s : %d \n"
               "address stack = %p \n", file, line, ad_stack);
        return STACK_NULL;
    }
    
    if (ad_stack->data == NULL) 
    {
        printf("Null poiter of data \n"
               "called from %s : %d \n"
               "address stack = %p \n", file, line, ad_stack);
        return STACK_DATA_NULL;
    }

    fprintf(
        ad_stack->dump_file,
        "Stack_t [0x%p] \n"
        "  caed from %s : %d \n"
        ON_DEBUG("  name %s born at %s : %d \n")
        "  { \n"
        "      THE LEFT_CANARY_OF_THE_STACK_EQUALS  = %I64d \n"
        "      THE RIGHT_CANARY_OF_THE_STACK_EQUALS = %I64d \n"
        "      capacity = %d \n"
        "      size = %d \n"
        "      data[0x%p] \n"
        "      THE LEFT_CANARY_OF_THE_DATA_EQUALS  = %I64d \n"
        "      THE RIGHT_CANARY_OF_THE_DATA_EQUALS = %I64d \n"
        "      { \n",
        ad_stack, file, line,
        ON_DEBUG(ad_stack->name, ad_stack->file, ad_stack->line,)
        ad_stack->c1, ad_stack->c2, ad_stack->capacity, ad_stack->size,
        ad_stack->data, *((Canary_t *)ad_stack->data - 1), *(Canary_t *)(ad_stack->data + ad_stack->capacity)
    );
    

    for (int i = 0; i < ad_stack->capacity; i ++) 
    {
        if (ad_stack->data[i] != POISON_VALUE_FOR_DATA) 
            fprintf(ad_stack->dump_file, "          *[i] = %u \n", ad_stack->data[i]);
        else
            fprintf(ad_stack->dump_file, "           [i] = %u (POISON) \n", ad_stack->data[i]);
    }

    fprintf(ad_stack->dump_file, "      } \n"
                     "  } \n \n \n");

    return STACK_NO_ERROR;
}
