#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "GIE_config.h"
#include "GIE_priv.h"


void GIE_voidEnable(void){
    SREG |= (1<<7);
}
void GIE_voidDisable(void){
    SREG &= ~(1<<7);
}