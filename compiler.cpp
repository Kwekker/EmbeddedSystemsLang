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
    Instruction *aInstructions[MAX_INSTRUCTIONS];
    uint16_t nInstructionIndex = 0;

    if(nArgc < 2) {
        printf("Bro ik heb een bestand nodig.\nGebruik ./compiler bestand.hot");
        return -1;
    }
    FILE *program = fopen(aArgv[1], "r");
    if(program == nullptr) {
        printf("Bro ik heb een bestand nodig.\nGebruik ./compiler bestand.hot");
        return -1;
    }

    //Dank je stackoverflow
    fseek(program, 0, SEEK_END);
    long programSize = ftell(program);
    fseek(program, 0, SEEK_SET);
    char *sBuffer = (char *)malloc(programSize + 1);
    fread(sBuffer, programSize, 1, program);
    fclose(program);
    sBuffer[programSize] = 0;

    char *sLine = strtok(sBuffer, ";");
    //Keep track of the label ids and the line of the label.
    uint16_t labelLineId[MAX_LABELS] = {0};


    while(sLine != NULL) {

        // Parse de regel in tokens
        uint8_t nCount = oParser.parse(sLine);

        // Compile
        if (nCount > 0) {
            if (strcmp(oParser.token(0), "button") == 0) {
                // Goed commando?
                if (nCount == 2) {
                    uint16_t index = getLabelIndex(oParser.token(1));
                    aInstructions[nInstructionIndex] = new WordInstruction(button, index);
                }
                else {
                    printf(" Syntax error! ");
                };
            }
            else
            if (strcmp(oParser.token(0), "led") == 0) {
                // Goed commando?
                if (nCount == 2) {
                    aInstructions[nInstructionIndex] = new ByteInstruction(led, atoi(oParser.token(1)));
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
                    aInstructions[nInstructionIndex] = new WordInstruction(label, index);
                    labelLineId[index] = nInstructionIndex;
                }
                else {
                    printf(" Syntax error at label! ");
                };
            }
            else if (strcmp(oParser.token(0), "jump") == 0) {
                // Goed commando?               
                if (nCount == 2) {
                    uint16_t index = getLabelIndex(oParser.token(1));
                    aInstructions[nInstructionIndex] = new WordInstruction(jump, index);
                }
                else {
                    printf(" Syntax error at jump! ");
                };
            }

            else if (strcmp(oParser.token(0), "wait") == 0) {
                // Goed commando?
                if (nCount == 2) {
                    aInstructions[nInstructionIndex] = new WordInstruction(wait, atoi(oParser.token(1)));
                }
                else {
                    printf(" Syntax error on wait! ");
                };
            }

            else if (strcmp(oParser.token(0), "print") == 0) {
                // Goed commando?
                if (nCount >= 2) {
                    aInstructions[nInstructionIndex] = new StringInstruction(print, oParser.getFirstTokenPointer());
                }
                else {
                    printf(" Syntax error on print! ");
                };
            }
            else {
                printf(" Onbekende invoer! ");
            };
        };
        nInstructionIndex++;
        sLine = strtok(NULL, ";");
    }

    // Afsluiten
    fclose(program);

    uint16_t nInstructionAmount = nInstructionIndex;
    nInstructionIndex = 0;

    //Edit labels sweep
    for(uint16_t i = 0; i < nInstructionAmount; i++) {
        Command com = aInstructions[i]->getCommand();
        if(com == label || com == jump || com == button) {
            ((WordInstruction *) aInstructions[i])->nArg_ = labelLineId[((WordInstruction *) aInstructions[i])->nArg_];
        }
    }

    printf("Compiled! :)\n------------------------------\n\n");

    while(oRuntime.run(aInstructions) < nInstructionAmount);

    
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