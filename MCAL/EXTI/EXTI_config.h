#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

typedef struct{
    u8 EXTI_u8state;
    u8 EXTI_u8senseMode;
}EXTI_t;

#endif /* EXTI_CONFIG_H_ */
