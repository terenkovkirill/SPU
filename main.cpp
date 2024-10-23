#include <TXLib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Stack.h"
#include "Checkout.h"
#include "Enum.h"

void SPU(const char* readfile, const char* log_file);

int main(int argc, const char* argv[])  //файлы для считывания и записи в dump
{
    if (argc != 3) {
        printf("Erroneous number of elements");
    }

    SPU(argv[1], argv[2]);
    return 0;
}

void SPU(const char* readfile, const char* logfile)   //ПЕреименовать функцию
{
    Stack_t stk = {};

    StackCtor(&stk, 2, logfile);

    FILE* read_file = fopen(readfile, "r");

    while(1)
    {
        int command = 0;
        fscanf(read_file, "%c \n", &command);

        switch (command) {
            case PUSH: {
                StackElem_t arg = 0;
                fscanf(read_file, "%c", &arg);
                StackPush(&stk, arg);
                break;
        
            }

            case SUB: {
                StackElem_t value1, value2;
                StackPop(&stk, &value1);
                StackPop(&stk, &value2);
                StackPush(&stk, value1 - value2);
                break;
            }

            case ADD: {
                StackElem_t value1, value2;
                StackPop(&stk, &value1);
                StackPop(&stk, &value2);
                StackPush(&stk, value1 + value2);
                break;
            }
            
            case MUL: {
                 StackElem_t value1, value2;
                StackPop(&stk, &value1);
                StackPop(&stk, &value2);
                StackPush(&stk, value1 * value2);
                break;
            }

            case OUTPUT: {
                StackElem_t value = 0;
                StackPop(&stk, &value);
                printf("%u", value);
            }
            
            case HLT:
                break;

            default: 
                printf("SNTXERR: %с \n", command);
                break;      
        }

        PrintStack(&stk);
    }
}


void PrintStack(struct Stack_t *ad_stack)
{
    assert(ad_stack != NULL);
    for (int i  = 0; i < ad_stack->size; i++)
    {
        printf("%u ", ad_stack->data[i]);
    }
    printf("\n");
}
