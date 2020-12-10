#ifndef BSP_LED_H
#define BSP_LED_H

#define LED_PORT				GPIOA
#define LED_PIN					GPIO_PIN_0
#define LED_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()
#define LED_ON				HAL_GPIO_WritePin(LED_PORT,LED_PIN,GPIO_PIN_RESET);
#define LED_OFF				HAL_GPIO_WritePin(LED_PORT,LED_PIN,GPIO_PIN_SET);

void LED_GPIO_Config(void);

#endif
