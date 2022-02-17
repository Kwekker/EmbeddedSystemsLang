// 3.b compiler

#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#define PARSER_MAX_TOKENS 20
#define PARSER_MAX_TOKENSSIZE 50

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

class Parser {
    public:
        Parser();
        ~Parser();
        uint8_t parse(char* sLine);
        char* token(uint8_t nIndex);
        char* getFirstTokenPointer();

        static uint8_t isWhiteSpace(char c);
        static uint8_t isValid(char c);
    private:
        char aToken_[PARSER_MAX_TOKENS][PARSER_MAX_TOKENSSIZE];
        char *sFirstTokenPointer_;
};

#endif // _PARSER_HPP_


