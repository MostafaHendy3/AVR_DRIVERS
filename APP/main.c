#include "../LIB/stdTypes.h"
#include "../LIB/errorStates.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_Int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/ADC/ADC_Int.h"

#include "../HAL/LCD/LCD_config.h"
#include "../HAL/LCD/LCD_Int.h"

#include "../HAL/lm35/lm35_int.h"

#include <util/delay.h>
//extern EXTI_t EXTI_tConfig[3];

//chain of ADC DATA
u8 adcResults[4]={0,0,0,0};
ADC_chain_t ADC_chain[4] = {{0,&adcResults[0]},
                                {1,&adcResults[1]},
                                {2,&adcResults[2]},
                                {4,&adcResults[3]}};

u8 flag = 0;
void chain_read(void *p)
{        
    LCD_enuGoHome();
    LCD_enuDisplayIntegerNumber(adcResults[0]);
    LCD_enuDisplayChar(' ');
    LCD_enuDisplayIntegerNumber(adcResults[1]);
    LCD_enuDisplayChar(' ');
    LCD_enuDisplayIntegerNumber(adcResults[2]);
    LCD_enuDisplayChar(' ');
    LCD_enuDisplayIntegerNumber(adcResults[3]);   
}

u8 readings = 0;
void read(void *p)
{        
    LCD_enuGoHome();
    LCD_enuDisplayIntegerNumber(*(u8 *)p);  
}

int main()
{
    u8 lm35 = 0;
    LM35_Init();
    LCD_enuInit();
    LCD_enuClear();
    /*
        ADC * 
    */
    while (1)
    {
        LM35_GetTemp(&lm35);
        LCD_enuGoHome();
        LCD_enuDisplayIntegerNumber(lm35);
   
    
    }

    
}

/* ADC 
     // Asynchronous    
    //ADC_enuStartConversion_ASync(0,&readings,&read,(void *)&readings);
    
    // Chain of ADC
    // ADC_enuStartChainConversion(&ADC_chain,4,&chain_read,(void *)&adcResults);

    // Synchronous
    // ADC_enuStartConversion_Sync(0,&readings);
    // DIO_enuSetPortDirection(DIO_u8PORTB, 0xff);
    // LCD_enuDisplayIntegerNumber(readings);

*/