#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_

#define EXTI_u8ENABLED  1
#define EXTI_u8DISABLED 0

#define EXTI_u8RISING_EDGE  1
#define EXTI_u8FALLING_EDGE 0
#define EXTI_u8ON_CHANGE    2
#define EXTI_u8LOW_LEVEL    3

#define EXTI_INT0 0
#define EXTI_INT1 1
#define EXTI_INT2 2

#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
#define ISC2 6

#define MCUCR *((volatile u8*)0x55)
#define MCUCSR *((volatile u8*)0x54)
#define GICR *((volatile u8*)0x5B)
#define GIFR *((volatile u8*)0x5A)

#define ISR(VECT) void VECT(void)__attribute__((signal));\
                    void VECT(void)

#define  VECT_INT0  __vector_1
#define  VECT_INT1  __vector_2
#define  VECT_INT2  __vector_3
#define  VECT_INT3  __vector_4
#define  VECT_INT4  __vector_5
#define  VECT_INT5  __vector_6
#define  VECT_INT6  __vector_7
#define  VECT_INT7  __vector_8
#define ADC_vect    __vector_16

#endif /* EXTI_PRIV_H_ */
