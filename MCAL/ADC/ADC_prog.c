#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "ADC_priv.h"
#include "ADC_config.h"
#include "../EXTI/EXTI_priv.h"
static void (*ADC_pfunISRFunction)(void *) =NULL;
static void *ADC_pvidISRParameter= NULL;
ES_t ADC_enuInit(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        #if REF_VOLTAGE == AVCC 
                ADMUX |= (1 << REFS0);
                ADMUX &= ~(1 << REFS1);
        #elif REF_VOLTAGE == AREF 
                ADMUX &= ~(1 << REFS0);
                ADMUX &= ~(1 << REFS1);
        #elif REF_VOLTAGE == INTERNAL 
                ADMUX |= (1 << REFS0);
                ADMUX |= (1 << REFS1);
        #else 
                #error "ADC Error ref voltage"
        #endif
                
        #if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT 
                ADMUX &= ~(1 << ADLAR);
        #elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT 
                ADMUX |= (1 << ADLAR);
        #else 
                #error "ADC Error Adjusment"
        #endif

        #if ADC_PRESCALER == DIVISION_FACTOR_2
                ADCSRA |= (1 << ADPS0);
                ADCSRA &= ~(1 << ADPS1);
                ADCSRA &= ~(1 << ADPS2);
        #elif ADC_PRESCALER == DIVISION_FACTOR_4
                ADCSRA &= ~(1 << ADPS0);
                ADCSRA |= (1 << ADPS1);
                ADCSRA &= ~(1 << ADPS2);
        #elif ADC_PRESCALER == DIVISION_FACTOR_8 
                ADCSRA |= (1 << ADPS0);
                ADCSRA |= (1 << ADPS1);
                ADCSRA &= ~(1 << ADPS2);
        #elif ADC_PRESCALER == DIVISION_FACTOR_16 
                ADCSRA &= ~(1 << ADPS0);
                ADCSRA &= ~(1 << ADPS1);
                ADCSRA |= (1 << ADPS2);
        #elif ADC_PRESCALER == DIVISION_FACTOR_32 
                ADCSRA |= (1 << ADPS0);
                ADCSRA &= ~(1 << ADPS1);
                ADCSRA |= (1 << ADPS2);
        #elif ADC_PRESCALER == DIVISION_FACTOR_64 
                ADCSRA &= ~(1 << ADPS0);
                ADCSRA |= (1 << ADPS1);
                ADCSRA |= (1 << ADPS2);
        #elif ADC_PRESCALER == DIVISION_FACTOR_128 
                ADCSRA |= (1 << ADPS0);
                ADCSRA |= (1 << ADPS1);
                ADCSRA |= (1 << ADPS2);
        #else 
                #error "ADC Error preScaler"
        #endif

        return Local_enuErrorState;
}
ES_t ADC_enuStartConversion(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA |= (1<<ADSC);
        return Local_enuErrorState;
}
ES_t ADC_enuPollingSystem(void)
{
        //wait on flag and clear it if it's high 
        //clear flag by writing one to flag
        ES_t Local_enuErrorState = ES_NOK;
        while((ADCSRA>>ADIF) == 0);
        ADCSRA |=(1<<ADIF);
        return Local_enuErrorState;
}
ES_t ADC_enuReadHighValue(u8 *Copy_pu8Value)
{
        ES_t Local_enuErrorState = ES_NOK;
        #if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
               *Copy_pu8Value = (ADCL>>2);
               *Copy_pu8Value|=(ADCH<<6);
        #elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
                *Copy_pu8Value = ADCH;
        #endif

        *Copy_pu8Value =ADCH;
        return Local_enuErrorState;
}
ES_t ADC_enuRead(u16 *Copy_pu16Value)
{
        ES_t Local_enuErrorState = ES_NOK;
        #if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
               *Copy_pu16Value = ADCL;
               *Copy_pu16Value|=((u16)ADCH<<8);
        #elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
                *Copy_pu16Value = (ADCL>>6);
                *Copy_pu16Value |= (ADCH<<2);
        #endif
        return Local_enuErrorState;
}
ES_t ADC_enuCallBack(void (*copy_pfunAppFun)(void *), void *copy_pvidAppParameter)
{
        ES_t Local_enuErrorState = ES_NOK;
        if(copy_pfunAppFun!=NULL){
                ADC_pfunISRFunction =copy_pfunAppFun;
                ADC_pvidISRParameter =copy_pvidAppParameter;
        }else{
                Local_enuErrorState = ES_NULL_POINTER;
        }
        return Local_enuErrorState;
}
ES_t ADC_enuEnableADC(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA |= (1<<ADEN);
        return Local_enuErrorState;
}
ES_t ADC_enuDisableADC(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA &= ~(1<<ADEN);
        return Local_enuErrorState;
}
ES_t ADC_enuEnableInterruptMode(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA |= (1<<ADIE);
        return Local_enuErrorState;
}
ES_t ADC_enuDisableInterruptMode(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA &= ~(1<<ADIE);
        return Local_enuErrorState;
}
ES_t ADC_enuSelectChannel(u8 copy_u8channelID)
{
        ES_t Local_enuErrorState = ES_NOK;
        if(copy_u8channelID > 7)
        {
                Local_enuErrorState = ES_OUT_OF_RANGE;
        }
        else
        {
                ADMUX &= 0xE0;
                ADMUX |= copy_u8channelID;
                Local_enuErrorState = ES_OK;
        }
        
        return Local_enuErrorState;
}
ES_t ADC_enuEnableTriggeringMode(u8 copy_u8TriggerSource)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA |= (1<<ADATE);
        switch (copy_u8TriggerSource)
        {
        case FREE_RUNNING_MODE:
                SFIOR &= ~(1<<ADTS0);
                SFIOR &= ~(1<<ADTS1);
                SFIOR &= ~(1<<ADTS2);
                break;
        case ANALOG_COMPARATOR:
                SFIOR |= (1<<ADTS0);
                SFIOR &= ~(1<<ADTS1);
                SFIOR &= ~(1<<ADTS2);
                break;
        case EXTERNAL_INTERRUPT_REQUEST_0:      
                SFIOR &= ~(1<<ADTS0);
                SFIOR |= (1<<ADTS1);
                SFIOR &= ~(1<<ADTS2);
                break;
        case TIMER_COUNTER0_COMPARE_MATCH:
                SFIOR |= (1<<ADTS0);
                SFIOR |= (1<<ADTS1);
                SFIOR &= ~(1<<ADTS2);
                break;
        case TIMER_COUNTER0_OVERFLOW:
                SFIOR &= ~(1<<ADTS0);
                SFIOR &= ~(1<<ADTS1);
                SFIOR |= (1<<ADTS2);
                break;
        case TIMER_COUNTER1_COMPARE_MATCH_B:
                SFIOR |= (1<<ADTS0);
                SFIOR &= ~(1<<ADTS1);
                SFIOR |= (1<<ADTS2);
                break;
        case TIMER_COUNTER1_OVERFLOW:
                SFIOR &= ~(1<<ADTS0);
                SFIOR |= (1<<ADTS1);
                SFIOR |= (1<<ADTS2);
                break;
        case TIMER_COUNTER1_CAPTURE_EVENT:
                SFIOR |= (1<<ADTS0);
                SFIOR |= (1<<ADTS1);
                SFIOR |= (1<<ADTS2);
                break;
        default:
        Local_enuErrorState = ES_OUT_OF_RANGE;
                break;
        }
        return Local_enuErrorState;
}
ES_t ADC_enuDisableTriggeringMode(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA &= ~(1<<ADATE);
        return Local_enuErrorState;
}

ISR(ADC_vect)
{
        if(ADC_pfunISRFunction != NULL)
        {
                ADC_pfunISRFunction(ADC_pvidISRParameter);
        }
}