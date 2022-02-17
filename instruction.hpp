#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <stdint.h>
#include <string.h>

enum Command {
    label   = 0,
    jump    = 1,
    led     = 2, 
    button  = 3,
    wait    = 4,
    print   = 5
};

class Instruction {
    public:
        Instruction();
        ~Instruction();
        Command getCommand();
    protected:
        Command eCommand_;

};

class VoidInstruction : public Instruction {
    public:
        VoidInstruction(Command eCommand);
        ~VoidInstruction();
};

class ByteInstruction : public Instruction {
    public:
        ByteInstruction(Command eCommand, uint8_t num);
        ~ByteInstruction();

        uint8_t nArg_;
};

class WordInstruction : public Instruction {
    public:
        WordInstruction(Command eCommand, uint16_t num);
        ~WordInstruction();

        uint16_t nArg_;
};

class StringInstruction : public Instruction {
    public:
        StringInstruction(Command eCommand, char *str);
        ~StringInstruction();

        char *sArg_;
};

#endif // __INSTRUCTION_H__