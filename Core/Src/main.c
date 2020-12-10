/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_led.h"
#include "debug_uart.h"
#include "sm1616_drv.h"
#include "sm1616_dev.h"
#include "apt8l16.h"




static TaskHandle_t AppTaskCreate_Handle = NULL;
static TaskHandle_t LED_Task_Handle = NULL;
static TaskHandle_t SM1616_Task_Handle = NULL;
static TaskHandle_t APT8L16_Task_Handle = NULL;
static TaskHandle_t dubug_uart_Task_Handle = NULL;
static TaskHandle_t APT8L16_Creat_Task_Handle = NULL;
extern uint8_t Disp_List[];
extern const uint8_t Num_Table[];
extern const uint8_t APT8L16_1_KOR_CONFIG[16];
uint8_t receive1;
uint8_t receive2;
uint8_t volatile i;
//uint8_t aTxBuffer[] = " **** UART_TwoBoards_ComPolling ****  **** UART_TwoBoards_ComPolling ****  **** UART_TwoBoards_ComPolling **** ";
extern UART_HandleTypeDef huart1;


static void AppTaskCreate(void);/* 用于创建任务 */
static void LED_Task(void* pvParameters);/* LED_Task任务实现 */
static void SM1616_Task(void* parameter);
static void APT8L16_Task(void* parameter);
static void APT8L16_Creat_Task(void *parameter);
static void debug_uart_Task(void *parameter);
void SystemClock_Config(void);
static void BSP_Init(void);




/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	BaseType_t xReturn = pdPASS;
	BSP_Init();
	xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* 任务入口函数 */
                        (const char*    )"AppTaskCreate",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )1, /* 任务的优先级 */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);/* 任务控制块指针 */ 
  /* 启动任务调度 */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* 启动任务，开启调度 */
  else
    return -1;
  
  while(1);   /* 正常不会执行到这里 */ 
}

static void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
  
  taskENTER_CRITICAL();           //进入临界区
  
  /* 创建LED_Task任务 */
  xReturn = xTaskCreate((TaskFunction_t )LED_Task, /* 任务入口函数 */
                        (const char*    )"LED_Task",/* 任务名字 */
                        (uint16_t       )512,   /* 任务栈大小 */
                        (void*          )NULL,	/* 任务入口函数参数 */
                        (UBaseType_t    )2,	    /* 任务的优先级 */
                        (TaskHandle_t*  )&LED_Task_Handle);/* 任务控制块指针 */
												
	xReturn = xTaskCreate((TaskFunction_t )SM1616_Task, /* 任务入口函数 */
                        (const char*    )"SM1616_Task",/* 任务名字 */
                        (uint16_t       )512,   /* 任务栈大小 */
                        (void*          )NULL,	/* 任务入口函数参数 */
                        (UBaseType_t    )3,	    /* 任务的优先级 */
                        (TaskHandle_t*  )&SM1616_Task_Handle);/* 任务控制块指针 */
												
	xReturn = xTaskCreate((TaskFunction_t )APT8L16_Creat_Task, /* 任务入口函数 */
                        (const char*    )"APT8L16_Creat_Task",/* 任务名字 */
                        (uint16_t       )512,   /* 任务栈大小 */
                        (void*          )NULL,	/* 任务入口函数参数 */
                        (UBaseType_t    )5,	    /* 任务的优先级 */
                        (TaskHandle_t*  )&APT8L16_Creat_Task_Handle);/* 任务控制块指针 */		
												
	xReturn = xTaskCreate((TaskFunction_t )APT8L16_Task, /* 任务入口函数 */
                        (const char*    )"APT8L16_Task",/* 任务名字 */
                        (uint16_t       )512,   /* 任务栈大小 */
                        (void*          )NULL,	/* 任务入口函数参数 */
                        (UBaseType_t    )4,	    /* 任务的优先级 */
                        (TaskHandle_t*  )&APT8L16_Task_Handle);/* 任务控制块指针 */
												
	xReturn = xTaskCreate((TaskFunction_t )debug_uart_Task, /* 任务入口函数 */
                        (const char*    )"debug_uart_Task",/* 任务名字 */
                        (uint16_t       )512,   /* 任务栈大小 */
                        (void*          )NULL,	/* 任务入口函数参数 */
                        (UBaseType_t    )5,	    /* 任务的优先级 */
                        (TaskHandle_t*  )&dubug_uart_Task_Handle);/* 任务控制块指针 */
												

  
  vTaskDelete(AppTaskCreate_Handle); //删除AppTaskCreate任务
  
  taskEXIT_CRITICAL();            //退出临界区
}


static void LED_Task(void* parameter)
{	
    while (1)
    {
			LED_ON;
			vTaskDelay(1);
			LED_OFF;
			vTaskDelay(1);
    }
}

static void SM1616_Task(void* parameter)
{	
    while (1)
    {
//			for(i=0;i<16;i++)
//			{
//				Disp_List[i] = Num_Table[receive];
//			}
//			sm1616_Display(Disp_List);
			vTaskDelay(10);
    }
}

static void APT8L16_Task(void* parameter)
{
	while(1)
	{
		APT8L16Init();
		receive1 = APTTouchRdOneData(APT_ADD_L,0x20);
		if(receive1 == 0x03)
		{
			SM1616_I2c_Send_OneByte(0x60,0xff);
		}
		
		vTaskDelay(100);
	}
}

static void APT8L16_Creat_Task(void *parameter)
{
//	APT8L16Init();
//	vTaskDelete(NULL);
}


static void debug_uart_Task(void* parameter)
{
	while(1)
	{
//		HAL_UART_Transmit(&huart1,aTxBuffer,16,5000);
		vTaskDelay(10);
	}
}


static void BSP_Init(void)
{
	
	HAL_Init();
  SystemClock_Config();
	LED_GPIO_Config();
	SM1616_I2c_Init();
	
//	Uart1_GPIO_Init();
//	Uart1_Init();
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the peripherals clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
