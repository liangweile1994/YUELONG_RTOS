#include "bsp_led.h"
#include "stm32g0xx_hal.h"



void LED_GPIO_Config(void)
{
	LED_CLK_ENABLE();
	static GPIO_InitTypeDef  GPIO_InitStruct = {0};
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_InitStruct.Pin = LED_PIN;
  HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}
