//file guard
#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

#define LED_NUM 2
typedef struct{
    u8 LED_u8Port;
    u8 LED_u8Pin;
    u8 LED_u8Connection;
    u8 LED_u8InitStatus;
}LED_t;

#endif /* LED_PRIV_H_ */