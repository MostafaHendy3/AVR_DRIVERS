//file guard
#ifndef LED_INT_H_
#define LED_INT_H_
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "LED_config.h"
#include "LED_priv.h"

ES_t LED_Init(LED_t * Copy_PAstrLEDState);
ES_t LED_SetLedOn(LED_t * Copy_PstrLEDID);
ES_t LED_SetLedOff(LED_t * Copy_PstrLEDID);


#endif