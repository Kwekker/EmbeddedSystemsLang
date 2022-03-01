#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <stdint.h>
#include "parser.hpp"
#define COMMAND_MAX_NAME 10

class Instruction {
public:
    Instruction(const char *name, uint8_t *(*funcPtr)(uint8_t *), uint8_t *(*compileFunc)(Parser, uint8_t *, uint8_t));
    ~Instruction();
    uint8_t *(*run)(uint8_t *);
    uint8_t *compile(Parser parser, uint8_t *compiled);
    char *getName();

    static uint8_t getId();

private:
    uint8_t *(*compileFunc)(Parser, uint8_t *, uint8_t);
    static uint8_t nInstructionCount_;
    char sName_[COMMAND_MAX_NAME];
    uint8_t nId_;
};

#endif // __INSTRUCTION_H__