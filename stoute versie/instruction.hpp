#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <stdint.h>
#include <string.h>

enum Command {
    label,
    jump,
    led, 
    button,
    wait,
    print
};

struct AbstractInstruction{
    virtual ~AbstractInstruction() = 0;
    Command eCommand_;
};

template <class T>
class Instruction : public AbstractInstruction {
    public:
        Instruction(Command eCommand, T arg);
        ~Instruction();
        T getArgument();
        void setArgument(T arg);
    private:
        T arg_;
};

// class VoidInstruction : public Instruction {
//     public:
//         VoidInstruction(Command eCommand);
//         ~VoidInstruction();

//     private:
// };

// class ByteInstruction : public Instruction {
//     public:
//         ByteInstruction(Command eCommand, uint8_t num);
//         ~ByteInstruction();

//     private:
//         uint8_t nArg_;
// };

// class WordInstruction : public Instruction {
//     public:
//         WordInstruction(Command eCommand, uint16_t num);
//         ~WordInstruction();

//     private:
//         uint16_t nArg_;
// };

// class StringInstruction : public Instruction {
//     public:
//         StringInstruction(Command eCommand, char *str);
//         ~StringInstruction();

//     private:
//         char *sArg_;
// };

#endif // __INSTRUCTION_H__