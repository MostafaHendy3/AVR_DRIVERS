#ifndef TIMER_INT_H_
#define TIMER_INT_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

ES_t TIMER0_init(void);
ES_t TIMER0_callBack(void (*func)(void),void *Copy_pvidParameter);

#endif /* TIMER_INT_H_ */
