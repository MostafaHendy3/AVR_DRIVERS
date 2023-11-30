#ifndef TIMER_PRIV_H_
#define TIMER_PRIV_H_

#define TCCR0 *((volatile u8 *)0x53)

#define TCCR0_WGM00 6 // waveform generation mode bit 0
#define TCCR0_WGM01 3 // waveform generation mode bit 1
#define TCCR0_CS00 0  // prescaler bit 0
#define TCCR0_CS01 1  // prescaler bit 1
#define TCCR0_CS02 2  // prescaler bit 2
#define TCCR0_COM00 4 // compare output mode bit 0
#define TCCR0_COM01 5 // compare output mode bit 1
#define TCCR0_FOC0 7  // force output compare

#define TCNT0 *((volatile u8 *)0x52)
#define TIMSK *((volatile u8 *)0x59)
#define OCIE0 1 // output compare interrupt enable
#define TOIE0 0 // overflow interrupt enable
#define NO_INTERRUTP 6
#define TIFR *((volatile u8 *)0x58)
#define OCF0 1 // output compare flag
#define TOV0 0 // overflow flag

#define OCR0 *((volatile u8 *)0x5C)

#define DISCONNECTED 0
#define CONNECTED 1

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

// Fast PWM mode
#define NON_INVERTING_CLR_ON_COMP 22
#define INVERTING_SET_ON_COMP 33

//phase correct PWM mode
#define NON_INVERTING_SET_ON_COMP 44
#define INVERTING_CLR_ON_COMP 55

// Prescaler
#define NO_CLOCK_SOURCE 0
#define NO_PRESCALING 1
#define PRESCALER_8 8
#define PRESCALER_64 64
#define PRESCALER_256 256
#define PRESCALER_1024 1024
#define EXTERNAL_CLOCK_SOURCE_FALLING_EDGE 6
#define EXTERNAL_CLOCK_SOURCE_RISING_EDGE 7



#endif /* TIMER_PRIV_H_ */
