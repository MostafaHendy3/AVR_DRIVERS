#ifndef TIMER_INT_H_
#define TIMER_INT_H_

ES_t TIMER0_init(void);
ES_t TIMER0_enuSetPreload(u8 Copy_u8Value);
ES_t TIMER0_enuSetASyncDelay(u32 Copy_u8Time,void (*func)(void),void *Copy_pvidParameter);
ES_t TIMER0_enuSetSyncDelay(u32 Copy_u8Time); 
ES_t TIMER0_GeneratePWM(u8 Copy_u8DutyCycle);
ES_t TIMER0_setCompareValue(u8 Copy_u8Value);
ES_t TIMER0_callBack(void (*func)(void),void *Copy_pvidParameter);

ES_t TIMER1_init(void);
ES_t TIMER1_GetTimerValue(u16 *Copy_pu16Value);
ES_t TIMER1_SetTimerValue(u16 Copy_u16Value);
ES_t TIMER1_callBack(void (*func)(void), void *Copy_pvidParameter);


#endif /* TIMER_INT_H_ */
