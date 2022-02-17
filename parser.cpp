// 3.b compiler

#include "parser.hpp"
#include <cstring>

Parser::Parser() {

    // Maak de tokens leeg
    memset(aToken_, 0, PARSER_MAX_TOKENS * PARSER_MAX_TOKENSSIZE);
};

Parser::~Parser() {

};

uint8_t Parser::parse(char* sLine) {
    uint8_t nTokens = 0;
    char *c = sLine;

    while(isValid(*c) && nTokens < PARSER_MAX_TOKENS) {  //Repeat for all tokens
        while(isWhiteSpace(*c)) c++;
        if(isValid(*c)) {
            uint8_t charIndex = 0;
            if(nTokens == 1) sFirstTokenPointer_ = c;
            while(!isWhiteSpace(*c) && isValid(*c) && charIndex < PARSER_MAX_TOKENSSIZE - 1) {
                aToken_[nTokens][charIndex++] = *c;
                c++;
            }
            aToken_[nTokens][charIndex] = 0;
            nTokens++;
        }
    }
    return nTokens;
};

char* Parser::token(uint8_t nIndex) {

    if (nIndex >= PARSER_MAX_TOKENS) {
        nIndex = 0;
    };
    return aToken_[nIndex];
};

char* Parser::getFirstTokenPointer() {
    return sFirstTokenPointer_;
}

uint8_t Parser::isWhiteSpace(char c) {
    return c == '\t' || c == ' ' || c == '\n';
}

uint8_t Parser::isValid(char c) {
    return c != ';' && c;
}