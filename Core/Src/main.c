/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "maxim_ds18b20.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct
{
	GPIO_TypeDef* settings;
	uint16_t pin;
}GenericGPIO_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
void delay_us(uint32_t delay)
{
	  __HAL_TIM_SET_COUNTER(&htim7, 0);
	  while (__HAL_TIM_GET_COUNTER(&htim7) < delay);
}

void delay_ms(uint32_t delay)
{
	for (uint32_t i=0; i<delay; ++i)
	{
		delay_us(1000);
	}
}

void set_gpio_low(void* gpio)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	HAL_GPIO_WritePin(((GenericGPIO_t*)gpio)->settings, ((GenericGPIO_t*)gpio)->pin, GPIO_PIN_RESET);
	/*Configure GPIO pin : DS18B20_PORT1_Pin */
	GPIO_InitStruct.Pin = ((GenericGPIO_t*)gpio)->pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(((GenericGPIO_t*)gpio)->settings, &GPIO_InitStruct);
	//HAL_GPIO_WritePin(DS18B20_PORT1_GPIO_Port, DS18B20_PORT1_Pin, GPIO_PIN_RESET);
}

void set_gpio_input(void* gpio)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*Configure GPIO pin : DS18B20_PORT1_Pin */
	GPIO_InitStruct.Pin = ((GenericGPIO_t*)gpio)->pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(((GenericGPIO_t*)gpio)->settings, &GPIO_InitStruct);
}

bool read_gpio(void* gpio)
{
	return (HAL_GPIO_ReadPin(((GenericGPIO_t*)gpio)->settings,((GenericGPIO_t*)gpio)->pin) == GPIO_PIN_SET) ? true : false;
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	GenericGPIO_t oneWirePort = {	.settings=DS18B20_Port_GPIO_Port, .pin=DS18B20_Port_Pin};
	oneWire_t oneWire = {
			.one_wire_pulldown = set_gpio_low,
			.one_wire_read = read_gpio,
			.one_wire_release = set_gpio_input,
			.delay_us = delay_us,
			.port = &oneWirePort
	};

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  if(one_wire_reset(&oneWire)) HAL_UART_Transmit(&huart3, (uint8_t*)"Sensor Found!!\n", 15, 100);
	  else HAL_UART_Transmit(&huart3, (uint8_t*)"Sensor NOT Found!!\n", 19, 100);
	  delay_ms(5000);
	  get_temperature(&oneWire);

	  uint8_t data[10];

	  uint8_t parte_entera = (uint8_t)oneWire.temperature;
	  uint8_t parte_decimal = 10.0*oneWire.temperature - 10*parte_entera;

  #if 1
	  data[0] = parte_entera/10 + '0';
	  data[1] = parte_entera%10 + '0';
	  data[2] = '.';
	  data[3] = parte_decimal + '0';
  #else
	  data[0] = 1+'0';
	  data[1] = 2+'0';
	  data[2] = '.';
	  data[3] = 3+'0';
  #endif
	  data[4] = '\n';
	  HAL_UART_Transmit(&huart3, data, 5, 100);
	  delay_ms(2000);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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
