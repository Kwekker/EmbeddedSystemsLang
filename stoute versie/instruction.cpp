#include "instruction.hpp"


template<class T>
Instruction<T>::Instruction(Command eCommand, T arg) {
    eCommand_ = eCommand;
    arg_ = arg;
}

template<class T>
Instruction<T>::~Instruction() {
    
}

template<class T>
T Instruction<T>::getArgument() {
    return arg_;
}

template<class T>
void Instruction<T>::setArgument(T arg) {
    arg_ = arg;
}


// Instruction::~Instruction() {
    
// }

// Command Instruction::getCommand() {
//     return eCommand_;
// }

// VoidInstruction::VoidInstruction(Command eCommand) {
//     eCommand_ = eCommand;
// }

// VoidInstruction::~VoidInstruction() {
    
// }

// ByteInstruction::ByteInstruction(Command eCommand, uint8_t num) {
//     eCommand_ = eCommand;
//     nArg_ = num;
// }

// ByteInstruction::~ByteInstruction() {
    
// }

// WordInstruction::WordInstruction(Command eCommand, uint16_t num) {
//     eCommand_ = eCommand;
//     nArg_ = num;
// }

// WordInstruction::~WordInstruction() {
    
// }

// StringInstruction::StringInstruction(Command eCommand, char *str) {
//     eCommand_ = eCommand;
//     strcpy(sArg_, str);
// }

// StringInstruction::~StringInstruction() {
    
// }