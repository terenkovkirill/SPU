#ifndef PROC_H
#define PROC_H

#include <TXLib.h>
#include <stdio.h>
#include "Enum.h"
#include "Stack.h"

const int NUM_REGS = 3;

struct Processors
{
    int* code;
    int regs[NUM_REGS];
    int ip;
    Stack_t* stk;               //TODO: Stack_t stk;
};



#define CONVERS(opcode) (opcode & OPCODE_MSK) 

void Processor(struct Processors *proc);
void PrintStack(struct Stack_t *ad_stack);
int* GetArgPop(struct Processors *proc);
int GetArgPush(struct Processors *proc);

#endif