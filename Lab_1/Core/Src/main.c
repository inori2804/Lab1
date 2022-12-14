/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
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

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	void clearAllClock() {
		GPIOA->ODR |= 0xFFF0;
	}
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
	void setNumberOnClock(int num) {
		switch (num) {
		case 0: {
			HAL_GPIO_WritePin(LABEL_B_GPIO_Port, LABEL_B_Pin, RESET);
			break;
		}
		case 1: {
			HAL_GPIO_WritePin(LABEL_C_GPIO_Port, LABEL_C_Pin, RESET);
			break;
		}
		case 2: {
			HAL_GPIO_WritePin(LABEL_D_GPIO_Port, LABEL_D_Pin, RESET);
			break;
		}
		case 3: {
			HAL_GPIO_WritePin(LABEL_E_GPIO_Port, LABEL_E_Pin, RESET);
			break;
		}
		case 4: {
			HAL_GPIO_WritePin(LABEL_F_GPIO_Port, LABEL_F_Pin, RESET);
			break;
		}
		case 5: {
			HAL_GPIO_WritePin(LABEL_G_GPIO_Port, LABEL_G_Pin, RESET);
			break;
		}
		case 6: {
			HAL_GPIO_WritePin(LABEL_H_GPIO_Port, LABEL_H_Pin, RESET);
			break;
		}
		case 7: {
			HAL_GPIO_WritePin(LABEL_I_GPIO_Port, LABEL_I_Pin, RESET);
			break;
		}
		case 8: {
			HAL_GPIO_WritePin(LABEL_J_GPIO_Port, LABEL_J_Pin, RESET);
			break;
		}
		case 9: {
			HAL_GPIO_WritePin(LABEL_K_GPIO_Port, LABEL_K_Pin, RESET);
			break;
		}
		case 10: {
			HAL_GPIO_WritePin(LABEL_L_GPIO_Port, LABEL_L_Pin, RESET);
			break;
		}
		case 11: {
			HAL_GPIO_WritePin(LABEL_A_GPIO_Port, LABEL_A_Pin, RESET);
			break;
		}
		default:
			break;
		}
	}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

// 	init turn of sate for each led using output data register
	GPIOA->ODR = 0xFFF0;
//	init sec min hour counter value
	int sec_counter = 0;
	int min_counter = 0;
	int hour_counter = 0;
// init count down value for sec and minute
	int count_down_sec = 5;
	int count_down_min = 5;
	while (1) {
//		calculate counter logic for sec, min and hour
		if (sec_counter >= 12) {
			count_down_min--;
			sec_counter = 0;
		}
		if(count_down_min <= 0){ //after sec run 5cycles, increase minute one unit
			count_down_min = 5;
			min_counter++;
		}
		if (min_counter >= 12) {
			hour_counter++;
			min_counter = 0;
		}
		if (hour_counter >= 12) {
			hour_counter = 0;
		}


//		clear all led and set value to display led
		clearAllClock();
		setNumberOnClock(sec_counter);
		setNumberOnClock(min_counter);
		setNumberOnClock(hour_counter);

//  	after 5sec in real time increase sec_counter one unit
//		so that, affter 5sec*12 = 60sec is one minute
		count_down_sec--;
		if (count_down_sec <= 0) {
			sec_counter++;
			count_down_sec = 5;
		}

		HAL_Delay(1000);
    /* USER CODE END WHILE */

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LABEL_A_Pin|LABEL_B_Pin|LABEL_C_Pin|LABEL_D_Pin
                          |LABEL_E_Pin|LABEL_F_Pin|LABEL_G_Pin|LABEL_H_Pin
                          |LABEL_I_Pin|LABEL_J_Pin|LABEL_K_Pin|LABEL_L_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LABEL_A_Pin LABEL_B_Pin LABEL_C_Pin LABEL_D_Pin
                           LABEL_E_Pin LABEL_F_Pin LABEL_G_Pin LABEL_H_Pin
                           LABEL_I_Pin LABEL_J_Pin LABEL_K_Pin LABEL_L_Pin */
  GPIO_InitStruct.Pin = LABEL_A_Pin|LABEL_B_Pin|LABEL_C_Pin|LABEL_D_Pin
                          |LABEL_E_Pin|LABEL_F_Pin|LABEL_G_Pin|LABEL_H_Pin
                          |LABEL_I_Pin|LABEL_J_Pin|LABEL_K_Pin|LABEL_L_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
	while (1) {
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
