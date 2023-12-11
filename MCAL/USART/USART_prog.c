

#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"

#include "USART_config.h"
#include "USART_priv.h"


ES_t USART_enuInit(void){
    ES_t Local_enuErrorState = ES_NOK;
    //NORMAL SPEED OR DOUBLE SPEED
    #if USART_SPEED == USART_SPEED_DOUBLE
        UCSRA |= (1<< UCSRA_U2X);
    #elif USART_SPEED == USART_SPEED_NORMAL
        UCSRA &= ~(1<< UCSRA_U2X);
    #else
        #error "Wrong Speed Configuration"
    #endif

    //direction configuration
    #if USART_DIRECTION == USART_DIRECTION_BOTH
        UCSRB |= (1<<UCSRB_RXEN) | (1<<UCSRB_TXEN);
    #elif USART_DIRECTION == USART_DIRECTION_TX
        UCSRB |= (1<<UCSRB_TXEN);
    #elif USART_DIRECTION == USART_DIRECTION_RX
        UCSRB |= (1<<UCSRB_RXEN);
    #else
        #error "Wrong Direction Configuration"
    #endif
    #if USART_INTERRUPT == USART_INTERRUPT_INTERRUPT
        UCSRB |= (1<<UCSRB_RXCIE) | (1<<UCSRB_TXCIE) | (1<<UCSRB_UDRIE);
    #elif USART_INTERRUPT == USART_INTERRUPT_POLLING
        UCSRB &= ~((1<<UCSRB_RXCIE) | (1<<UCSRB_TXCIE) | (1<<UCSRB_UDRIE));
    #else
        #error "Wrong Interrupt Configuration"
    #endif

    u8 local_UCSRC = 0x80;
    //mode configuration
    #if USART_MODE == USART_MODE_ASYNC
        local_UCSRC &= ~(1<<UCSRC_UMSEL);
    #elif USART_MODE == USART_MODE_SYNC
        local_UCSRC |= (1<<UCSRC_UMSEL);
    #else
        #error "Wrong Mode Configuration"
    #endif


    //parity configuration
    #if USART_PARITY == USART_PARITY_DISABLED
        local_UCSRC &= ~((1<<UCSRC_UPM1) | (1<<UCSRC_UPM0));
    #elif USART_PARITY == USART_PARITY_EVEN
        local_UCSRC &= ~(1<<UCSRC_UPM0);
        local_UCSRC |= (1<<UCSRC_UPM1);
    #elif USART_PARITY == USART_PARITY_ODD
        local_UCSRC |= (1<<UCSRC_UPM0);
        local_UCSRC |= (1<<UCSRC_UPM1);
    #endif

     //stop bits configuration
    #if USART_STOPBITS == USART_STOPBITS_1 
        local_UCSRC &= ~(1<<UCSRC_USBS);
    #elif USART_STOPBITS == USART_STOPBITS_2
        local_UCSRC |= (1<<UCSRC_USBS);
    #else
        #error "Wrong Stop Bits Configuration"
    #endif
    
    //character size configuration
    #if USART_DATA_SIZE == USART_DATA_SIZE_5
        local_UCSRC &= ~(1<<UCSRC_UCSZ0);
        local_UCSRC &= ~(1<<UCSRC_UCSZ1);
        UCSRB &= ~(1<<UCSRB_UCSZ2);
    #elif USART_DATA_SIZE == USART_DATA_SIZE_6
        local_UCSRC |= (1<<UCSRC_UCSZ0);
        local_UCSRC &= ~(1<<UCSRC_UCSZ1);
        UCSRB &= ~(1<<UCSRB_UCSZ2);
    #elif USART_DATA_SIZE == USART_DATA_SIZE_7
        local_UCSRC &= ~(1<<UCSRC_UCSZ0);
        local_UCSRC |= (1<<UCSRC_UCSZ1);
        UCSRB &= ~(1<<UCSRB_UCSZ2);
    #elif USART_DATA_SIZE == USART_DATA_SIZE_8
        local_UCSRC |= (1<<UCSRC_UCSZ0);
        local_UCSRC |= (1<<UCSRC_UCSZ1);
        UCSRB &= ~(1<<UCSRB_UCSZ2);
    #elif USART_DATA_SIZE == USART_DATA_SIZE_9
        local_UCSRC |= (1<<UCSRC_UCSZ0);
        local_UCSRC |= (1<<UCSRC_UCSZ1);
        UCSRB |= (1<<UCSRB_UCSZ2);
    #else
        #error "Wrong Character Size Configuration"
    #endif
    
    //clock polarity configuration
    #if USART_CLOCK_POL == USART_CLOCK_POL_RISING_TX_FALLING_RX
        local_UCSRC &= ~(1<<UCSRC_UCPOL);
    #elif USART_CLOCK_POL == USART_CLOCK_POL_FALLING_TX_RISING_RX
        local_UCSRC |= (1<<UCSRC_UCPOL);
    #else
        #error "Wrong Clock Polarity Configuration"
    #endif
    UCSRC = local_UCSRC;

    u16 Local_u16UBRR = BAUD(USART_BAUDRATE);
    UBRRL = (u8)Local_u16UBRR;
    UBRRH |= (u8)(Local_u16UBRR>>8);

    return Local_enuErrorState;
}
ES_t USART_enuSendChar(u8 Copy_u8Char){
    ES_t Local_enuErrorState = ES_NOK;
    #if USART_INTERRUPT == USART_INTERRUPT_POLLING
        while(!(UCSRA & (1<<UCSRA_UDRE)));
        UDR = Copy_u8Char;
    #elif USART_INTERRUPT == USART_INTERRUPT_INTERRUPT
        UDR = Copy_u8Char;
    #endif
    return Local_enuErrorState;
}
ES_t USART_enuReceiveChar(u8 * Copy_pu8Char){

    ES_t Local_enuErrorState = ES_NOK;
     if(Copy_pu8Char != NULL){
        #if USART_INTERRUPT == USART_INTERRUPT_POLLING
     
        while(!(UCSRA & (1<<UCSRA_RXC)));
        *Copy_pu8Char=UDR;
        Local_enuErrorState = ES_OK;
        #elif USART_INTERRUPT == USART_INTERRUPT_INTERRUPT
            UDR = Copy_u8Char;
        #endif
     }else {
         Local_enuErrorState = ES_NULL_POINTER;
     }
    return Local_enuErrorState;
}
ES_t USART_enuSendString(const char * Copy_pCString){
    ES_t Local_enuErrorState = ES_NOK;
    while(*Copy_pCString != '\0'){
       while(!(UCSRA & (1<<UCSRA_UDRE)));
        UDR = *Copy_pCString;
        Copy_pCString++;
    }
    return Local_enuErrorState;
}
ES_t USART_enuReceiveString(char * Copy_pCString){
    ES_t Local_enuErrorState = ES_NOK;
    u8 local_u8data = 0 ,local_index = 0;
    while(1){
        while(!(UCSRA & (1<<UCSRA_RXC)));
        local_u8data = UDR;
        if(local_u8data == '\r' || local_u8data == '\n'){
            Copy_pCString[local_index] = '\0';
            break;
        }
        Copy_pCString[local_index] = local_u8data;
        local_index++;
    }
    return Local_enuErrorState;
}