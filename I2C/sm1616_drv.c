#include "sm1616_drv.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "task.h"

#define SM1616_SCL_H()    HAL_GPIO_WritePin(SM1616_SCL_GPIO_Port, SM1616_SCL_Pin, GPIO_PIN_SET)
#define SM1616_SCL_L()    HAL_GPIO_WritePin(SM1616_SCL_GPIO_Port, SM1616_SCL_Pin, GPIO_PIN_RESET)
#define SM1616_SDA_H()    HAL_GPIO_WritePin(SM1616_SDA_GPIO_Port, SM1616_SDA_Pin, GPIO_PIN_SET)
#define SM1616_SDA_L()    HAL_GPIO_WritePin(SM1616_SDA_GPIO_Port, SM1616_SDA_Pin, GPIO_PIN_RESET)
#define SM1616_SDA_Read() HAL_GPIO_ReadPin(SM1616_SDA_GPIO_Port, SM1616_SDA_Pin)
#define IIC_DELAY  1

///*I2CÑÓÊ±º¯Êý*/
//static void I2c_Delay(uint8_t cnt)
//{   
//    while (cnt) 
//     cnt--;  			/* Decrement counter until it is zero */
//}
///*******************************************************/

static void SCL_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = SM1616_SCL_Pin; 
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
	GPIO_InitStruct.Pull = GPIO_PULLUP; 
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SM1616_SCL_GPIO_Port, &GPIO_InitStruct);
}

static void SDA_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = SM1616_SDA_Pin; 
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
	GPIO_InitStruct.Pull = GPIO_PULLUP; 
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SM1616_SDA_GPIO_Port, &GPIO_InitStruct);
}

static void SDA_In(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = SM1616_SDA_Pin; 
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; 
	GPIO_InitStruct.Pull = GPIO_PULLUP; 
	HAL_GPIO_Init(SM1616_SDA_GPIO_Port, &GPIO_InitStruct);
}

void SM1616_I2c_Init(void)
{
	SDA_Out();
	SCL_Out();
	SM1616_SDA_H();
	SM1616_SCL_H();
}

static void I2c_Start(void)
{
	SDA_Out();
	SM1616_SDA_H();
	SM1616_SCL_H();
	vTaskDelay(IIC_DELAY);
	SM1616_SDA_L();
	vTaskDelay(IIC_DELAY);
	SM1616_SCL_L();
}

static void I2c_Stop(void)
{
	SDA_Out();
	SM1616_SDA_L();
	SM1616_SCL_H();
	vTaskDelay(IIC_DELAY);
	SM1616_SDA_H();
	vTaskDelay(IIC_DELAY);

}

static void I2c_SendByte(uint8_t  dat)
{
  uint8_t  i,j;
  j = dat;
  
	SDA_Out();
  for (i=0; i<8; i++)
  {
		vTaskDelay(IIC_DELAY);
    if ((j & 0x80)==0)
    { SM1616_SDA_L();}
    else
    { SM1616_SDA_H();}
    j <<=1;
    vTaskDelay(IIC_DELAY);
    SM1616_SCL_H();
	vTaskDelay(IIC_DELAY);
    SM1616_SCL_L();
    vTaskDelay(IIC_DELAY);
  }

}

static uint8_t  I2c_WaitAck(void)
{
	uint8_t  cnt = 0;
	SDA_In();
	SM1616_SDA_H();
	vTaskDelay(IIC_DELAY);
	SM1616_SCL_H();
	vTaskDelay(IIC_DELAY);
	while(SM1616_SDA_Read())
	{
	cnt++;
	if(cnt>=250)
	{
			SM1616_SCL_L();
			vTaskDelay(IIC_DELAY);
	  return FALSE;
	}
	}
	SM1616_SCL_L();
	vTaskDelay(IIC_DELAY);
	return TRUE;
	
}

uint8_t SM1616_I2c_Send_OneByte(uint8_t reg_addr, uint8_t dat)
{
	I2c_Start();
	I2c_SendByte(reg_addr);
	if(I2c_WaitAck() == FALSE)
	{
//		return FALSE;
	}
	I2c_SendByte(dat);
	I2c_WaitAck();
	I2c_Stop();
	return TRUE;
}

uint8_t SM1616_I2c_Send_NBytes(uint8_t reg_addr, uint8_t *buf, uint8_t len)
{
	uint8_t i;
	
	I2c_Start();
	I2c_SendByte(reg_addr);
	if(I2c_WaitAck() == FALSE)
	{
//		return FALSE;
	}
	for(i=0;i<len;i++)
	{
		I2c_SendByte(*buf++);
		I2c_WaitAck();
	}
	I2c_Stop();
	return TRUE;
}
