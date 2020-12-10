#include "i2c.h"

/* BRIEF:GPIO_Init 										                      */
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


/* BRIEF:generate i2c start signal 										               */
static void I2c_Start(void)
{
	SDA_Out();
	SM1616_SDA_H();
	vTaskDelay(IIC_DELAY);
	SM1616_SCL_H();
	vTaskDelay(IIC_DELAY);
	vTaskDelay(IIC_DELAY);
	SM1616_SDA_L();
	vTaskDelay(IIC_DELAY);
	vTaskDelay(IIC_DELAY);
	SM1616_SCL_L();
	vTaskDelay(IIC_DELAY);
}


/* BRIEF:generate i2c stop signal 										               */
static void I2c_Stop(void)
{
	SDA_Out();
	SM1616_SDA_L();
	vTaskDelay(IIC_DELAY);
	SM1616_SCL_H();
	vTaskDelay(IIC_DELAY);
	SM1616_SDA_H();
	vTaskDelay(IIC_DELAY);

}

/* BRIEF:i2c sent one byte       										               */
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
		vTaskDelay(IIC_DELAY);
    SM1616_SCL_L();
  }

}

/* BRIEF:i2c waitting for ack,and no answer
		 return i2c or no receive slave ack signal    		           */
static uint8_t I2c_WaitAck(void)
{
    uint8_t result = 0; 
    SDA_In();  
		vTaskDelay(IIC_DELAY);	          
    SM1616_SCL_H();           
    vTaskDelay(IIC_DELAY);
    if(SM1616_SDA_Read())
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    SM1616_SCL_L();
    vTaskDelay(IIC_DELAY);
    return result;  
}