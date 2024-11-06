#ifndef ENUM_H
#define ENUM_H

enum Command {
    PUSH = 1,
    ADD = 2,
    SUB = 3,                //subtraction = вычитание
    DIV = 4,                //division = деление
    OUTPUT = 5,
    MUL = 7,                //multiplication = умножение
    POP = 10,
    JMP = 11,
    JA = 12,
    JB = 13,
    JE = 14,
    JAE = 15,
    JBE = 16,
    JNE = 17,
    HLT = 0                 //halt = остановка
};

enum RegTypes {
    AX = 0, 
    BX = 1
};

enum PushPopTypes {
    STACK_ARG = 0b00000001,
    REG_ARG   = 0b00000010,
    SUM_ARG   = 0b00000100,
    RAM_ARG   = 0b00001000
};

// enum CommandTypeMasks {
//     REG_ARG = 0b00100000,
//     DATA_ARG = 0b01000000,
//     SUM_ARG = 0b10000000,
//     ARG_TYPE_MSK =0b11100000,
//     OPCODE_MSK = 0b00011111
// };

enum LabelNames {
    FIRST = 5000,
    SECOND = 5100,
    THIRD = 5200,
    FOURTH = 5300,
    FIFTH = 5400
};



#endif