#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "EXTI_priv.h"
#include "EXTI_config.h"
#include "Interrupt.h"
// pointer to 2d array of void functions

static volatile void(*EXTI_Pfun[3][2]) = {{NULL, NULL}, {NULL, NULL}, {NULL, NULL}};

ES_t EXTI_enuInit(EXTI_t *Copy_pstrEXTI)
{
    ES_t Local_enuErrorState = ES_NOK;

    if (Copy_pstrEXTI != NULL)
    {
        // enable Active INT
        u8 Local_u8iterator = 0;
        for (Local_u8iterator = 0; Local_u8iterator < 3; Local_u8iterator++)
        {
            if (Copy_pstrEXTI[Local_u8iterator].EXTI_u8state == EXTI_u8ENABLED)
            {
                switch (Local_u8iterator)
                {
                case EXTI_INT0:
                    GICR |= (1 << 6);
                    switch (Copy_pstrEXTI[Local_u8iterator].EXTI_u8senseMode)
                    {
                    case EXTI_u8FALLING_EDGE:
                        MCUCR |= (1 << ISC01);
                        MCUCR &= ~(1 << ISC00);
                        break;
                    case EXTI_u8RISING_EDGE:
                        MCUCR |= (1 << ISC00);
                        MCUCR |= (1 << ISC01);
                        break;
                    case EXTI_u8ON_CHANGE:
                        MCUCR &= ~(1 << ISC01);
                        MCUCR |= (1 << ISC00);
                        break;
                    case EXTI_u8LOW_LEVEL:
                        MCUCR &= ~(1 << ISC01);
                        MCUCR &= ~(1 << ISC00);
                        break;
                    default:
                        break;
                    }
                    break;
                case EXTI_INT1:
                    GICR |= (1 << 7);
                    switch (Copy_pstrEXTI[Local_u8iterator].EXTI_u8senseMode)
                    {
                    case EXTI_u8FALLING_EDGE:
                        MCUCR |= (1 << ISC11);
                        MCUCR &= ~(1 << ISC10);
                        break;
                    case EXTI_u8RISING_EDGE:
                        MCUCR |= (1 << ISC10);
                        MCUCR |= (1 << ISC11);
                        break;
                    case EXTI_u8ON_CHANGE:
                        MCUCR &= ~(1 << ISC11);
                        MCUCR |= (1 << ISC10);
                        break;
                    case EXTI_u8LOW_LEVEL:
                        MCUCR &= ~(1 << ISC11);
                        MCUCR &= ~(1 << ISC10);
                        break;
                    default:
                        break;
                    }
                    break;
                case EXTI_INT2:
                    GICR |= (1 << 5);
                    switch (Copy_pstrEXTI[Local_u8iterator].EXTI_u8senseMode)
                    {
                    case EXTI_u8FALLING_EDGE:
                        MCUCSR &= ~(1 << ISC2);
                        break;
                    case EXTI_u8RISING_EDGE:
                        MCUCSR |= (1 << ISC2);
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
    else
    {
        Local_enuErrorState = ES_NULL_POINTER;
    }
    return Local_enuErrorState;
}
ES_t EXTI_enuEnableINT(u8 Copy_u8EXTI_INDEX)
{
    ES_t Local_enuErrorState = ES_NOK;
    if (Copy_u8EXTI_INDEX < 3)
    {
        switch (Copy_u8EXTI_INDEX)
        {
        case EXTI_INT0:
            GICR |= (1 << 6);
            break;
        case EXTI_INT1:
            GICR |= (1 << 7);
            break;
        case EXTI_INT2:
            GICR |= (1 << 5);
            break;
        default:
            break;
        }
    }
    else
    {
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }

    return Local_enuErrorState;
}
ES_t EXTI_enuDisableINT(u8 Copy_u8EXTI_INDEX)
{
    ES_t Local_enuErrorState = ES_NOK;
    if (Copy_u8EXTI_INDEX < 3)
    {
        switch (Copy_u8EXTI_INDEX)
        {
        case EXTI_INT0:
            GICR &= ~(1 << 6);
            break;
        case EXTI_INT1:
            GICR &= ~(1 << 7);
            break;
        case EXTI_INT2:
            GICR &= ~(1 << 5);
            break;
        default:
            break;
        }
    }
    else
    {
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }

    return Local_enuErrorState;
}
ES_t EXTI_enuSetSenseMode(u8 Copy_u8EXTI_INDEX, u8 Copy_u8SenseMode)
{
    ES_t Local_enuErrorState = ES_NOK;
    if (Copy_u8SenseMode < 4 && Copy_u8EXTI_INDEX < 4)
    {
        switch (Copy_u8EXTI_INDEX)
        {
        case EXTI_INT0:
            switch (Copy_u8SenseMode)
            {
            case EXTI_u8FALLING_EDGE:
                MCUCR |= (1 << ISC01);
                MCUCR &= ~(1 << ISC00);
                break;
            case EXTI_u8RISING_EDGE:
                MCUCR |= (1 << ISC00);
                MCUCR |= (1 << ISC01);
                break;
            case EXTI_u8ON_CHANGE:
                MCUCR &= ~(1 << ISC01);
                MCUCR |= (1 << ISC00);
                break;
            case EXTI_u8LOW_LEVEL:
                MCUCR &= ~(1 << ISC01);
                MCUCR &= ~(1 << ISC00);
                break;
            }
        case EXTI_INT1:
            switch (Copy_u8SenseMode)
            {
            case EXTI_u8FALLING_EDGE:
                MCUCR |= (1 << ISC11);
                MCUCR &= ~(1 << ISC10);
                break;
            case EXTI_u8RISING_EDGE:
                MCUCR |= (1 << ISC10);
                MCUCR |= (1 << ISC11);
                break;
            case EXTI_u8ON_CHANGE:
                MCUCR &= ~(1 << ISC11);
                MCUCR |= (1 << ISC10);
                break;
            case EXTI_u8LOW_LEVEL:
                MCUCR &= ~(1 << ISC11);
                MCUCR &= ~(1 << ISC10);
                break;
            }
        case EXTI_INT2:
            switch (Copy_u8SenseMode)
            {
            case EXTI_u8FALLING_EDGE:
                MCUCSR &= ~(1 << ISC2);
                break;
            case EXTI_u8RISING_EDGE:
                MCUCSR |= (1 << ISC2);
                break;
            }
        default:
            break;
        }
    }

    return Local_enuErrorState;
}
ES_t EXTI_enuSetCallBack(u8 Copy_u8EXTI_INDEX, void *Copy_pvCallBack, void *Copy_pvCallBackArg)
{
    ES_t Local_enuErrorState = ES_NOK;
    if (Copy_u8EXTI_INDEX < 3)
    {
        if (Copy_pvCallBack != NULL && Copy_pvCallBackArg != NULL)
        {
            EXTI_Pfun[Copy_u8EXTI_INDEX][0] = Copy_pvCallBack;
            EXTI_Pfun[Copy_u8EXTI_INDEX][1] = Copy_pvCallBackArg;
        }
    }
    else
    {
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }

    return Local_enuErrorState;
}
ISR(VECT_INT0)
{
    if (EXTI_Pfun[0][0] != NULL)
    {
        
        ((void (*)(u8))EXTI_Pfun[0][0])(*(u8 *)EXTI_Pfun[0][1]);
    }
}
ISR(VECT_INT1)
{
    if (EXTI_Pfun[1] != NULL)
    {
        ((void (*)(u8))EXTI_Pfun[1][0])(*(u8 *)EXTI_Pfun[1][1]);
    }
}
ISR(VECT_INT2)
{
    if (EXTI_Pfun[2] != NULL)
    {
        ((void (*)(u8))EXTI_Pfun[2][0])( *(u8 *) EXTI_Pfun[2][1]);
    }
}