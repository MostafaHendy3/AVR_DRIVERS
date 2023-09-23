#include "LIB/stdTypes.h"
#include "LIB/errorStates.h"
#include "MCAL/DIO/DIO_int.h"
#include "HAL/Switch/Switch_int.h"

#include <util/delay.h>

extern SW_t Switch_AstrSwitchState[SW_NUM];

int main()
{
    DIO_enuInit();
    Switch_enuInit(Switch_AstrSwitchState);
    u8 pinState ;
    u8 seven_seg[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                        0x6D, 0x7D, 0x07, 0x7F, 0x6F};
    while (1)
    {
        Switch_enuGetState(Switch_AstrSwitchState, &pinState);
        for (int i = 0; i < 3; i++)
        {
            if (pinState == 0)
            {
                DIO_enuSetPinValue(DIO_u8PORTB, i, DIO_u8HIGH);
            }else{
                DIO_enuSetPinValue(DIO_u8PORTB, i, DIO_u8LOW);
            }
           
        }
    }
}

/*
    for (int counter1 = 0; counter1 <= 9; counter1++)
        {
            DIO_enuSetPortValue(DIO_u8PORTA, seven_seg[counter1]);
            for (int i = 0; i <=9; i++)
            {
               DIO_enuSetPortValue(DIO_u8PORTB, ~seven_seg[i]);
                _delay_ms(500);
            }
            DIO_enuSetPortValue(DIO_u8PORTB, ~seven_seg[0]);

        }*/