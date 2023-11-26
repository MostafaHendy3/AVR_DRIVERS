#ifndef TIMER_PRIV_H_
#define TIMER_PRIV_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#define TCCR0 *((volatile u8 *)0x53)

#define TCCR0_WGM00 6 // waveform generation mode bit 0
#define TCCR0_WGM01 3 // waveform generation mode bit 1
#define TCCR0_CS00  0 // prescaler bit 0
#define TCCR0_CS01  1 // prescaler bit 1
#define TCCR0_CS02  2 // prescaler bit 2
#define TCCR0_COM00 4 // compare output mode bit 0
#define TCCR0_COM01 5 // compare output mode bit 1
#define TCCR0_FOC0  7 // force output compare

#define TCNT0 *((volatile u8 *)0x52)
#define TIMSK *((volatile u8 *)0x59)
#define OCIE0 1 // output compare interrupt enable
#define TOIE0 0 // overflow interrupt enable
#define TIFR *((volatile u8 *)0x58)
#define OCF0 1 // output compare flag
#define TOV0 0 // overflow flag

#define OCR0 *((volatile u8 *)0x5C)

// Waveform generation
#define NORMAL 0
#define PWM_PHASE_CORRECT 1
#define CTC 2
#define FAST_PWM 3

// Compare output mode
#define NORMAL_PORT_OPERATION 0
#define TOGGLE_OC0_ON_COMPARE_MATCH 1
#define CLEAR_OC0_ON_COMPARE_MATCH 2
#define SET_OC0_ON_COMPARE_MATCH 3

// Prescaler
#define NO_CLOCK_SOURCE 0
#define NO_PRESCALING 1
#define PRESCALER_8 2
#define PRESCALER_64 3
#define PRESCALER_256 4
#define PRESCALER_1024 5
#define EXTERNAL_CLOCK_SOURCE_FALLING_EDGE 6
#define EXTERNAL_CLOCK_SOURCE_RISING_EDGE 7


#endif /* TIMER_PRIV_H_ */
