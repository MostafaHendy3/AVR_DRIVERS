#ifndef LCD_INT_H_
#define LCD_INT_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"


ES_t LCD_enuInit(void);
ES_t LCD_enuDisplayChar(u8 Copy_u8Data);
ES_t LCD_enuSendCommand(u8 Copy_u8Command);
ES_t LCD_enuClear(void);
ES_t LCD_enuGoHome(void);


#endif /* LCD_INT_H_ */
