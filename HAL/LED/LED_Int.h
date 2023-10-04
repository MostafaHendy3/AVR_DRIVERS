//file guard
#ifndef LED_INT_H_
#define LED_INT_H_
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

typedef struct{
    u8 LED_u8Port;
    u8 LED_u8Pin;
    u8 LED_u8Connection;
    u8 LED_u8InitStatus;
}LED_t;

ES_t LED_Init(LED_t * Copy_PAstrLEDState);
ES_t LED_SetLedOn(LED_t * Copy_PstrLEDID);
ES_t LED_SetLedOff(LED_t * Copy_PstrLEDID);


#endif