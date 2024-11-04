#ifndef ENUM_H
#define ENUM_H

enum Command {
    PUSH = 1,
    ADD = 2,
    SUB = 3,
    DIV = 4,
    OUTPUT = 5,
    MUL = 7,
    JB = 9,
    POP_AX = 10,
    PUSH_AX = 11,
    PUSH_BX =12,
    POP_BX = 13,
    POP = 14,
    HLT = 0
};

enum RegTypes {
    AX = 0, 
    BX = 1
};

enum CommandTypeMasks {
    REG_ARG = 0b00100000,
    DATA_ARG = 0b01000000,
    SUM_ARG = 0b10000000,
    ARG_TYPE_MSK =0b11100000,
    OPCODE_MSK = 0b00011111
};

enum LabelNames {
    FIRST = 5000,
    SECOND = 5100,
    THIRD = 5200,
    FOURTH = 5300,
    FIFTH = 5400
};



#endif