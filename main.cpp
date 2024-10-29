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
        return 0 ;
    }

    //нужна запись в массиви передача указателя на маааив в SPU
    //нужен подсчёт длины массива

    SPU(argv[1], argv[2]);
    return 0;
}

void SPU(const char* readfile, const char* logfile /*int code[], len_arr*/)   //в чём отличие записи в аргументах code[]  и code
{
    Stack_t stk = {};

    StackCtor(&stk, 2, logfile);

    FILE* read_file = fopen(readfile, "r");

    int ip = 0;     //продвинутая версия

    while(ip < )     
    {
        int command = 0;
        fscanf(read_file, "%d \n", &command);


        switch (code[ip]) {                 //в чём отличие case с фигурными скобками и без них
            case PUSH: {
                StackPush(&stk, code[ip + 1]);
                ip += 2;
                break;
            }

            case SUB: {
                StackElem_t value1, value2;
                StackPop(&stk, &value1);
                StackPop(&stk, &value2);
                StackPush(&stk, value1 - value2);
                ip += 1;
                break;
            }

            case ADD: {
                StackElem_t value1, value2;
                StackPop(&stk, &value1);
                StackPop(&stk, &value2);
                StackPush(&stk, value1 + value2);
                ip += 1;
                break;
            }
            
            case MUL: {
                StackElem_t value1, value2;
                StackPop(&stk, &value1);
                StackPop(&stk, &value2);
                StackPush(&stk, value1 * value2);
                ip += 1;
                break;
            }

            case OUTPUT: {
                StackElem_t value = 0;
                StackPop(&stk, &value);
                printf("%d", value);
                ip += 1;
                break;
            }
            
            case HLT:
                break;

            default: 
                printf("SNTXERR: %d \n", code[ip]);
                break;      
        }
    }

    /*
    while(1)
    {
        int command = 0;
        fscanf(read_file, "%d \n", &command);

        switch (command) {
            case PUSH: {
                StackElem_t arg = 0;
                fscanf(read_file, "%d", &arg);
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
                printf("%d", value);
            }
            
            case HLT:
                break;

            default: 
                printf("SNTXERR: %d \n", command);
                break;      
        }
    }
    */

    PrintStack(&stk);
}


void PrintStack(struct Stack_t *ad_stack)
{
    assert(ad_stack != NULL);
    for (int i  = 0; i < ad_stack->size; i++)
    {
        printf("%d ", ad_stack->data[i]);
    }
    printf("\n");
}

