// 3.c runtime
//
// g++ -Wall -o runtime compiler.cpp parser.cpp runtime.cpp
// ./runtime

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <map>
#include <string>
#include "parser.hpp"
#include "runtime.hpp"
#include "instruction.hpp"

#define MAX_INVOER 100
#define MAX_INSTRUCTIONS 255
#define LABEL_UNKNOWN 0xffff
#define MAX_LABELS          10
#define MAX_LABEL_LENGTH    6

uint16_t getLabelIndex(std::string sLabel);

int main(int nArgc, char* aArgv[]) {
    setbuf(stdout, NULL);
    Parser oParser;
    Runtime oRuntime;
    AbstractInstruction *aInstructions[MAX_INSTRUCTIONS];
    uint16_t nInstructionPtr = 0;

    if(nArgc < 2) {
        printf("Bro ik heb een bestand nodig.\nGebruik ./compiler bestand.hot");
        return -1;
    }
    FILE *program = fopen(aArgv[1], "r");
    if(program == nullptr) {
        printf("Bro ik heb een bestand nodig.\nGebruik ./compiler bestand.hot");
        return -1;
    }

    char sBuffer[MAX_INVOER + 1];
    uint8_t nCount;

    uint16_t labelLineId[MAX_LABELS] = {0};

    // Initialiseren

    // Vraag om een regel tekst in sBuffer
    while(sBuffer[0] != 0 && sBuffer[0] != EOF) {
        // Lees een regel
        fgets(sBuffer, MAX_INVOER, program);
        printf("Gelezen: [%s]\n", sBuffer);
        // Parse de regel in tokens
        nCount = oParser.parse(sBuffer);

        /*// Toon de tokens
        printf("Tokens %d: ", nCount);
        for (uint8_t i = 0; i < nCount; i++) {
            printf("{%s}", oParser.token(i));
        };
        printf("\n");
        */

        // Compile
        if (nCount > 0) {
            if (strcmp(oParser.token(0), "button") == 0) {
                // Goed commando?
                if (nCount == 2) {
                    uint16_t index = getLabelIndex(oParser.token(1));
                    aInstructions[nInstructionPtr] = new Instruction<uint16_t>(button, index);
                }
                else {
                    printf(" Syntax error! ");
                };
            }
            else
            if (strcmp(oParser.token(0), "led") == 0) {
                // Goed commando?
                if (nCount == 2) {
                    aInstructions[nInstructionPtr] = new Instruction<uint8_t>(led, atoi(oParser.token(1)));
                }
                else {
                    printf(" Syntax error at led! ");
                };
            }
            else
            if (strcmp(oParser.token(0), "label") == 0) {
                // Goed commando?
                if (nCount == 2) {
                    uint16_t index = getLabelIndex(oParser.token(1));
                    aInstructions[nInstructionPtr] = new Instruction<uint16_t>(label, index);
                    labelLineId[index] = nInstructionPtr;
                }
                else {
                    printf(" Syntax error at label! ");
                };
            }
            else if (strcmp(oParser.token(0), "jump") == 0) {
                // Goed commando?
                if (nCount == 2) {
                    uint16_t index = getLabelIndex(oParser.token(1));
                    aInstructions[nInstructionPtr] = new Instruction<uint16_t>(jump, index);
                }
                else {
                    printf(" Syntax error at jump! ");
                };
            }

            else if (strcmp(oParser.token(0), "wait") == 0) {
                // Goed commando?
                if (nCount == 2) {
                    aInstructions[nInstructionPtr] = new Instruction<uint16_t>(wait, atoi(oParser.token(1)));
                }
                else {
                    printf(" Syntax error! ");
                };
            }

            else if (strcmp(oParser.token(0), "print") == 0) {
                // Goed commando?
                if (nCount == 2) {
                    aInstructions[nInstructionPtr] = new Instruction<std::string>(print, oParser.token(1));
                }
                else {
                    printf(" Syntax error! ");
                };
            }
            else {
                printf(" Onbekende invoer! ");
            };
        };
        nInstructionPtr++;
    }

    //Edit labels sweep
    for(uint16_t i = 0; i < nInstructionPtr; i++) {
        if(aInstructions[i]->eCommand_ == label) {
            ((Instruction<uint16_t> *) aInstructions[i]) -> setArgument( labelLineId[ ((Instruction<uint16_t> *)aInstructions[i]) -> getArgument()]);
        }
    }

    // Afsluiten
    printf("\nAfgesloten :-)\n\n");
    return 0;
};

//Ik gebruik hier strings want maps vinden char arrays niet leuk
uint16_t getLabelIndex(std::string sLabel) {
    static std::map<std::string, uint16_t> labels;
    static uint16_t nextIndex = 0;

    if(!labels.count(sLabel)) {
        labels[sLabel] = nextIndex;
        return nextIndex++;
    }
    else return labels[sLabel];

}