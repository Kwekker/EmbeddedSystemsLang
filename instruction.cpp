#include "instruction.hpp"
#include <stdio.h>
#include <stdlib.h>

Instruction::Instruction() {
    
}

Instruction::~Instruction() {
    
}

Command Instruction::getCommand() {
    return eCommand_;
}

VoidInstruction::VoidInstruction(Command eCommand) {
    eCommand_ = eCommand;
}

VoidInstruction::~VoidInstruction() {
    
}

ByteInstruction::ByteInstruction(Command eCommand, uint8_t num) {
    eCommand_ = eCommand;
    nArg_ = num;
}

ByteInstruction::~ByteInstruction() {
    
}

WordInstruction::WordInstruction(Command eCommand, uint16_t num) {
    eCommand_ = eCommand;
    nArg_ = num;
}

WordInstruction::~WordInstruction() {
    
}

StringInstruction::StringInstruction(Command eCommand, char *str) {
    eCommand_ = eCommand;
    sArg_ = (char *)malloc(strlen(str));
    strcpy(sArg_, str);
}

StringInstruction::~StringInstruction() {
    
}