#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"

#include "SPI_priv.h"
#include "SPI_Config.h"

//  SPCR |= (1<<);
//  SPCR &= ~(1<<);
ES_t SPI_init(){
    ES_t local_errorState = ES_NOK;
    //selecting mode Master / Slave
    #if SPI_MODE == MASTER_MODE
        SPCR |= (1<<MSTR);
    #elif SPI_MODE == SLAVE_MODE
        SPCR &= ~(1<<MSTR);
    #endif

    #if DATA_ORDER == LSB_FIRST
        SPCR |= (1<<DORD);
    #elif DATA_ORDER == MSB_FIRST
        SPCR &= ~(1<<DORD);
    #endif

    #if CLOCK_POLARITY ==RISING_LEADING
        SPCR |= (1<<CPOL);
    #elif CLOCK_POLARITY == FALLING_LEADING
        SPCR &= ~(1<<CPOL);
    #endif

    #if CLOCK_PHASE ==SAMPLE_LEADING
        SPCR |= (1<<CPHA);
    #elif CLOCK_PHASE == SETUP_LEADING
        SPCR &= ~(1<<CPHA);
    #endif

    #if SPI_CLOCK_RATE == F_SYS_4
        SPCR &= ~(1<<SPR0);
        SPCR &= ~(1<<SPR1);
        SPSR &= ~(1<<SPI2X);
    #elif SPI_CLOCK_RATE == F_SYS_16
        SPCR |= (1<<SPR0);
        SPCR &= ~(1<<SPR1);
        SPSR &= ~(1<<SPI2X);
    #elif SPI_CLOCK_RATE == F_SYS_64
        SPCR &= ~(1<<SPR0);
        SPCR |= (1<<SPR1);
        SPSR &= ~(1<<SPI2X);
    #elif SPI_CLOCK_RATE == F_SYS_128
        SPCR |= (1<<SPR0);
        SPCR |= (1<<SPR1);
        SPSR &= ~(1<<SPI2X);
    #elif SPI_CLOCK_RATE == F_SYS_2
        SPCR &= ~(1<<SPR0);
        SPCR &= ~(1<<SPR1);
        SPSR |= (1<<SPI2X);
    #elif SPI_CLOCK_RATE == F_SYS_8
        SPCR |= (1<<SPR0);
        SPCR &= ~(1<<SPR1);
        SPSR |= (1<<SPI2X);
    #elif SPI_CLOCK_RATE == F_SYS_32
        SPCR &= ~(1<<SPR0);
        SPCR |= (1<<SPR1);
        SPSR |= (1<<SPI2X);
    #elif SPI_CLOCK_RATE == F_SYS_64
        SPCR |= (1<<SPR0);
        SPCR |= (1<<SPR1);
        SPSR |= (1<<SPI2X);
    #endif

    
    //enable interrupt
    #if SPI_INTERRUPT_MODE == SPI_INTERRUPT_ENABLE
        SPCR |= (1<<SPIE);
    #elif SPI_INTERRUPT_MODE == SPI_INTERRUPT_DISABLE
        SPCR &= ~(1<<SPIE);
    #endif
    //enable SPI
    SPCR |= (1<<SPE);
    local_errorState=ES_OK;
    return local_errorState;
}
ES_t SPI_sendData(u8 Copy_u8Data){
    ES_t local_errorState = ES_NOK;
     char flush_buffer;
	SPDR = Copy_u8Data;			
	while(!(SPSR & (1<<SPIF)));
	flush_buffer = SPDR;
    return local_errorState;
}
ES_t SPI_RecieveData(u8 *Copy_u8Data){
    ES_t local_errorState = ES_NOK;
    if(Copy_u8Data != NULL){
        while(!(SPSR & (1<<SPIF)));
        *Copy_u8Data = SPDR;
        local_errorState=ES_OK;
    }else{
        local_errorState=ES_NULL_POINTER;
    }
    local_errorState=ES_OK;
    return local_errorState;
}
