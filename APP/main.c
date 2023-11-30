#include "../LIB/stdTypes.h"
#include "../LIB/errorStates.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_Int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/ADC/ADC_Int.h"
#include "../MCAL/TIMERS/TIMER_Int.h"

#include "../HAL/LCD/LCD_config.h"
#include "../HAL/LCD/LCD_Int.h"
#include "../Hal/SS_LT/SS_LT_config.h"
#include "../Hal/SS_LT/SS_LT_int.h"
#include "../HAL/lm35/lm35_int.h"

#include <util/delay.h>

/*
    make two multiplexed seven segement 
    first display : count up every second
    second display : Count down Every second  
    Using Timer0 (Compare Match)
*/

// extern SEVEN_SEGMENT_t SS_LT_AstrConfig[SEG_NUM];
// static volatile u8 SevenSegement_CounterUP =0;
// static volatile u8 SevenSegement_CounterDown =9;
// volatile u8 state =0;

// void LED(void){
//     static u16 local_u16Counter =0;
//     local_u16Counter++;
//     //Compare match time 250 us
//     //blink time 10 ms
//     //count time 1 Second
//     if (local_u16Counter % 40 ==0){
//         if(state == 0){
//             SevenSegement_enuDisableCommon(0);
//             SevenSegement_enuEnableCommon(1);
//             SevenSegement_enuDisplayNum(1,SevenSegement_CounterUP);
//             state =1;
//         }else {
//             SevenSegement_enuDisableCommon(1);
//             SevenSegement_enuEnableCommon(0);
//             SevenSegement_enuDisplayNum(0,SevenSegement_CounterDown);
//             state=0;
//         }
//     }
//     if(local_u16Counter == 4000){
//         SevenSegement_CounterUP++;
//         SevenSegement_CounterDown--;
//         local_u16Counter=0;
//     }
// }

void PWM(void){
    static u8 localCounter =0;
    localCounter++;
    if(localCounter==19){
        DIO_enuSetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8LOW);
    }else if(localCounter==20){
        DIO_enuSetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8HIGH);
        localCounter=0;
    }
}

void fun(){
    DIO_enuTogPinValue(DIO_u8PORTB,DIO_u8PIN4);
}

int main()
{
    
    DIO_enuSetPinDirection(DIO_u8PORTB,DIO_u8PIN4,DIO_u8OUTPUT);
    DIO_enuSetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8LOW);
    // SevenSegement_Init(SS_LT_AstrConfig);
    // SevenSegement_enuDisableCommon(0);
    // SevenSegement_enuEnableCommon(1);

    GIE_voidEnable();
    TIMER0_init();
    TIMER0_setCompareValue(125);
    TIMER0_callBack(fun,NULL);

    //TIMER0_callBack(&PWM,NULL);    
    while (1){

    }
    
}
