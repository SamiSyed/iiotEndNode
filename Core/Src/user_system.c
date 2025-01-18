#include "user_system.h"
#include "filter.h"
#include "main.h"
#include "stdio.h"
#include "tim.h"
#include "usart.h"

static bool rawDataReceived = false;
static SystemError systemError = NO_ERROR;
static bool sendingData = false;
static bool receivingData = false;
static bool initialized = false;
/* This initially has to be true to fetch first AT Reply*/
static bool lastCommandOK = true;
uint32_t timeStamp_timer = 0;

uint8_t loraMessage_TX[LORA_TX_BUFFER_SIZE + 1];

/* GSM variables */

/* Flag */
void setRawDataReceived(bool status) { rawDataReceived = status; }
bool isRawDataReceived(void) { return rawDataReceived; }

void setSendingFlag(bool flag) { sendingData = flag; }
bool getSendingFlag(void) { return sendingData; }

void setReceivingFlag(bool flag) { receivingData = flag; }
bool getReceivingFlag(void) { return receivingData; }

void setLastCommandOK(bool status) { lastCommandOK = status; }
bool isLastCommandOK(void) { return lastCommandOK; }

/* Error */
void setSystemError(SystemError error) {
  /* Keep first error so it is not over written */
  if (systemError == NO_ERROR) {
    systemError = error;
  }
}

SystemError getSystemError(void) { return systemError; }


uint16_t GetTemperatureLevel(void) {
  uint16_t temperatureLevel = 0;

  temperatureLevel = (uint16_t)(SYS_GetTemperatureLevel() / 256);
  /* USER CODE BEGIN GetTemperatureLevel */

  /* USER CODE END GetTemperatureLevel */
  return temperatureLevel;
}

void Delay_CustomTimer(uint32_t delayMs) {
  timeStamp_timer = getTick_CustomTimer();
  while (1) {
    if (__HAL_TIM_GET_COUNTER(&htim2) - timeStamp_timer >= delayMs) {
      break;
    }
  }
}

uint32_t getTick_CustomTimer(void) { return __HAL_TIM_GET_COUNTER(&htim2); }

uint32_t getTick_CustomTimer_Sec(void) {
  return (__HAL_TIM_GET_COUNTER(&htim2) + 1) / 1000;
}

void initDelayCustomTimer(void) {
  timeStamp_timer = __HAL_TIM_GET_COUNTER(&htim2);
}

char *prepareLoraMessage(void) {
  uint8_t dataString[LORA_END_NODE_VALUE_SIZE];
  uint16_t rawData = GetTemperatureLevel();
  // uint16_t rawData = SYS_GetBatteryLevel();

  // printf("LORA: Temperature : %i\r\n", temperature);
  printf("\r\nRaw Data : %i\r\n", rawData);

  itoa(rawData, dataString, 10);

  // snprintf(loraMessage_TX, sizeof(loraMessage_TX), "%s#%s", IOT_GATEWAY_KEY,
  //          SENSOR_ID);
  snprintf(loraMessage_TX, sizeof(loraMessage_TX), "%s#%s#%s", IOT_GATEWAY_KEY,
           SENSOR_ID, dataString);
  printf("LORA: TX: %s\r\n",loraMessage_TX);
  return loraMessage_TX;
}