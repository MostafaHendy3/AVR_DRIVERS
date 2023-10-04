
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "Seven_Segement_priv.h"
#include "Seven_Segement_config.h"

ES_t SevenSegement_Init(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    u32 Local_Check = 0;
    Local_Check = DIO_enuSetPinDirection(SEG_APORT, SEG_APIN, DIO_u8OUTPUT);
    Local_Check |= (DIO_enuSetPinDirection(SEG_BPORT, SEG_BPIN, DIO_u8OUTPUT) << 3);
    Local_Check |= (DIO_enuSetPinDirection(SEG_CPORT, SEG_CPIN, DIO_u8OUTPUT) << 6);
    Local_Check |= (DIO_enuSetPinDirection(SEG_DPORT, SEG_DPIN, DIO_u8OUTPUT) << 9);
    Local_Check |= (DIO_enuSetPinDirection(SEG_EPORT, SEG_EPIN, DIO_u8OUTPUT) << 12);
    Local_Check |= (DIO_enuSetPinDirection(SEG_FPORT, SEG_FPIN, DIO_u8OUTPUT) << 15);
    Local_Check |= (DIO_enuSetPinDirection(SEG_GPORT, SEG_GPIN, DIO_u8OUTPUT) << 18);

#if SEG_CMN <= DIO_u8PIN7 && SEG_CMN_PORT <= DIO_u8PORTD
    DIO_enuSetPinDirection(SEG_COMPORT, SEG_COM, DIO_u8OUTPUT);
#elif SEG_CMN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED

#else
#error "your Common Pin has a wrong selection"
#endif

#if SEG_DOT <= DIO_u8PIN7 && SEG_DOT_PORT <= DIO_u8PORTD
    DIO_enuSetPinDirection(SEG_DOTPORT, SEG_DOT, DIO_u8OUTPUT);
#elif SEG_DOT == NOT_CONNECTED || SEG_DOT_PORT == NOT_CONNECTED

#else
#error "your DOT Pin has a wrong selection"
#endif

    u8 Local_Iterator = 0;
    for (Local_Iterator = 0; Local_Iterator < 7; Local_Iterator++)
    {
        if (((Local_Check >> (Local_Iterator * 3)) & 7) != ES_OK)
        {
            return Local_enuErrorState;
        }
    }

    return Local_enuErrorState;
}
ES_t SevenSegement_enuDisplayNum(u8 Copy_u8Number)
{
    ES_t Local_enuErrorState = ES_NOK;
    if (Copy_u8Number < 10)
    {

        #if SEG_TYPE == COMMON_CATHODE
                DIO_enuSetPinValue(SEG_APORT, SEG_APIN, ((Seg_Au8NumberDisplay[Copy_u8Number] >> 0) & 1));
                DIO_enuSetPinValue(SEG_BPORT, SEG_BPIN, ((Seg_Au8NumberDisplay[Copy_u8Number] >> 1) & 1));
                DIO_enuSetPinValue(SEG_CPORT, SEG_CPIN, ((Seg_Au8NumberDisplay[Copy_u8Number] >> 2) & 1));
                DIO_enuSetPinValue(SEG_DPORT, SEG_DPIN, ((Seg_Au8NumberDisplay[Copy_u8Number] >> 3) & 1));
                DIO_enuSetPinValue(SEG_EPORT, SEG_EPIN, ((Seg_Au8NumberDisplay[Copy_u8Number] >> 4) & 1));
                DIO_enuSetPinValue(SEG_FPORT, SEG_FPIN, ((Seg_Au8NumberDisplay[Copy_u8Number] >> 5) & 1));
                DIO_enuSetPinValue(SEG_GPORT, SEG_GPIN, ((Seg_Au8NumberDisplay[Copy_u8Number] >> 6) & 1));
        #elif SEG_TYPE == COMMON_ANODE
                DIO_enuSetPinValue(SEG_APORT, SEG_APIN, !((Seg_Au8NumberDisplay[Copy_u8Number] >> 0) & 1));
                DIO_enuSetPinValue(SEG_BPORT, SEG_BPIN, !((Seg_Au8NumberDisplay[Copy_u8Number] >> 1) & 1));
                DIO_enuSetPinValue(SEG_CPORT, SEG_CPIN, !((Seg_Au8NumberDisplay[Copy_u8Number] >> 2) & 1));
                DIO_enuSetPinValue(SEG_DPORT, SEG_DPIN, !((Seg_Au8NumberDisplay[Copy_u8Number] >> 3) & 1));
                DIO_enuSetPinValue(SEG_EPORT, SEG_EPIN, !((Seg_Au8NumberDisplay[Copy_u8Number] >> 4) & 1));
                DIO_enuSetPinValue(SEG_FPORT, SEG_FPIN, !((Seg_Au8NumberDisplay[Copy_u8Number] >> 5) & 1));
                DIO_enuSetPinValue(SEG_GPORT, SEG_GPIN, !((Seg_Au8NumberDisplay[Copy_u8Number] >> 6) & 1));
        #else
        #error "your Seven Segement Type has a wrong selection"
        #endif
    }else{
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }

    return Local_enuErrorState;
}
ES_t SevenSegement_enuEnableCommon(void)
{
    ES_t Local_enuErrorState = ES_NOK;

    #if SEG_CMN <= DIO_u8PIN7 && SEG_CMN_PORT <= DIO_u8PORTD
        #if SEG_TYPE == COMMON_CATHODE
            Local_enuErrorState =DIO_enuSetPinValue(SEG_COMPORT, SEG_COM, DIO_u8LOW);
        #elif SEG_TYPE == COMMON_ANODE
            Local_enuErrorState=DIO_enuSetPinValue(SEG_COMPORT, SEG_COM, DIO_u8HIGH);
        
        #else
        #error "your Seven Segement Type has a wrong selection"
        #endif
    #elif SEG_CMN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED

    #else
    #error "your Common Pin has a wrong selection"
    #endif
    return Local_enuErrorState;
}
ES_t SevenSegement_enuDisableCommon(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    #if SEG_CMN <= DIO_u8PIN7 && SEG_CMN_PORT <= DIO_u8PORTD
        #if SEG_TYPE == COMMON_CATHODE
            Local_enuErrorState =DIO_enuSetPinValue(SEG_COMPORT, SEG_COM, DIO_u8HIGH);
        #elif SEG_TYPE == COMMON_ANODE
            Local_enuErrorState=DIO_enuSetPinValue(SEG_COMPORT, SEG_COM, DIO_u8LOW);
        
        #else
        #error "your Seven Segement Type has a wrong selection"
        #endif
    #elif SEG_CMN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED

    #else
    #error "your Common Pin has a wrong selection"
    #endif

    return Local_enuErrorState;
}
ES_t SevenSegement_enuEnableDot(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    #if SEG_DOT <= DIO_u8PIN7 && SEG_DOTPORT <= DIO_u8PORTD
        #if SEG_TYPE == COMMON_CATHODE
            Local_enuErrorState =DIO_enuSetPinValue(SEG_DOTPORT, SEG_DOT, DIO_u8HIGH);
        #elif SEG_TYPE == COMMON_ANODE
            Local_enuErrorState=DIO_enuSetPinValue(SEG_DOTPORT, SEG_DOT, DIO_u8LOW);
        
        #else
        #error "your Seven Segement Type has a wrong selection"
        #endif
    #elif SEG_DOT == NOT_CONNECTED || SEG_DOTPORT == NOT_CONNECTED

    #else
    #error "your Common Pin has a wrong selection"
    #endif

    return Local_enuErrorState;
}
ES_t SevenSegement_enuDisableDot(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    #if SEG_DOT <= DIO_u8PIN7 && SEG_DOTPORT <= DIO_u8PORTD
        #if SEG_TYPE == COMMON_CATHODE
            Local_enuErrorState =DIO_enuSetPinValue(SEG_DOTPORT, SEG_DOT, DIO_u8LOW);
        #elif SEG_TYPE == COMMON_ANODE
            Local_enuErrorState=DIO_enuSetPinValue(SEG_DOTPORT, SEG_DOT, DIO_u8HIGH);
        
        #else
        #error "your Seven Segement Type has a wrong selection"
        #endif
    #elif SEG_DOT == NOT_CONNECTED || SEG_DOTPORT == NOT_CONNECTED

    #else
    #error "your Common Pin has a wrong selection"
    #endif

    return Local_enuErrorState;
}
ES_t SevenSegement_enuClear(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    

        #if SEG_TYPE == COMMON_CATHODE
                DIO_enuSetPinValue(SEG_APORT, SEG_APIN, DIO_u8LOW);
                DIO_enuSetPinValue(SEG_BPORT, SEG_BPIN, DIO_u8LOW);
                DIO_enuSetPinValue(SEG_CPORT, SEG_CPIN, DIO_u8LOW);
                DIO_enuSetPinValue(SEG_DPORT, SEG_DPIN, DIO_u8LOW);
                DIO_enuSetPinValue(SEG_EPORT, SEG_EPIN, DIO_u8LOW);
                DIO_enuSetPinValue(SEG_FPORT, SEG_FPIN, DIO_u8LOW);
                DIO_enuSetPinValue(SEG_GPORT, SEG_GPIN, DIO_u8LOW);
        #elif SEG_TYPE == COMMON_ANODE
                DIO_enuSetPinValue(SEG_APORT, SEG_APIN, DIO_u8HIGH);
                DIO_enuSetPinValue(SEG_BPORT, SEG_BPIN, DIO_u8HIGH);
                DIO_enuSetPinValue(SEG_CPORT, SEG_CPIN, DIO_u8HIGH);
                DIO_enuSetPinValue(SEG_DPORT, SEG_DPIN, DIO_u8HIGH);
                DIO_enuSetPinValue(SEG_EPORT, SEG_EPIN, DIO_u8HIGH);
                DIO_enuSetPinValue(SEG_FPORT, SEG_FPIN, DIO_u8HIGH);
                DIO_enuSetPinValue(SEG_GPORT, SEG_GPIN, DIO_u8HIGH);
        #else
        #error "your Seven Segement Type has a wrong selection"
        #endif
   

    return Local_enuErrorState;

}
