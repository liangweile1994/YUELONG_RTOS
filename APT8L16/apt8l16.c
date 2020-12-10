#include "apt8l16.h"


uint8_t arr_APTRegData[14]={GSR,MCON,FILTER0,K0_ENB,K1_ENB,SENSE_CON,SENSE_S,GSR_K07,GSR_K17,REF_UTH,KEY_ATH,DSMIT,MCONH,FILTER1};
uint8_t arr_T_Sens[16]={13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13};


/* BRIEF:GPIO_Init 										                      */
static void SCL_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = APT8L16_SCL_Pin; 
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
	GPIO_InitStruct.Pull = GPIO_PULLUP; 
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(APT8L16_SCL_GPIO_Port, &GPIO_InitStruct);
}

static void SDA_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = APT8L16_SDA_Pin; 
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
	GPIO_InitStruct.Pull = GPIO_PULLUP; 
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(APT8L16_SDA_GPIO_Port, &GPIO_InitStruct);
}


static void SDA_In(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = APT8L16_SDA_Pin; 
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; 
	GPIO_InitStruct.Pull = GPIO_PULLUP; 
	HAL_GPIO_Init(APT8L16_SDA_GPIO_Port, &GPIO_InitStruct);
}


/**
* @brief  i2c_initialization
* @param  
* @retval 
*/
static void ATP8L16_I2c_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	SDA_Out();
	SCL_Out();
	APT8L16_SDA_H();
	APT8L16_SCL_H();
}

/* BRIEF:generate i2c start signal 										               */
static void I2c_Start(void)
{
	SDA_Out();
	APT8L16_SDA_H();
	vTaskDelay(IIC_DELAY);
	APT8L16_SCL_H();
	vTaskDelay(IIC_DELAY);
	vTaskDelay(IIC_DELAY);
	APT8L16_SDA_L();
	vTaskDelay(IIC_DELAY);
	vTaskDelay(IIC_DELAY);
	APT8L16_SCL_L();
	vTaskDelay(IIC_DELAY);
}

void I2c_Start_test1(void)
{
	SDA_Out();
	APT8L16_SDA_H();
	vTaskDelay(IIC_DELAY);
	APT8L16_SCL_H();
	vTaskDelay(IIC_DELAY);
	vTaskDelay(IIC_DELAY);
	APT8L16_SDA_L();
	vTaskDelay(IIC_DELAY);
	vTaskDelay(IIC_DELAY);
	APT8L16_SCL_L();
	vTaskDelay(IIC_DELAY);
}


/* BRIEF:generate i2c stop signal 										               */
static void I2c_Stop(void)
{
	SDA_Out();
	APT8L16_SDA_L();
	vTaskDelay(IIC_DELAY);
	APT8L16_SCL_H();
	vTaskDelay(IIC_DELAY);
	APT8L16_SDA_H();
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
    { APT8L16_SDA_L();}
    else
    { APT8L16_SDA_H();}
    j <<=1;
    vTaskDelay(IIC_DELAY);
    APT8L16_SCL_H();
		vTaskDelay(IIC_DELAY);
		vTaskDelay(IIC_DELAY);
    APT8L16_SCL_L();
  }
}

/* BRIEF:i2c Receive one byte       										               */
static uint8_t I2c_ReceiveByte(void)
{
  uint8_t i;
  uint8_t TempData = 0;
  SDA_In();
  for (i=0; i<8; i++)
  {
    APT8L16_SCL_H();
    vTaskDelay(IIC_DELAY);
    TempData <<= 1;
    if(APT8L16_SDA_Read())
    {
      TempData|=0x01; 
    }
    APT8L16_SCL_L();
    vTaskDelay(IIC_DELAY);
  }
  SDA_Out();
  return(TempData);
}


/* BRIEF:i2c waitting for ack,and no answer
		 return i2c or no receive slave ack signal    		           */
static uint8_t I2c_WaitAck(void)
{
    uint8_t result = 0; 
    SDA_In();  
		vTaskDelay(IIC_DELAY);	          
    APT8L16_SCL_H();           
    vTaskDelay(IIC_DELAY);
    if(APT8L16_SDA_Read())
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    APT8L16_SCL_L();
    vTaskDelay(IIC_DELAY);
    return result;  
}



void  APTTouchWrOneData(uint8_t apt_add,uint8_t APTWrAdd,uint8_t APTWrData)
{
   I2c_Start();
   I2c_SendByte((apt_add<<1)|0x00);
   I2c_WaitAck();
   I2c_SendByte(APTWrAdd);
   I2c_WaitAck();
   I2c_SendByte(APTWrData);
   I2c_WaitAck();
   I2c_Stop();
}
/*******************************************************************************
* APT Touch Key Read one address data
********************************************************************************/
uint8_t  APTTouchRdOneData(uint8_t apt_add,uint8_t APTRdAdd)
{
   uint8_t APTRdData=0;
   I2c_Start();
   I2c_SendByte((apt_add<<1)|0x00);
   I2c_WaitAck();
   I2c_SendByte(APTRdAdd);
   I2c_WaitAck();
   I2c_Stop();
   I2c_Start();
   I2c_SendByte((apt_add<<1)|0x01);
   I2c_WaitAck();
   APTRdData=I2c_ReceiveByte();
   I2c_Stop();
   return(APTRdData);
}


void APT8L16Init(void)
{
    uint8_t i=0;
    ATP8L16_I2c_Init();
    APTTouchWrOneData(APT_ADD_L,0x3A,0x5A);    //setting mode
    for(i=0x20;i<=0x2D;)   
    {
        APTTouchWrOneData(APT_ADD_L,i,arr_APTRegData[i-0x20]);
        i++;
    }
    for(i=0;i<=0x0F;)   
     {
        APTTouchWrOneData(APT_ADD_L,i,arr_T_Sens[i]);            //Set sensing K00~K17
        i++;   
     }

    APTTouchWrOneData(APT_ADD_L,0x3A,0x00);    //setting working mode
}


uint8_t APT8L16ReadKeyValue(void)
{
  uint8_t KeyValue;
  KeyValue=APTTouchRdOneData(APT_ADD_L,0x36);
  switch(KeyValue)
  {
    case 0x01: return 0;  //return k00
    case 0x02: return 1;  //return k01
    case 0x03: return 2;  //return k02
    case 0x04: return 3;  //return k03
    case 0x05: return 4;  //return k04
    case 0x06: return 5;  //return k05
    case 0x07: return 6;  //return k06
    case 0x08: return 7;  //return k07
//    case 0x09: return 10; //return k10
//    case 0x0a: return 11; //return k11
//    case 0x0b: return 12; //return k12
//    case 0x0c: return 13; //return k13
//    case 0x0d: return 14; //return k14
//    case 0x0e: return 15; //return k15
//    case 0x0f: return 16; //return k16
//    case 0x10: return 17; //return k17
		case 0xff: return 15;
  }
}
