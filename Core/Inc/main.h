/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RTC_PREDIV_A ((1<<(15-RTC_N_PREDIV_S))-1)
#define RTC_N_PREDIV_S 10
#define RTC_PREDIV_S ((1<<RTC_N_PREDIV_S)-1)
#define GPRS_RX_Pin GPIO_PIN_7
#define GPRS_RX_GPIO_Port GPIOB
#define ENABLE_PWR_LED_Pin GPIO_PIN_5
#define ENABLE_PWR_LED_GPIO_Port GPIOB
#define ACTION_BUTTON_Pin GPIO_PIN_13
#define ACTION_BUTTON_GPIO_Port GPIOB
#define GPRS_TX_Pin GPIO_PIN_6
#define GPRS_TX_GPIO_Port GPIOB
#define ENABLE_3V_Pin GPIO_PIN_9
#define ENABLE_3V_GPIO_Port GPIOA
#define LED_OUT_Pin GPIO_PIN_10
#define LED_OUT_GPIO_Port GPIOB
#define RF_SW_CTRL1_Pin GPIO_PIN_4
#define RF_SW_CTRL1_GPIO_Port GPIOA
#define RF_SW_CTRL2_Pin GPIO_PIN_5
#define RF_SW_CTRL2_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
void Delay_CustomTimer(uint32_t delayMs);
uint32_t getTick_CustomTimer(void);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
