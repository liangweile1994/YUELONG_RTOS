#ifndef  _SM1616_DRV_H
#define	 _SM1616_DRV_H

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"


#define SM1616_SCL_Pin 						GPIO_PIN_4
#define SM1616_SCL_GPIO_Port 				GPIOC
#define SM1616_SDA_Pin 						GPIO_PIN_5
#define SM1616_SDA_GPIO_Port 				GPIOC


#define SM1616_SCL_H()    HAL_GPIO_WritePin(SM1616_SCL_GPIO_Port, SM1616_SCL_Pin, GPIO_PIN_SET)
#define SM1616_SCL_L()    HAL_GPIO_WritePin(SM1616_SCL_GPIO_Port, SM1616_SCL_Pin, GPIO_PIN_RESET)
#define SM1616_SDA_H()    HAL_GPIO_WritePin(SM1616_SDA_GPIO_Port, SM1616_SDA_Pin, GPIO_PIN_SET)
#define SM1616_SDA_L()    HAL_GPIO_WritePin(SM1616_SDA_GPIO_Port, SM1616_SDA_Pin, GPIO_PIN_RESET)
#define SM1616_SDA_Read() HAL_GPIO_ReadPin(SM1616_SDA_GPIO_Port, SM1616_SDA_Pin)
#define IIC_DELAY  1


void SM1616_I2c_Init(void);
void SM1616_I2c_Send_OneByte(uint8_t reg_addr, uint8_t dat);
void SM1616_I2c_Send_NBytes(uint8_t *buf, uint8_t len);

#endif
