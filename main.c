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
#include "HAL/KEYPAD/KEYPAD_Int.h"
#include "HAL/KEYPAD/KEYPAD_config.h"

#include <util/delay.h>

// extern SW_t Switch_AstrSwitchState[SW_NUM];
//  extern LED_t LED_AstrLEDState[LED_NUM];
// extern SEVEN_SEGMENT_t SS_LT_AstrConfig[SEG_NUM];
int main()
{
    
    // array of patterns for custom character on lcd
    LCD_enuInit();
    KEYPAD_Init();
    
    LCD_enuSendCommand(0x80);

    u8 local_u8PressedKey = KEYPAD_NO_PRESSED_KEY;
    
    while (1)
    {
        do{
            KEYPAD_GetPressedKey(&local_u8PressedKey);
        }
        while(local_u8PressedKey == KEYPAD_NO_PRESSED_KEY);
        LCD_enuDisplayChar(local_u8PressedKey);
    }
}
