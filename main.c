#include "LIB/stdTypes.h"
#include "LIB/errorStates.h"

#include "MCAL/DIO/DIO_int.h"
#include "HAL/Switch/Switch_int.h"
#include "HAL/Switch/Switch_config.h"
#include "HAL/LED/LED_int.h"
#include "HAL/SS_LT/SS_LT_Int.h"
#include "HAL/SS_LT/SS_LT_Config.h"

#include <util/delay.h>

// extern SW_t Switch_AstrSwitchState[SW_NUM];
// extern LED_t LED_AstrLEDState[LED_NUM];
extern SEVEN_SEGMENT_t SS_LT_AstrConfig[SEG_NUM];
int main()
{
    SevenSegement_Init(SS_LT_AstrConfig);
    while (1)
    {
        for (int i = 0; i < 10; i++)
        {
            SevenSegement_enuDisplayNum(1, i);
            _delay_ms(500);
        }
                    _delay_ms(500);
        SevenSegement_enuClear(1);
                    _delay_ms(500);

    }
}
