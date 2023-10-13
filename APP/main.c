#include "../LIB/stdTypes.h"
#include "../LIB/errorStates.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_config.h"
#include "../HAL/KEYPAD/KEYPAD_Int.h"
#include "../HAL/KEYPAD/KEYPAD_config.h"

#include "APP_Int.h"
#include "APP_Config.h"

#include <util/delay.h>

int main()
{
    APP_enuInit();

    while (1)
    {
        APP_enuStart();
    }
}

void ReadOperand(){
    
}
