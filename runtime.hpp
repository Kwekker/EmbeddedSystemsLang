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

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "instruction.hpp"

class Runtime {
    public:
        Runtime();
        ~Runtime();
        uint16_t run(Instruction *aInsArray[]);
        
    private:
        uint16_t nInsPtr_;
};
    

#endif // _RUNTIME_HPP_