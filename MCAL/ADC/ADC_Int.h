#ifndef ADC_INT_H_
#define ADC_INT_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

ES_t ADC_enuInit(void); 
ES_t ADC_enuStartConversion(void);
ES_t ADC_enuPollingSystem(void);
ES_t ADC_enuReadHighValue(u8 * Copy_pu8Value);
ES_t ADC_enuRead(u16 * Copy_pu16Value);
ES_t ADC_enuCallBack(void (*copy_pfunAppFun)(void *),void *copy_pvidAppParameter);
ES_t ADC_enuEnableADC(void);
ES_t ADC_enuDisableADC(void);
ES_t ADC_enuEnableInterruptMode(void);
ES_t ADC_enuDisableInterruptMode(void);
ES_t ADC_enuSelectChannel(u8 copy_u8channelID);
ES_t ADC_enuEnableTriggeringMode(u8 copy_u8TriggerSource);
ES_t ADC_enuDisableTriggeringMode(void);

#endif /* ADC_INT_H_ */
