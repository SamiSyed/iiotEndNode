#include "filter.h"
#include "user_system.h"

/**
 * @brief Initialize filter with struct and assign 0 as default value
 *
 * @param *filter : Pointer of struct filter
 *        *buffer : Pointer of the buffer to be used
 * @retval void
 */
SystemError MovingAverage_Init(MovingAverageFilter *filter, uint16_t *buffer,
                               uint8_t size) {
  if (size < 1) {
    return ERROR_FILTER_BUFFER_SIZE;
  }
  filter->buffer = buffer;
  filter->size = size;
  filter->index = 0;
  filter->sum = 0;

  return NO_ERROR;
  // for (uint16_t i = 0; i < size; i++) {
  //   buffer[i] = 0;
  // }
}

/**
 * @brief Run the filter to insert and calculate new value
 *
 * @param *filter : Pointer of struct filter
 *        *newValue : New value to insert
 * @retval uint32_t : return updated value
 */
uint32_t runFilter(MovingAverageFilter *filter, const uint16_t newValue) {
  /* Subtract the oldest number in the moving average from the sum to remove its
   * effect */
  // uint16_t oldValue = 0;
  // osStatus_t status = osError;

  filter->sum -= filter->buffer[filter->index];
  /* Get old value for to subtract from the sum so the effect is gone. */
  // status = osMessageQueueGet(filter->buffer, &oldValue, NULL, 0U);
  // if (status == osOK) {
  //   filter->sum -= oldValue;
  // } else {
  //   setSystemError(ERROR_MESSAGE_QUEUE);
  // }

  /* Assign the new value to the current position in the circular buffer */
  filter->buffer[filter->index] = newValue;
  // if (getSystemError() == NO_ERROR) {
  //   status = osMessageQueuePut(filter->buffer, &newValue, 0U, 0U);
  //   if (status == osOK) {
  //     /* Add the new value to the sum to include it in the moving average */
  filter->sum += newValue;
  //   }

  // } else {
  //   setSystemError(ERROR_MESSAGE_QUEUE);
  // }

  /* Increment the position, wrapping around to the beginning if necessary */
  filter->index = (filter->index + 1U) % filter->size;

  /* Return the latest moving average filter value */
  return filter->sum / filter->size;
}
