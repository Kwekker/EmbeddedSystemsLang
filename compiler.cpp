// 3.c runtime
//
// g++ -Wall -o runtime compiler.cpp parser.cpp runtime.cpp
// ./runtime

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <map>
#include <string>
#include <string.h>
#include "parser.hpp"
#include "runtime.hpp"
#include "instruction.hpp"

int main(int nArgc, char* aArgv[]) {
    setbuf(stdout, NULL);
    Parser oParser;
    uint8_t compiled[1024] = {0};

    const uint8_t instructionCount = 3;
    Instruction instructions[] = {
        Instruction("label", Runtime::label, Runtime::compLabel),
        Instruction("jump", Runtime::jump, Runtime::compJump),
        Instruction("print", Runtime::print, Runtime::compPrint)
    };


    printf("Reading file..\n");

    if(nArgc < 2) {
        printf("Bro ik heb een bestand nodig.\nGebruik ./compiler bestand.hot\n");
        return -1;
    }
    FILE *program = fopen(aArgv[1], "r");
    if(program == nullptr) {
        printf("Dat was geen geldig bestand...\nGebruik ./compiler bestand.hot\n");
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
    uint8_t* compiledPointer = compiled;


    printf("--== Compiling ==--\n");
    //compileer de dingen
    while(sLine != NULL) { 

        printf("\tCompiling [\e[33m%s\e[0m]\n", sLine);
        // Parse de regel in tokens
        uint8_t nCount = oParser.parse(sLine);

        // Compile
        if (nCount > 0) {
            for(uint8_t i = 0; i < instructionCount; i++) {
                printf("\t\t%s == %s??\n", oParser.token(0), instructions[i].getName());
                if(strcmp(oParser.token(0), instructions[i].getName()) == 0) {
                    compiledPointer = instructions[i].compile(oParser, compiledPointer);
                    break;
                }
            }
        }

        sLine = strtok(NULL, ";");
    }

    // Afsluiten
    fclose(program);
    *compiledPointer = 0;

    printf("--== Labeling jumps ==--\n");
    Runtime::labelJumps();

    
    printf("The compiled program: \n");
    uint8_t* c = compiled;
    uint8_t zCount = 0;
    while(zCount < 5) {
        printf("%02x ", *(c++)); // :O c++!
        if(*c == 0) zCount++;
        else zCount = 0;
    }

    printf("\n");
    c = compiled;
    zCount = 0;
    while(zCount < 5) {
        if(*c == '\n') printf("\\n ");
        else printf(" %c ", *c);
        c++;
        if(*c == 0) zCount++;
        else zCount = 0;
    }




    // Run het programma
    compiledPointer = compiled;

    printf("\n--== Running the program ==--\n\n");
    while(*compiledPointer != 0) {
        compiledPointer = instructions[*compiledPointer - 1].run(compiledPointer + 1);//instructions[*compiledPointer - 1]
    }
    printf("\n\n--== End of program ==--\n");

    return 0;
};