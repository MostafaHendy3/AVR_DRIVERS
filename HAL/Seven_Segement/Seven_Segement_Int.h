#ifndef SEVEN_SEGEMENT_INT_H_
#define SEVEN_SEGEMENT_INT_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

ES_t SevenSegement_Init(void);
ES_t SevenSegement_enuDisplayNum(u8 Copy_u8Number);
ES_t SevenSegement_enuEnableCommon(void);
ES_t SevenSegement_enuDisableCommon(void);
ES_t SevenSegement_enuEnableDot(void);
ES_t SevenSegement_enuDisableDot(void);
ES_t SevenSegement_enuClear(void);

#endif /* SEVEN_SEGEMENT_INT_H_ */
