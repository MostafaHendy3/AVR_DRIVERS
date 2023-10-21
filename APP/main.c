#include "../LIB/stdTypes.h"
#include "../LIB/errorStates.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_Int.h"
#include "../MCAL/GIE/GIE_int.h"

void func(u8 state);
void func1(void);
void func2(void);

#include <util/delay.h>
extern EXTI_t EXTI_tConfig[3];
volatile u8 state = 0;
int main()
{
    DIO_enuSetPinDirection(DIO_u8PORTA, DIO_u8PIN0, DIO_u8OUTPUT);
    DIO_enuSetPinDirection(DIO_u8PORTD, DIO_u8PIN2, DIO_u8INPUT);
    DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN2, DIO_u8PULL_UP);
    GIE_voidEnable();
    EXTI_enuInit(EXTI_tConfig);
    DIO_enuSetPinDirection(DIO_u8PORTD, DIO_u8PIN3, DIO_u8INPUT);
    DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN3, DIO_u8PULL_UP);
    DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN2, DIO_u8INPUT);
    DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN2, DIO_u8PULL_UP);

    EXTI_enuSetCallBack(EXTI_u8INT0, (func) ,(void *) &state);
    EXTI_enuSetCallBack(EXTI_u8INT1, (func1) ,(void *) &state);
    EXTI_enuSetCallBack(EXTI_u8INT2, (func2) ,(void *) &state);
    while (1)
    {
    }
}

void func(u8 local_state)
{
    DIO_enuSetPinValue(DIO_u8PORTA, DIO_u8PIN0, local_state);
}
void func1(void)
{
    state = 1;
}
void func2(void)
{
    state = 0;
}
