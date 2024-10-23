#ifndef STACK_H
#define STACK_H

#include <TXLib.h>

//#define DEBUG
#define NO_ITEMS 0
#define FILENAME 
typedef uint8_t StackElem_t;
typedef uint64_t Canary_t;


#ifdef DEBUG                                                    
    #define ON_DEBUG(...) __VA_ARGS__
#else
    #define ON_DEBUG(...)
#endif    

#ifdef DEBUG
    #define STACK_CTOR(ad_stack, capacity, dmp_file) {\
            StackCtor(ad_stack, capacity, dmp_file, #ad_stack, __FILE__, __LINE__);\
    }
#else
    #define STACK_CTOR(ad_stack, capacity, dump_file) {\
        StackCtor(ad_stack, capacity, dump_file);\
    }
#endif

#define STACK_ASSERT(ad_stack) \
        StackAssertFunc(ad_stack /*, __FILE__, __LINE__*/)


const StackElem_t POISON_VALUE_FOR_DATA = (StackElem_t)0xDEDEDEDBAD;            //что опроисходит с 16ричным числом ?
const int POISON_VALUE_FOR_SIZE = (int)0xBADCAFE;
const int POISON_VALUE_FOR_CAPACITY = (int)0xFEEDDEDBAD;
const Canary_t STACK_CANARY = (Canary_t)0xBADEDA;
const Canary_t DATA_CANARY = (Canary_t)0xBEDADEDA;


struct Stack_t
{
    Canary_t c1;      

    StackElem_t* data;
    int size;
    int capacity;
    int status;
    FILE* dump_file;
    ON_DEBUG(const char* name;)
    ON_DEBUG(const char* file;)
    ON_DEBUG(int line;)

    Canary_t c2;     
};


void StackCtor(struct Stack_t *ad_stack, int capacity, const char* dmp_file ON_DEBUG(, const char* name, const char* file, int line));
void StackRealloc(struct Stack_t *ad_stack);
void FillPoisonValue(struct Stack_t *ad_stack);
void StackPush(struct Stack_t *ad_stack, StackElem_t elem);
void StackPop(struct Stack_t *ad_stack, StackElem_t* x);
void StackDestructor(struct Stack_t *ad_stack);
void PrintStack(struct Stack_t *ad_stack);
void StackAssertFunc(struct Stack_t *ad_stack /*, const char* file, int line*/);

#endif