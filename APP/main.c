#include "../LIB/stdTypes.h"
#include "../LIB/errorStates.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_Int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/ADC/ADC_Int.h"

volatile void func(void * state);
volatile void func1(u8 local_state);
volatile void func2(u8 local_state);

#include <util/delay.h>
extern EXTI_t EXTI_tConfig[3];
volatile u8 state = 0;
void read(void*p){
    ADC_enuReadHighValue((u8*)p);
}

int main()
{
    u8 adcread =0;
    u16 adc16 =0;
    GIE_voidDisable();
    DIO_enuSetPortDirection(DIO_u8PORTC,0xff);
    DIO_enuSetPinDirection(DIO_u8PORTA,DIO_u8PIN2,DIO_u8INPUT);
    DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN2,DIO_u8INPUT);
    ADC_enuInit();
    EXTI_enuInit(EXTI_tConfig);
    EXTI_enuSetSenseMode(EXTI_u8INT0,EXTI_u8FALLING_EDGE);
    EXTI_enuEnableINT(EXTI_u8INT0);
    ADC_enuEnableADC();
    ADC_enuSelectChannel(2);
    ADC_enuEnableTriggeringMode(EXTERNAL_INTERRUPT_REQUEST_0);
    ADC_enuEnableInterruptMode();
    ADC_enuCallBack(read,&adcread);
    ADC_enuStartConversion();
    GIE_voidEnable();
    
    while(1)
    {
        DIO_enuSetPortValue(DIO_u8PORTC,adcread);
    
    }

    // DIO_enuSetPinDirection(DIO_u8PORTA, DIO_u8PIN0, DIO_u8OUTPUT);
    // DIO_enuSetPinDirection(DIO_u8PORTD, DIO_u8PIN2, DIO_u8INPUT);
    // DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN2, DIO_u8PULL_UP);
    // GIE_voidEnable();
    // EXTI_enuInit(EXTI_tConfig);
    // DIO_enuSetPinDirection(DIO_u8PORTD, DIO_u8PIN3, DIO_u8INPUT);
    // DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN3, DIO_u8PULL_UP);
    // DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN2, DIO_u8INPUT);
    // DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN2, DIO_u8PULL_UP);
    

    // EXTI_enuSetCallBack(EXTI_u8INT0, (func) ,(void *) &state);
    // EXTI_enuSetCallBack(EXTI_u8INT1, (func1) ,(void *) &HIGHLOCAL);
    // EXTI_enuSetCallBack(EXTI_u8INT2, (func2) ,(void *) &LOWLOCAL);
   
}

volatile void func(void * local_state)
{
    *(u8 *)local_state = 1;
    DIO_enuSetPinValue(DIO_u8PORTA, DIO_u8PIN0,*(u8*) local_state);
}
 void  volatile func1(u8 local_state)
{
    state =local_state;
}
void volatile func2(volatile u8 local_state)
{
    state = local_state;
}
