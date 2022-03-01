/* 
Voorbeeld van de taal:

label x
led rood on
wait 100
led rood off
wait 100
jump x
*/

#ifndef _RUNTIME_HPP_
#define _RUNTIME_HPP_

#define MAX_INVOER 100
#define MAX_INSTRUCTIONS 255
#define LABEL_UNKNOWN 0xffff
#define MAX_LABELS          10
#define MAX_LABEL_LENGTH    6
#define MAX_PROGRAM_LENGTH 1024

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <map>
#include "instruction.hpp"
#include "parser.hpp"

class Runtime {
    public:
        Runtime();
        ~Runtime();

        static uint8_t *label(uint8_t *command);
        static uint8_t *compLabel(Parser parser, uint8_t *code, uint8_t id);

        static uint8_t *jump(uint8_t *command);
        static uint8_t *compJump(Parser parser, uint8_t *code, uint8_t id);
        
        static uint8_t *print(uint8_t *command);
        static uint8_t *compPrint(Parser parser, uint8_t *code, uint8_t id);

        static void labelJumps();
    private:
        static std::map<std::string, uint8_t *> mLabels;
        static std::map<uint8_t *, std::string> mUnfinishedJumps;
};
    

#endif // _RUNTIME_HPP_