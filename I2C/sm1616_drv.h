#ifndef  _SM1616_DRV_H
#define	 _SM1616_DRV_H

#include "main.h"

#define SM1616_SCL_Pin 						GPIO_PIN_4
#define SM1616_SCL_GPIO_Port 				GPIOC
#define SM1616_SDA_Pin 						GPIO_PIN_5
#define SM1616_SDA_GPIO_Port 				GPIOC

#define TRUE  1
#define FALSE 0

void SM1616_I2c_Init(void);
uint8_t SM1616_I2c_Send_OneByte(uint8_t reg_addr, uint8_t dat);
uint8_t SM1616_I2c_Send_NBytes(uint8_t reg_addr, uint8_t *buf, uint8_t len);

#endif
