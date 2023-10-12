#include "LIB/stdTypes.h"
#include "LIB/errorStates.h"

#include "MCAL/DIO/DIO_int.h"
#include "HAL/Switch/Switch_int.h"
#include "HAL/Switch/Switch_config.h"
#include "HAL/LED/LED_int.h"
#include "HAL/SS_LT/SS_LT_Int.h"
#include "HAL/SS_LT/SS_LT_Config.h"
#include "HAL/LCD/LCD_int.h"
#include "HAL/LCD/LCD_config.h"

#include <util/delay.h>

// extern SW_t Switch_AstrSwitchState[SW_NUM];
//  extern LED_t LED_AstrLEDState[LED_NUM];
// extern SEVEN_SEGMENT_t SS_LT_AstrConfig[SEG_NUM];
int main()
{
    // array of patterns for custom character on lcd
    u8 customChar[] = {
        0B00000,
        0B00000,
        0B01010,
        0B00000,
        0B10001,
        0B01110,
        0B00000,
        0B00000
        };

    LCD_enuInit();
    LCD_enuSendCommand(0x40);
    for(u8 i = 0; i < 8; i++){
    LCD_enuDisplayChar(customChar[i]);
    }
    LCD_enuSendCommand(0x80);
    LCD_enuDisplayChar(0);
    while (1)
    {
    }
}
