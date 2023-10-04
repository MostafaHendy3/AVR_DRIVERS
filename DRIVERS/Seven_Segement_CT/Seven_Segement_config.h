#ifndef SEVEN_SEGEMENT_CONFIG_H_
#define SEVEN_SEGEMENT_CONFIG_H_
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "../../MCAL/DIO/DIO_int.h"


#define SEG_APIN    DIO_u8PIN0
#define SEG_APORT   DIO_u8PORTA

#define SEG_BPIN    DIO_u8PIN1
#define SEG_BPORT   DIO_u8PORTA

#define SEG_CPIN    DIO_u8PIN2
#define SEG_CPORT   DIO_u8PORTA

#define SEG_DPIN    DIO_u8PIN3
#define SEG_DPORT   DIO_u8PORTA

#define SEG_EPIN    DIO_u8PIN4
#define SEG_EPORT   DIO_u8PORTA

#define SEG_FPIN    DIO_u8PIN5
#define SEG_FPORT   DIO_u8PORTA

#define SEG_GPIN    DIO_u8PIN6
#define SEG_GPORT   DIO_u8PORTA

#define SEG_COM     NOT_CONNECTED
#define SEG_COMPORT NOT_CONNECTED

#define SEG_DOT     NOT_CONNECTED
#define SEG_DOTPORT NOT_CONNECTED

#define SEG_TYPE COMMON_ANODE

#endif /* SEVEN_SEGEMENT_CONFIG_H_ */
