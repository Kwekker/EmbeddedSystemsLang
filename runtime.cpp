#include "runtime.hpp"
// #include <bcm2835.h>

Runtime::Runtime() {
}

Runtime::~Runtime() {
        
}

std::map<std::string, uint8_t *> Runtime::mLabels;
std::map<uint8_t *, std::string> Runtime::mUnfinishedJumps;

uint8_t* Runtime::label(uint8_t *command) {
    // In runtime doen we niks met label
    // Deze functie wordt ook als het goed is nooit gerunt   
    return command;
}
uint8_t* Runtime::compLabel(Parser parser, uint8_t *code, uint8_t id) {
    mLabels[parser.token(1)] = code;
    return code;
}

uint8_t* Runtime::jump(uint8_t *command) {
    int16_t dist = *((int16_t *)command);
    return command + dist;
}
uint8_t* Runtime::compJump(Parser parser, uint8_t *code, uint8_t id) {
    *(code++) = id;
    if(mLabels.count(parser.token(1))) {
        int16_t dist = mLabels[parser.token(1)] - code;
        *((int16_t *) code) = dist;
        code += 2;
    }
    else { 
        mUnfinishedJumps[code] = parser.token(1);
        *(code++) = 0xff;
        *(code++) = 0xff;
    }
    return code;
}

uint8_t* Runtime::print(uint8_t *command) {
    while(*command != ';') putchar(*(command++));
    return command + 1;
}
uint8_t* Runtime::compPrint(Parser parser, uint8_t *code, uint8_t id) {
    *(code++) = id;

    char *c = parser.getFirstTokenPointer();

    //Kopieer de text die moet worden geprint inclusief de ;
    //TODO: zorg dat je ; kan printen met een \; 
    while(*c != 0) *(code++) = *(c++);
    *(code++) = ';';
    return code;
}

//Dank je https://stackoverflow.com/questions/26281979/c-loop-through-map
void Runtime::labelJumps() {
    for (auto const& x : mUnfinishedJumps) {
        int16_t dist = mLabels[x.second] - x.first;
        *((int16_t *) x.first) = dist;
    }
}
