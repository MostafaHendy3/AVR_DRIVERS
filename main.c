#include "LIB/stdTypes.h"
#include "LIB/errorStates.h"
#include "MCAL/DIO/DIO_int.h"
#include <util/delay.h>

int main()
{
    DIO_enuInit();
    DIO_enuSetPortDirection(DIO_u8PORTA, 0xFF);
    DIO_enuSetPortDirection(DIO_u8PORTB, 0xFF);
    uint8_t portA = 0xff;
    uint8_t state = 0;
    DIO_enuSetPortValue(DIO_u8PORTA, portA);
    while (1)
    {

        for (int counter = 0; counter < 8; counter++)
        {
            DIO_enuGetPortValue(DIO_u8PORTA, &state);
            DIO_enuSetPortValue(DIO_u8PORTB, state);
            DIO_enuSetPinValue(DIO_u8PORTA, counter, DIO_u8LOW);
            _delay_ms(500);
            DIO_enuGetPortValue(DIO_u8PORTA, &state);
            DIO_enuSetPortValue(DIO_u8PORTB, state);
            _delay_ms(500);
        }
    }
}