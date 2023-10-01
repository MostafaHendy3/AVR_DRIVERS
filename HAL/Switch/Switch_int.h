//file gaurd 
#ifndef SWITCH_INT_H_
#define SWITCH_INT_H_
#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"

#include "Switch_priv.h"
#include "Switch_config.h"


//function to initialize the switch
ES_t Switch_enuInit(SW_t * Copy_AstrSwitchState);
ES_t Switch_enuGetState(SW_t *Copy_AstrSwitchState,u8 * Copy_pu8SwState);

#endif /* SWITCH_INT_H_ */