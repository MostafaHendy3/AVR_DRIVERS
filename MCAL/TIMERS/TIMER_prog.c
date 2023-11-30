#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "../../MCAL/TIMERS/TIMER_priv.h"
#include "../../MCAL/TIMERS/TIMER_config.h"

#include "../Intterupt.h"

static void (*TIMER0_callBackPtr)() = NULL;
static  void * TIMER0_callBackParameter = NULL;
static u32 gNum_OVF =0;
static u32 gPreload =0;


ES_t TIMER0_init(void){
    ES_t local_errorstate = ES_NOK;
    //choose mode
     #if TIMER0_COMPARE_OUTPUT_MODE == NORMAL_PORT_OPERATION
        TCCR0 &= ~(1<<TCCR0_COM00);
        TCCR0 &= ~(1<<TCCR0_COM01);
    #endif

    #if TIMER0_WAVEFORM_GENERATION_MODE == NORMAL
        TCCR0 &= ~(1<<TCCR0_WGM00);
        TCCR0 &= ~(1<<TCCR0_WGM01);    
    #elif TIMER0_WAVEFORM_GENERATION_MODE == PWM_PHASE_CORRECT
        TCCR0 &= ~(1<<TCCR0_WGM01);
        TCCR0 |= (1<<TCCR0_WGM00);
        #if TIMER0_COMPARE_OUTPUT_MODE == NON_INVERTING_SET_ON_COMP
            TCCR0 &= ~(1<<TCCR0_COM00);
            TCCR0 |= (1<<TCCR0_COM01);
        #elif TIMER0_COMPARE_OUTPUT_MODE == INVERTING_CLR_ON_COMP
            TCCR0 |= (1<<TCCR0_COM00);
            TCCR0 &= ~(1<<TCCR0_COM01);
        #endif
    #elif TIMER0_WAVEFORM_GENERATION_MODE == CTC
        TCCR0 |= (1<<TCCR0_WGM01);
        TCCR0 &= ~(1<<TCCR0_WGM00);
            
        #if TIMER0_COMPARE_OUTPUT_MODE == TOGGLE_OC0_ON_COMPARE_MATCH
                //CTC MODE
                TCCR0 |= (1<<TCCR0_COM00);
                TCCR0 &= ~(1<<TCCR0_COM01);
        #elif TIMER0_COMPARE_OUTPUT_MODE == CLEAR_OC0_ON_COMPARE_MATCH
                //CTC MODE
                TCCR0 &= ~(1<<TCCR0_COM00);
                TCCR0 |= (1<<TCCR0_COM01);
        #elif TIMER0_COMPARE_OUTPUT_MODE == SET_OC0_ON_COMPARE_MATCH
                //CTC MODE
                TCCR0 |= (1<<TCCR0_COM00);
                TCCR0 |= (1<<TCCR0_COM01);
        #endif
    #elif TIMER0_WAVEFORM_GENERATION_MODE == FAST_PWM
        TCCR0 |= (1<<TCCR0_WGM00);
        TCCR0 |= (1<<TCCR0_WGM01);
        #if TIMER0_COMPARE_OUTPUT_MODE == NON_INVERTING_CLR_ON_COMP
            TCCR0 |= (1<<TCCR0_COM01);
            TCCR0 &= ~(1<<TCCR0_COM00);
        #elif TIMER0_COMPARE_OUTPUT_MODE == INVERTING_SET_ON_COMP
            TCCR0 |= (1<<TCCR0_COM00);
            TCCR0 |= (1<<TCCR0_COM01);
        #endif
    #endif

   

    #if TIMER0_INTERRUPT_ENABLE == OCIE0
        TIMSK |= (1<<OCIE0);
    #elif TIMER0_INTERRUPT_ENABLE == TOIE0
        TIMSK |= (1<<TOIE0);
    #elif TIMER0_INTERRUPT_ENABLE == NO_INTERRUTP
        TIMSK &= ~(1<<OCIE0);
        TIMSK &= ~(1<<TOIE0);
    #endif


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
    #elif TIMER0_PRESCALER == PRESCALER_256
        TCCR0 &= ~(1<<TCCR0_CS00);
        TCCR0 &= ~(1<<TCCR0_CS01);
        TCCR0 |= (1<<TCCR0_CS02);
    #elif TIMER0_PRESCALER == PRESCALER_1024
        TCCR0 |= (1<<TCCR0_CS00);
        TCCR0 &= ~(1<<TCCR0_CS01);
        TCCR0 |= (1<<TCCR0_CS02);
    #elif TIMER0_PRESCALER == EXTERNAL_CLOCK_SOURCE_FALLING_EDGE
        TCCR0 &= ~(1<<TCCR0_CS00);
        TCCR0 |= (1<<TCCR0_CS01);
        TCCR0 |= (1<<TCCR0_CS02);
    #elif TIMER0_PRESCALER == EXTERNAL_CLOCK_SOURCE_RISING_EDGE
        TCCR0 |= (1<<TCCR0_CS00);
        TCCR0 |= (1<<TCCR0_CS01);
        TCCR0 |= (1<<TCCR0_CS02);
    #endif

    return local_errorstate;
}
ES_t TIMER0_setCompareValue(u8 Copy_u8Value){
    ES_t local_errorstate = ES_NOK;
    OCR0 = Copy_u8Value;
    local_errorstate = ES_OK;
    return local_errorstate;
}
ES_t TIMER0_enuSetPreload(u8 Copy_u8Value){
    ES_t local_errorstate = ES_NOK;
    TCNT0 = Copy_u8Value;
    local_errorstate = ES_OK;
    return local_errorstate;

}
ES_t TIMER0_enuSetSyncDelay(u32 Copy_u8Time){
    ES_t local_errorstate = ES_NOK;
    TIMSK &= ~(1<<TOIE0);
    f32 overflowTime = (256.0*(f32)TIMER0_PRESCALER) / (f32)F_CPU ;
    f32 NumOVF = Copy_u8Time/overflowTime;
    if(NumOVF - (u32)NumOVF != 0.0){
        u32 NumOVF_int = (u32)NumOVF +1 ;
        NumOVF =NumOVF-(u32)NumOVF;
        u8 preload = 256 - (NumOVF*256);
        TCNT0 =preload;
        while(NumOVF_int > 0){
            while(((TIFR>>TOV0)&1 )==0);
            TIFR |= (1<<TOV0);
            NumOVF_int--;
        }
    
    }else{
        u32 NumOVF_int = (u32)NumOVF;
        while(NumOVF_int>0){
            while(((TIFR>>TOV0)&1) ==0);
            TIFR |= (1<<TOV0);
        }
    }
    
   return local_errorstate;
}
ES_t TIMER0_enuSetASyncDelay(u32 Copy_u8Time,void (*func)(void),void *Copy_pvidParameter){
    ES_t local_errorstate = ES_NOK;
   if(func != NULL){
        TIMER0_callBackPtr = func;
        TIMER0_callBackParameter = Copy_pvidParameter;
        local_errorstate = ES_OK;
    }else{
        local_errorstate = ES_NULL_POINTER;
    }
    f32 overflowTime = (256.0* TIMER0_PRESCALER) / F_CPU ;
    f32 NumOVF = Copy_u8Time/overflowTime;
    if(NumOVF - (u32)NumOVF !=0.0){
        u32 NumOVF_int = (u32)NumOVF +1 ;
        NumOVF =NumOVF-(u32)NumOVF;
        u8 preload = 256*(1-NumOVF);
        gNum_OVF = NumOVF_int;
        gPreload =preload;
        TCNT0 =preload;
    }else{
        gNum_OVF=(u32)NumOVF;   
    }
    TIMSK |= (1<<TOIE0);
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
        static u32 counts =0;
        counts++;
        if(counts == 1000){
            TIMER0_callBackPtr(TIMER0_callBackParameter);
            counts=0;
        }
        
    }
}

ISR(VECT_TIMER0_OVF){
    if(TIMER0_callBackPtr != NULL){
        static u32 counts = 0;
        counts ++;
        if(counts == gNum_OVF){
            TCNT0 =gPreload;
            TIMER0_callBackPtr(TIMER0_callBackParameter);

            counts =0;
        }
    }
}