#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include "SPI_priv.h"
//mode configuration
#define SPI_MODE SLAVE_MODE
//DATA order Configuration
#define DATA_ORDER LSB_FIRST
//Clock polarity
#define CLOCK_POLARITY RISING_LEADING
//Clock Phase
#define CLOCK_PHASE SAMPLE_LEADING
//SPI Clock Rate Select
#define SPI_CLOCK_RATE F_SYS_16
//SPI Interrupt Enable
#define SPI_INTERRUPT_MODE SPI_INTERRUPT_DISABLE

#endif /* SPI_CONFIG_H_ */
