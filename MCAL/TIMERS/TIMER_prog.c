#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "../../MCAL/TIMERS/TIMER_priv.h"
#include "../../MCAL/TIMERS/TIMER_config.h"

#include "../Intterupt.h"

static void (*TIMER0_callBackPtr)() = NULL;
static  void * TIMER0_callBackParameter = NULL;


ES_t TIMER0_init(void){
    ES_t local_errorstate = ES_NOK;
    //choose mode
    #if TIMER0_WAVEFORM_GENERATION_MODE == NORMAL
        TCCR0 &= ~(1<<TCCR0_WGM00);
        TCCR0 &= ~(1<<TCCR0_WGM01);    
    #endif

    #if TIMER0_INTERRUPT_ENABLE == OCIE0
        TIMSK |= (1<<OCIE0);
    #endif

    /*Set compare match value*/
    OCR0 = 250;
    /*Set prescaler*/
    #if TIMER0_PRESCALER == NO_CLOCK_SOURCE
        TCCR0 &= ~(1<<TCCR0_CS00);
        TCCR0 &= ~(1<<TCCR0_CS01);
        TCCR0 &= ~(1<<TCCR0_CS02);
    #elif TIMER0_PRESCALER == NO_PRESCALING
        TCCR0 |= (1<<TCCR0_CS00);
        TCCR0 &= ~(1<<TCCR0_CS01);
        TCCR0 &= ~(1<<TCCR0_CS02);
    #elif TIMER0_PRESCALER == PRESCALER_8
        TCCR0 &= ~(1<<TCCR0_CS00);
        TCCR0 |= (1<<TCCR0_CS01);
        TCCR0 &= ~(1<<TCCR0_CS02);
    #elif TIMER0_PRESCALER == PRESCALER_64
        TCCR0 |= (1<<TCCR0_CS00);
        TCCR0 |= (1<<TCCR0_CS01);
        TCCR0 &= ~(1<<TCCR0_CS02);
    #endif
    

    return local_errorstate;
}
ES_t TIMER0_callBack(void (*func)(void),void *Copy_pvidParameter){

    ES_t local_errorstate = ES_NOK;
    if(func != NULL){
        TIMER0_callBackPtr = func;
        TIMER0_callBackParameter = Copy_pvidParameter;
        local_errorstate = ES_OK;
    }else{
        local_errorstate = ES_NULL_POINTER;
    }
    return local_errorstate;
}
ISR(VECT_TIMER0_COMP){
    if(TIMER0_callBackPtr != NULL){
        TIMER0_callBackPtr(TIMER0_callBackParameter);
    }
}