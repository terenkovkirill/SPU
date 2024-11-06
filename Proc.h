#ifndef PROC_H
#define PROC_H

#include <TXLib.h>
#include <stdio.h>
#include "Enum.h"
#include "Stack.h"

const int NUM_REGS = 3;

struct SPU
{
    int* code;
    int regs[NUM_REGS];
    int ip;
    Stack_t stk;               
};


#ifdef DEBUG
    #define DBG        if(1)                //что это значит  !
    #define dbg(...) __VA_ARGS__
#else
    #define DBG        if(0)
    #define dbg(...)
#endif


//#define CONVERS(opcode) (opcode & OPCODE_MSK) 

void Processor(struct SPU *proc);
void PrintStack(struct Stack_t *ad_stack);
int* GetArgPop(struct SPU *proc);
int GetArgPush(struct SPU *proc);

#endif