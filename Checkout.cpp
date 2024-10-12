#include <TXLib.h>
#include <stdio.h>
#include <assert.h>

#include "Checkout.h"
#include "Stack.h"

void StackAssertFunc(struct Stack_t *ad_stack, const char* filename /*, const char* file, int line*/)         //фигово написано
{
    StackErr_t err = StackError(ad_stack);

    if (err != STACK_NULL) {
        ad_stack->status = err;
    }

    STACK_DUMP(ad_stack, filename);

    if (err != STACK_NO_ERROR)
    {          
        assert(0);
    }
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

    return STACK_NO_ERROR;
}

/*
StackErr_t StackDump(struct Stack_t *ad_stack, const char* filename, const char* file, int line)         //фигово написано
{
    FILE* fileptr = fopen(filename, "wb");

    fprintf(fileptr, "called from %s : %d \n"
                     "address stack = %p \n", file, line, ad_stack);

    if (ad_stack == NULL) {
        fprintf(fileptr, "Null poiter of data \n");
        fclose(fileptr);
        return STACK_NULL;
    }

    fprintf(fileptr, "error: %d\n"
                     "address data = %p \n"
                     "stack size = %d \n"
                     "stack capacity = %d \n \n \n", ad_stack->status, ad_stack->data,      \
                                                     ad_stack->size, ad_stack->capacity);

    fclose(fileptr);

    return STACK_NO_ERROR;
}
*/



StackErr_t StackDump(struct Stack_t *ad_stack, const char* filename, const char* file, int line)         //фигово написано
{
    FILE* fileptr = fopen(filename, "wb");

    if (ad_stack == NULL) {
        fprintf(fileptr, "Null poiter of data \n"
                         "called from %s : %d \n"
                         "address stack = %p \n", file, line, ad_stack);
        fclose(fileptr);
        return STACK_NULL;
    }

    fprintf(fileptr, "Stack_t [0x%p] \n"
                     "  called from %s : %d \n"
                     ON_DEBUG("  name %s born at %s : %d \n")
                     "  { \n"
                     "      THE LEFT_CANARY_OF_THE_STACK_EQUALS  = %llu \n"
                     "      THE RIGHT_CANARY_OF_THE_STACK_EQUALS = %llu \n"
                     "      capacity = %d \n"
                     "      size = %d \n"
                     "      data[0x%p] \n"
                     "      THE LEFT_CANARY_OF_THE_DATA_EQUALS  = %llu \n"
                     "      THE RIGHT_CANARY_OF_THE_DATA_EQUALS = %llu \n"
                     "      { \n", ad_stack, file, line, ON_DEBUG(ad_stack->name, ad_stack->file, ad_stack->line,) \
                                   ad_stack->c1, ad_stack->c2, ad_stack->capacity, ad_stack->size, \
                                   ad_stack->data, *(ad_stack->data - 1), *(ad_stack->data + ad_stack->capacity));
    
    for (int i = 0; i < ad_stack->capacity; i ++) 
    {
        if (ad_stack->data[i] != POIZON_VALUE_FOR_DATA) 
            fprintf(fileptr, "          *[i] = %g \n", ad_stack->data[i]);
        else
            fprintf(fileptr, "           [i] = %g (POISON) \n", ad_stack->data[i]);
    }

    fprintf(fileptr, "      } \n"
                     "  } \n \n \n");

    fclose(fileptr);

    return STACK_NO_ERROR;
}


