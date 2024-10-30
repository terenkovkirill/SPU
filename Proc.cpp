#include <TXLib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Stack.h"
#include "Checkout.h"
#include "Enum.h"
#include "Proc.h"
#include "Read.h"


int main(int argc, const char* argv[])  //файлы для считывания и записи в dump
{
    if (argc != 3) {
        printf("Erroneous number of elements");
        return 0 ;
    }

    struct FileData proc = ReadingFile(argv[1]);

    Processor(argv[2], &proc);

    return 0;
}


void Processor(const char* log_file, struct FileData *proc)   //в чём отличие записи в аргументах code[]  и code
{
    Stack_t stk = {};

    StackCtor(&stk, 2, log_file);

    int ip = 0;     //продвинутая версия

    while(ip < proc->count_commands)     
    {  
        switch ((int)proc->dinamic_text[ip]) {                 //в чём отличие case с фигурными скобками и без них
            case PUSH: {
                StackPush(&stk, (int)proc->dinamic_text[ip + 1]);
                ip += 1;
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
                printf("SNTXERR: %d \n", (int)proc->dinamic_text[ip]);
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
        printf("%d ", ad_stack->data[i]);
    }
    printf("\n");
}
