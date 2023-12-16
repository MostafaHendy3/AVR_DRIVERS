#include "../LIB/stdTypes.h"
#include "../LIB/errorStates.h"
#include "../MCAL\GIE\GIE_Int.h"
#include "../MCAL/GIE/GIE_priv.h"
#include "../MCAL/WDT/WDT_Int.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_Int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/ADC/ADC_Int.h"
#include "../MCAL/TIMERS/TIMER_Int.h"
#include "../MCAL/TIMERS/TIMER_config.h"
#include "../MCAL/USART/USART_Int.h"
#include "../MCAL/USART/USART_config.h"
#include "../MCAL/SPI/SPI_Int.h"
#include "../MCAL/SPI/SPI_config.h"


#include "../HAL/LCD/LCD_config.h"
#include "../HAL/LCD/LCD_Int.h"
#include "../Hal/SS_LT/SS_LT_config.h"
#include "../Hal/SS_LT/SS_LT_int.h"
#include "../HAL/lm35/lm35_int.h"

#include "../MCAL/Intterupt.h"
#include "util/delay.h"
#include "../MCAL/SPI/SPI_Int.h"
#include "../MCAL/SPI/SPI_config.h"




extern EXTI_t EXTI_tConfig[3];

void func(void);
void ICU_HW(void);
int main()
{
    //master
    DIO_enuSetPinDirection(DIO_u8PORTB,DIO_u8PIN4,DIO_u8OUTPUT);
    DIO_enuSetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8HIGH);
    DIO_enuSetPinDirection(DIO_u8PORTB,DIO_u8PIN5,DIO_u8OUTPUT);
    DIO_enuSetPinValue(DIO_u8PORTB,DIO_u8PIN5,DIO_u8HIGH);
    DIO_enuSetPinDirection(DIO_u8PORTB,DIO_u8PIN6,DIO_u8INPUT);
    DIO_enuSetPinValue(DIO_u8PORTB,DIO_u8PIN6,DIO_u8FLOAT);
    DIO_enuSetPinDirection(DIO_u8PORTB,DIO_u8PIN7,DIO_u8OUTPUT);
    DIO_enuSetPinValue(DIO_u8PORTB,DIO_u8PIN7,DIO_u8HIGH);


    SPI_init();   
    
    //send string
    //b in ascii is 98
    u8 local_data=98;  
    while (1){
        SPI_sendData(local_data);
        _delay_ms(100);
    }
    
}



// void ICU_SW(){
//     static u8 counter =0;
//     counter++;
//     if(counter == 1){
//         TIMER1_SetTimerValue(0);
//     }else if (counter == 2){
//         TIMER1_GetTimerValue(&periodTicks);
//         EXTI_enuSetSenseMode(EXTI_u8INT1,EXTI_u8FALLING_EDGE);

//     }else if (counter == 3){
//         /**/
//         TIMER1_GetTimerValue(&OnTicks);
//         OnTicks =OnTicks - periodTicks;
//         counter =0;
//         LCD_enuGoHome();
//     }
    
// }

// void ICU_HW(){
//     static u8 local_count =0;
//     static u16 ReadingOne =0;
//     static u16 Readingtwo =0;
//     static u16 Readingthree =0;
//     local_count++;
//     if(local_count==1){
//         ICU_enuReadInputCapture(&ReadingOne);
//     }else if (local_count ==2){
//         ICU_enuReadInputCapture(&Readingtwo);
//         periodTicks =Readingtwo- ReadingOne;
//         ICU_enuSetEdge(Falling_edge);
//     }else if(local_count == 3){
//         ICU_enuReadInputCapture(&Readingthree);
//         OnTicks = Readingthree -Readingtwo;
//         ICU_enuDisableINT();
//     }
// }

/* 
    DIO_enuInit();
    LCD_enuInit();
    LCD_enuGoHome();
    GIE_voidDisable();
    EXTI_enuInit(EXTI_tConfig);
    EXTI_enuSetSenseMode(EXTI_u8INT0,EXTI_u8RISING_EDGE);
    DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN2,DIO_u8INPUT);
    DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8FLOAT);
    EXTI_enuSetCallBack(EXTI_u8INT0,ICU_SW,NULL);
    GIE_voidEnable();
    TIMER0_init();
    TIMER1_init();
    TIMER1_SetTimerValue(0);
    TIMER0_GeneratePWM(50);
    while (1){
        while(OnTicks ==0 && periodTicks ==0);
        LCD_enuGoHome();
        LCD_enuDisplayIntegerNumber(OnTicks);
        LCD_enuDisplayChar(' ');
        LCD_enuDisplayIntegerNumber(periodTicks);
        LCD_enuDisplayChar(' ');
    }
*/



/*
DIO_enuInit();
    LCD_enuInit();
    DIO_enuSetPinDirection(DIO_u8PORTB,DIO_u8PIN3,DIO_u8OUTPUT);
    DIO_enuSetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8LOW);

    //exti 

    //generate pwm with duty 25 %
    
    GIE_voidDisable();
    // EXTI_enuInit(EXTI_tConfig);
    // DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN3,DIO_u8INPUT);
    // DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN3,DIO_u8FLOAT);
    // EXTI_enuSetCallBack(EXTI_u8INT1,ICU_SW,NULL);
    GIE_voidEnable();
    TIMER0_init();
    TIMER1_init();
    DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN6,DIO_u8INPUT);
    DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8FLOAT);
    ICU_Init();
    ICU_enuSetCallBack(ICU_HW,NULL);
    TIMER1_SetTimerValue(0);
    TIMER0_GeneratePWM(1);

    while (1){
        while(OnTicks ==0 && periodTicks ==0);
        LCD_enuGoHome();
        LCD_enuDisplayIntegerNumber(OnTicks);
        LCD_enuDisplayChar(' ');
        LCD_enuDisplayIntegerNumber(periodTicks);
        LCD_enuDisplayChar(' ');
    }    
*/
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