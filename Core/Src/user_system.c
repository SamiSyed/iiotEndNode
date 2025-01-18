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

static uint16_t newValueBuffer[NUMBER_OF_SENSORS];
static uint16_t
    filteredSensorValues[NUMBER_OF_SENSORS]; /* Global Sensor Values*/
static MovingAverageFilter sensorFilters[NUMBER_OF_SENSORS];
static uint16_t filterBuffer[NUMBER_OF_SENSORS][FILTER_BUFFER_SIZE];
static Uart2Status_e uart2Status = UART2_RX_COMPLETE;

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

Uart2Status_e getUart2Status(void) { return uart2Status; }

void setUart2Status(Uart2Status_e status) { uart2Status = status; }

SystemError getSystemError(void) { return systemError; }

/* Filter */
SystemError initSensorFilter(void) {
  SystemError error = NO_ERROR;
  /* Create NUMBER_OF_SENSORS amount of filter */
  for (uint8_t sId = 0; sId < (uint8_t)NUMBER_OF_SENSORS; sId++) {
    error = MovingAverage_Init(&sensorFilters[sId], &filterBuffer[sId][0],
                               FILTER_BUFFER_SIZE);
    if (error != NO_ERROR) {
      break;
    }
  }

  return error;
}

void runAllFilter(void) {
  for (uint8_t sId = 0; sId < (uint8_t)NUMBER_OF_SENSORS; sId++) {
    filteredSensorValues[sId] =
        runFilter(&sensorFilters[sId], newValueBuffer[sId]);
  }
}

void setNewValueBuffer(uint16_t newValue) {
  for (uint8_t sId = 0; sId < (uint8_t)NUMBER_OF_SENSORS; sId++) {
    newValueBuffer[sId] = newValue;
  }
}

/* Get value from global sensor array*/
uint16_t getFilteredValueByIndex(uint8_t index) {
  return filteredSensorValues[index];
}


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
