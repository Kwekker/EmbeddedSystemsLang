#include "instruction.hpp"
#include <cstring>

Instruction::Instruction(const char *name, uint8_t *(*funcPtr)(uint8_t *), uint8_t *(*compileFunc)(Parser, uint8_t *, uint8_t)) {
    this->run = funcPtr;
    this->compileFunc = compileFunc;
    std::strcpy(this->sName_, name);
    nId_ = getId();
    printf("\n%s = 0x%02x\n", this->sName_, this->nId_);
}

Instruction::~Instruction() {
    
}

//Start bij 1 want we willen geen \0 karakter.
uint8_t Instruction::nInstructionCount_ = 1;

uint8_t* Instruction::compile(Parser parser, uint8_t *compiled) {
    return compileFunc(parser, compiled, nId_);
}

char* Instruction::getName() {
    return sName_;
}

uint8_t Instruction::getId() {
    return nInstructionCount_++;
}




