#ifndef SPI_INT_H_
#define SPI_INT_H_
#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"

ES_t SPI_init();
ES_t SPI_sendData(u8 Copy_u8Data);
ES_t SPI_RecieveData(u8 *Copy_u8Data);




#endif /* SPI_INT_H_ */
