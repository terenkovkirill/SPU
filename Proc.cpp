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
    
    struct SPU proc = CreatCodeArray(argv[1]);

    Stack_t proc_stk = {};

    proc.stk = &proc_stk;                       //правильная ли это инициализация структуры
    StackCtor(proc.stk, 2, argv[2]);

    proc.ip = 0; 

    Processor(&proc); 
    
    for (int i = 0; i < 13; i++) {
        printf("code[%d] = %d \n", i, proc.code[i]);
    }
    
    return 0;
}


void Processor(struct SPU *proc)  
{
    while(proc->code[proc->ip] != HLT)     
    {
        printf("case: %d \n", proc->code[proc->ip]);

        switch (proc->code[proc->ip]) {                 //в чём отличие case с фигурными скобками и без них  !
            case PUSH: {
                StackPush(proc->stk, GetArgPush(proc));
                break;
            }

            case POP: {
                StackElem_t* addr = GetArgPop(proc);
                StackPop(proc->stk, addr);
                break;
            }

            case SUB: {
                StackElem_t value1, value2;
                StackPop(proc->stk, &value1);
                StackPop(proc->stk, &value2);
                StackPush(proc->stk, value2 - value1);
                proc->ip += 1;
                break;
            }

            case ADD: {
                StackElem_t value1, value2;
                StackPop(proc->stk, &value1);
                StackPop(proc->stk, &value2);
                printf("--ADD: value1 = %d, value2 = %d, value1 + value2 = %d \n", value1, value2, value1 + value2);
                StackPush(proc->stk, value1 + value2);
                proc->ip += 1;
                break;
            }
            
            case MUL: {
                StackElem_t value1, value2;
                StackPop(proc->stk, &value1);
                StackPop(proc->stk, &value2);
                StackPush(proc->stk, value1 * value2);
                printf("--MUL: value1 = %d, value2 = %d, value1 * value2 = %d \n", value1, value2, value1 * value2);
                proc->ip += 1;
                break;
            }

            case DIV: {
                StackElem_t value1, value2;
                StackPop(proc->stk, &value1);
                StackPop(proc->stk, &value2);
                StackPush(proc->stk, value2 / value1);
                printf("--DIV: value1 = %d, value2 = %d, value1 / value2 = %d \n", value1, value2, value1 / value2);
                proc->ip += 1;
                break;
            } 

            case OUTPUT: {
                StackElem_t value = 0;
                StackPop(proc->stk, &value);
                printf("--OUTPUT: %d \n", value);
                proc->ip += 1;
                break;
            }                      
            
            case HLT:
                break;

            default: 
                printf("SNTXERR: %d \n", proc->code[proc->ip++]);
                break;      
        }

        PrintStack(proc->stk);
    }


    printf("\n \n");
}

int GetArgPush(struct SPU *proc)
{
    proc->ip++;         //int opCode = proc->code[proc->ip++];
    int argType = proc->code[proc->ip++]; 

    if (argType & STACK_ARG)                                    ///Побитовое умножение исключительно для скорости
        return proc->code[proc->ip++];                           
    
    if (argType & REG_ARG)
        return proc->regs[proc->code[proc->ip++]];
    
    // if (cmd & SUM_ARG)
    //     return proc->regs[proc->code[proc->ip++]] + proc->code[proc->ip++];

    // if (argType & 4)
    //     result = RAM[result];

    return 1;                   //это надо поправить
}

int* GetArgPop(struct SPU *proc)
{
    proc->ip++;     //int opCode = proc->code[proc->ip++];
    int argType = proc->code[proc->ip++]; 

    if (argType & REG_ARG)                                      //берёт число из стека и записывает его в регистр
        return &(proc->regs[proc->code[proc->ip++]]);           //возврает адрес ячейки в массиве регистров

    // if (cmd & DATA_ARG)
    //     return куда-то в RAM;

    return &(proc->regs[proc->code[proc->ip++]]);           //это надо поправить
}



void PrintStack(struct Stack_t *ad_stack)
{
    assert(ad_stack != NULL);
    for (int i  = 0; i < ad_stack->size; i++)
    {
        printf("%d \n", ad_stack->data[i]);
    }
    printf("\n");
}



/*

in
pushr bx  ; stack: bx
push -1 ; stack: bx, -1
mul     ; stack: -bx
in
pushr ax  ; stack: - bx, ax
div     ; stack: 
out     ; stack: 
hlt


TODO:
1 Pushr ax, push bx  в процессоре и асме
2 Написать pop (выпопливает ax из массива регисторов)
3 Написать jump
4 Написать прогу, считающую сумму квадратов от 1 до 3.
*/




/*
То, что хочу обсудить:
    считывание в файл 
    /r /n
    режимы открытия файлов w , wb
*/