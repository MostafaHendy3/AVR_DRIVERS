#ifndef USART_INT_H_
#define USART_INT_H_

#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"



ES_t USART_enuInit(void);
ES_t USART_enuSendChar(u8 Copy_u8Char);
ES_t USART_enuReceiveChar(u8 * Copy_pu8Char);
ES_t USART_enuSendString(char * Copy_pCString);
ES_t USART_enuReceiveString(char * Copy_pCString);

#endif /* USART_INT_H_ */
