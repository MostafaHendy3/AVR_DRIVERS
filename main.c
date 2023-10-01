#include "LIB/stdTypes.h"
#include "LIB/errorStates.h"

#include "MCAL/DIO/DIO_int.h"
#include "HAL/Switch/Switch_int.h"
#include "HAL/Switch/Switch_config.h"
#include "HAL/LED/LED_int.h"
#include "HAL/LED/LED_config.h"

#include <util/delay.h>

extern SW_t Switch_AstrSwitchState[SW_NUM];
extern LED_t LED_AstrLEDState[LED_NUM];

int main()
{
    DIO_enuInit();
    DIO_enuSetPortDirection(DIO_u8PORTA, 0b01111111);
    DIO_enuSetPortDirection(DIO_u8PORTB, 0b01111111);
    u8 sevenSegements[] = {
        0b00111111,
        0b00000110,
        0b01011011,
        0b01001111,
        0b01100110,
        0b01101101,
        0b01111101,
        0b00000111,
        0b01111111,
        0b01101111};

    // LED_Init(LED_AstrLEDState);
    Switch_enuInit(Switch_AstrSwitchState);
    u8 local_u8SwitchState1 = 0;
    u8 local_u8SwitchState2 = 0;
    static u8 local_u8ICounter = 0;
    u8 digitone = sevenSegements[0];
    u8 digittwo = sevenSegements[0];
    DIO_enuSetPortValue(DIO_u8PORTA,digitone);
    DIO_enuSetPortValue(DIO_u8PORTB, digittwo);
    u8 localflag=0;
    while (1)
    {
        Switch_enuGetState(&Switch_AstrSwitchState[0], &local_u8SwitchState1);
        Switch_enuGetState(&Switch_AstrSwitchState[1], &local_u8SwitchState2);

        if (local_u8SwitchState1 == 0 && localflag ==0)
        {
            local_u8ICounter++;
            localflag=1;
        }
        else if (local_u8SwitchState2 == 0 && localflag ==0)
        {
            local_u8ICounter--;
            localflag=1;
        }else if(local_u8SwitchState1 == 1 && local_u8SwitchState2 == 1){
            localflag=0;
        }
        digitone =local_u8ICounter % 10;
        digittwo = local_u8ICounter / 10;
        DIO_enuSetPortValue(DIO_u8PORTA, sevenSegements[digitone]);
        DIO_enuSetPortValue(DIO_u8PORTB, sevenSegements[digittwo]);
    }
}
/*

                                                Assignment 2

1-Write Embedded C code to control a led using a push button.                 ( 6 points)
 Requirements:
•The Led 1 & 2 is connected to pin 0 & 1 in PORTA.
• The switch 1 , 2 , 3 is connected to pin 0 & 1 & 2 in PORTB.
• If switch 1 is pressed just turn on the first led1 only , if switch     2 is pressed just turn on led2 only , if switch 3 is pressed turn on the 2 leds .
• In case no switches are pressed both leds are off.

2- Write Embedded c code to control a 7-segment using two push buttons.      ( 8 points)
Requirements:
 • The two switches are connected to pin 0 & 1 in PORTA.
• If the switch1 is pressed just increase the number appeared in the 7 segment display, and if the number reach the maximum number (9) do nothing.
• If the switch2 is pressed just decrease the number appeared in the 7 segment display, and if the number reach the minimum number (0) do nothing.
3-  Write Embedded c code to control  2 multiplexed seven segments using two push buttons.
 , the first one use to count up , and the second one use to count down , when you start your program , number 50 is displayed.               ( 10 points)
Requirements:
• If the switch1 is pressed just increase the value appearing in the two multiplexed 7 segment displays.
EX :- 50 becomes 51 and so on ..

 •If the switch 2 is pressed just decrease the number appearing in the two multiplexed 7 segment displays.
 EX :- 50 becomes 49 and so on ..

4- implement the DIO driver    ( 6 points)
*/