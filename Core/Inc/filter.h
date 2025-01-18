#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>

#include "user_system.h"

typedef struct {
  uint16_t *buffer;
  uint8_t size;
  uint8_t index;
  uint32_t sum;
} MovingAverageFilter;

SystemError MovingAverage_Init(MovingAverageFilter *filter, uint16_t *buffer,
                        uint8_t size);
uint32_t runFilter(MovingAverageFilter *filter, const uint16_t newValue);

#endif /* FILTER_H */
