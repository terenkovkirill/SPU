#ifndef CHECKOUT_H
#define CHECKOUT_H
#include <TXLib.h>
#include "Stack.h"

#define STACK_DUMP(ad_stack)  \
        StackDump(ad_stack, __FILE__, __LINE__)

enum StackErr_t {
    STACK_NO_ERROR = 0,
    STACK_NULL = 1,
    STACK_DATA_NULL = 2,
    STACK_SIZE_LESS_THAN_ZERO = 3,
    STACK_SIZE_MORE_THAN_CAPACITY = 4,
    LEFT_DATA_CANARY_BROKE = 5,
    RIGHT_DATA_CANARY_BROKE = 6,
    LEFT_STACK_CANARY_BROKE = 7,
    RIGHT_STACK_CANARY_BROKE = 8,
};


StackErr_t StackError(struct Stack_t *ad_stack);
StackErr_t StackDump(struct Stack_t *ad_stack, const char* file, int line);

#endif