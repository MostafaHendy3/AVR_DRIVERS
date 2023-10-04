#include "LIB/stdTypes.h"
#include "LIB/errorStates.h"

#include "MCAL/DIO/DIO_int.h"
#include "HAL/Switch/Switch_int.h"
#include "HAL/Switch/Switch_config.h"
#include "HAL/LED/LED_int.h"
#include "HAL/LED/LED_config.h"
#include "HAL/Seven_Segement/Seven_Segement_int.h"
#include "HAL/Seven_Segement/Seven_Segement_config.h"


#include <util/delay.h>

// extern SW_t Switch_AstrSwitchState[SW_NUM];
// extern LED_t LED_AstrLEDState[LED_NUM];

int main()
{
    SevenSegement_Init();

    while (1)
    {
        for(u8 i = 0; i < 10; i++)
        {
            SevenSegement_enuDisplayNum(i);
            _delay_ms(1000);
        }
        SevenSegement_enuClear();
        _delay_ms(1000);
    }
}
