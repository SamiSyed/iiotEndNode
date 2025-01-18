#ifndef SYSTEM_H
#define SYSTEM_H

#include "stdbool.h"
#include "stdint.h"
#include "stm32wlxx_hal.h"

#define FILTER_BUFFER_SIZE 10U
#define UART_RX_BUFFER_SIZE 60U
#define LORA_LISTENING_DURATION 3000U /* UNIT ms */

#define SENSOR_ID_DIGIT 3
#define IOT_GATEWAY_KEY "0123456789"
#define IOT_GATEWAY_KEY_SIZE 10U
#define LORA_MESSAGE_DELIMITER "#"
#define LORA_MESSAGE_DELIMITER_SIZE 1
#define IOT_GATEWAY_MESSAGE_SIZE 3U
#define LORA_END_NODE_VALUE_SIZE 4U

#define LORA_RX_BUFFER_SIZE                                                    \
  (IOT_GATEWAY_KEY_SIZE + LORA_MESSAGE_DELIMITER_SIZE +                        \
   IOT_GATEWAY_MESSAGE_SIZE)
#define LORA_TX_BUFFER_SIZE                                                    \
  (LORA_RX_BUFFER_SIZE + LORA_MESSAGE_DELIMITER_SIZE + LORA_END_NODE_VALUE_SIZE)

#define SENSOR_ID "102"

#define usb_uart &huart1

typedef enum {
  NO_ERROR,
  ERROR_MESSAGE_QUEUE,
  ERROR_FILTER_BUFFER_SIZE,
  ERROR_INDEX_OUT_OF_RANGE,
  ERROR_UART_TRANSMIT,
  ERROR_REPLY,
  ERROR_NO_AT_REPLY,
  ERROR_LAST_COMMAND_FAILED,
  ERROR_SEND_MQTT_FAILED,
} SystemError;

typedef enum {
  UART2_WAITING_TX,
  UART2_TX_COMPLETE,
  UART2_WAITING_RX,
  UART2_RX_COMPLETE,
} Uart2Status_e;

void setRawDataReceived(bool status);
bool isRawDataReceived(void);

void setLastCommandOK(bool status);
bool isLastCommandOK(void);

void setSystemError(SystemError error);
SystemError getSystemError(void);

Uart2Status_e getUart2Status(void);
void setUart2Status(Uart2Status_e status);

SystemError initSensorFilter(void);
void runAllFilter(void);
void setNewValueBuffer(uint16_t newValue);
uint16_t getFilteredValueByIndex(uint8_t index);

/* Uart Flag */
void setSendingFlag(bool flag);
bool getSendingFlag(void);
void setReceivingFlag(bool flag);
bool getReceivingFlag(void);

/* GSM */
SystemError gsmInit(void);
void setGMSReadinessFlag(bool);
bool isGSMReady(void);

uint16_t GetTemperatureLevel(void);

/* AT command */
SystemError sendATCommand(char *command, char *param, char *reply, bool addAT);
SystemError sendATCommandRetry(char *command, char *param, char *reply,
                               bool addAT);
void sendCommand(char *command);

/* Custom Delay */
void Delay_CustomTimer(uint32_t delayMs);
uint32_t getTick_CustomTimer(void);
uint32_t getTick_CustomTimer_Sec(void);
void initDelayCustomTimer(void);
char *prepareLoraMessage(void);
#endif /* SYSTEM_H */