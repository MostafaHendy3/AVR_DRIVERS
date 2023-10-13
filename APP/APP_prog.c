#include "../LIB/stdTypes.h"
#include "../LIB/errorStates.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_config.h"
#include "../HAL/KEYPAD/KEYPAD_Int.h"
#include "../HAL/KEYPAD/KEYPAD_config.h"
#include "APP_priv.h"
#include "APP_config.h"
#include <util/delay.h>

u32 Global_u32Operand1 = 0;
u32 Global_u32Operand2 = 0;
u8 Global_u32Operator = 0;
f32 Result = 0;
u8 EqualPressed = 0;
u8 ClearFlag = 0;

ES_t APP_enuInit(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    LCD_enuInit();
    KEYPAD_Init();
    OpenScreen();
    _delay_ms(1000);
    LCD_enuClear();
    return Local_enuErrorState;
}
ES_t APP_enuStart(void)
{
    ES_t Local_enuErrorState = ES_NOK;

    u8 local_u8PressedKey;

    while (EqualPressed == 0)
    {
        do
        {
            KEYPAD_GetPressedKey(&local_u8PressedKey);
        } while (local_u8PressedKey == KEYPAD_NO_PRESSED_KEY);
        // check if the pressed key is equal
        if (local_u8PressedKey == '=')
        {
            LCD_enuDisplayChar(local_u8PressedKey);
            CalcResult();
            View_On_Screen(Result, (Result - (u32)Result) * 1000);
            CLEAR();
            ClearFlag = 1;
            break;
        }
        // check if the pressed key is a number
        else if (local_u8PressedKey <= '9' && local_u8PressedKey >= '0')
        {
            /*Clear Past operation*/
            if (ClearFlag == 1)
            {
                LCD_enuClear();
                ClearFlag = 0;
            }
            /* Differentiate between operand one and two */
            if (Global_u32Operator == 0)
            {
                /* To avoid the first operand to be zero */
                if (Global_u32Operand1 == 0)
                {
                    LCD_enuClear();
                }
                Global_u32Operand1 = Global_u32Operand1 * 10 + (local_u8PressedKey - '0');
            }
            else
            {
                /* To avoid the second operand to be zero */

                Global_u32Operand2 = Global_u32Operand2 * 10 + (local_u8PressedKey - '0');
            }
            LCD_enuDisplayChar(local_u8PressedKey);
        }
        // check if the pressed key is Clear
        else if (local_u8PressedKey == 'C')
        {
            LCD_enuClear();
            CLEAR();
        }
        // check if the pressed key is an operator
        else
        {
            LCD_enuDisplayChar(local_u8PressedKey);
            /*Clear Past operation*/
            if (ClearFlag == 1)
            {
                LCD_enuClear();
                ClearFlag = 0;
            }
            EqualPressed = 0;
            Global_u32Operator = local_u8PressedKey;
        }
    }
    
    return Local_enuErrorState;
}

static void CalcResult(void)
{
    switch (Global_u32Operator)
    {
    case '+':
        Result = Global_u32Operand1 + Global_u32Operand2;
        break;
    case '-':
        Result = Global_u32Operand1 - Global_u32Operand2;
        break;
    case '*':
        Result = Global_u32Operand1 * Global_u32Operand2;
        break;
    case '/':
        if(Global_u32Operand2 == 0){
            ErrorScreen();
            break;
        }
        Result = Global_u32Operand1 / (f32)Global_u32Operand2;
        break;
    default:
        break;
    }
}
static void View_On_Screen(u32 local_u8INT_Part, u32 local_u8FLOAT_Part)
{
    u8 local_line2 = 0xCF;

    while (local_u8FLOAT_Part >= 1)
    {
        LCD_enuSendCommand(local_line2);
        u32 digit1 = local_u8FLOAT_Part % 10;
        LCD_enuDisplayChar(digit1 + '0'); // Print the digit
        local_u8FLOAT_Part /= 10;
        local_line2--;
    }
    LCD_enuSendCommand(local_line2);
    LCD_enuDisplayChar('.');
    local_line2--;

    while (local_u8INT_Part >= 1)
    {
        LCD_enuSendCommand(local_line2);
        u32 digit = local_u8INT_Part % 10;
        LCD_enuDisplayChar(digit + '0'); // Print the digit
        local_u8INT_Part /= 10;
        local_line2--;
    }
    LCD_enuGoHome();
}
static void CLEAR(void)
{
    Global_u32Operand1 = 0;
    Global_u32Operand2 = 0;
    Global_u32Operator = 0;
    Result = 0;
    EqualPressed = 0;
    ClearFlag = 0;
}
static void ErrorScreen(void)
{
    LCD_enuClear();
    LCD_enuGoHome();
    char *Error = "Error";
    u8 i = 0;
    while (Error[i] != '\0')
    {
        LCD_enuDisplayChar(Error[i]);
        i++;
    }
}
static void OpenScreen(void)
{
    LCD_enuClear();
    LCD_enuGoHome();
    char *OPEN = "Hello Calculator";
    u8 i = 0;
    while (OPEN[i] != '\0')
    {
        LCD_enuDisplayChar(OPEN[i]);
        i++;
    }
}