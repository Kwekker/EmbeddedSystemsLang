#include "runtime.hpp"
// #include <bcm2835.h>

Runtime::Runtime() {
    nInsPtr_ = 0;
}

Runtime::~Runtime() {
        
}

uint16_t Runtime::run(Instruction* aInsArray[]) {
    Instruction* in = aInsArray[nInsPtr_];
    switch(in->getCommand()) {
        case label  : //Already done while compiling

            break;
        case jump   :
            nInsPtr_ = ((WordInstruction *)in)->nArg_;
            return nInsPtr_;
        case led    :
            
            break;
        case button :
            
            return nInsPtr_;
        case wait   :
            
            break;
        case print  :
            printf("%s", ((StringInstruction *)in)->sArg_);
            break;
    }
    nInsPtr_++;
    return nInsPtr_;
}