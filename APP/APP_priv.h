#ifndef APP_PRIV_H_
#define APP_PRIV_H_
#define Equal_Pressed 1
#define Equal_NOT_Pressed 0
#define CLEARPressed 'C'
#define FloatingPointON 1
#define FloatingPointOFF 0


static void CalcResult(void);
static void View_On_Screen(s32 local_u8INT_Part, u32 local_u8FLOAT_Part);
static void CLEAR(void);
static void OpenScreen(void);
static void ErrorScreen(void);

#endif /* APP_PRIV_H_ */
