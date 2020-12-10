#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

#define APT8L16_SCL_Pin 						GPIO_PIN_13
#define APT8L16_SCL_GPIO_Port 				GPIOB
#define APT8L16_SDA_Pin 						GPIO_PIN_14
#define APT8L16_SDA_GPIO_Port 				GPIOB


#define APT8L16_SCL_H()    HAL_GPIO_WritePin(APT8L16_SCL_GPIO_Port, APT8L16_SCL_Pin, GPIO_PIN_SET)
#define APT8L16_SCL_L()    HAL_GPIO_WritePin(APT8L16_SCL_GPIO_Port, APT8L16_SCL_Pin, GPIO_PIN_RESET)
#define APT8L16_SDA_H()    HAL_GPIO_WritePin(APT8L16_SDA_GPIO_Port, APT8L16_SDA_Pin, GPIO_PIN_SET)
#define APT8L16_SDA_L()    HAL_GPIO_WritePin(APT8L16_SDA_GPIO_Port, APT8L16_SDA_Pin, GPIO_PIN_RESET)
#define APT8L16_SDA_Read() HAL_GPIO_ReadPin(APT8L16_SDA_GPIO_Port, APT8L16_SDA_Pin)
#define IIC_DELAY  1


#define APT_ADD_H	(0x56)			 //APT ADDÒý½ÅµçÆ½Îª¸ß£¬µØÖ·
#define APT_ADD_L	(0x57)		   //APT ADDÒý½ÅµçÆ½ÎªµÍ£¬µØÖ·
#define GSR  		  (0x03)		
#define MCON 		  (0x05)			
#define FILTER0 	(0xF4)			
#define K0_ENB	 	(0x00)			// disable £¨°´¼üÍ¨µÀÎª1½ûÖ¹£¬Îª0Ê¹ÄÜ£©
#define K1_ENB	 	(0x00)			// disable £¨°´¼üÍ¨µÀÎª1½ûÖ¹£¬Îª0Ê¹ÄÜ£©
#define SENSE_CON	(0x00)			
#define SENSE_S		(0x08)			
#define GSR_K07		(0x02)			
#define GSR_K17		(0x02)			
#define	REF_UTH	  (0x10)			  
#define KEY_ATH		(0x10)			
#define DSMIT		  (0x04)		
#define MCONH		  (0x00)			
#define FILTER1		(0x00)	



uint8_t  APTTouchRdOneData(uint8_t apt_add,uint8_t APTRdAdd);
void  APTTouchWrOneData(uint8_t apt_add,uint8_t APTWrAdd,uint8_t APTWrData);
void  APT8L16Init(void);
uint8_t APT8L16ReadKeyValue(void);
