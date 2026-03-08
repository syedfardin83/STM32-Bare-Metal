#ifndef INC_SYSTEM_H
#define INC_SYSTEM_H

#include <stdint.h>

#define CLOCK_FREQ    (32000000)
#define SYSTICK_FREQ  (1000)

void system_setup(void);
uint64_t system_get_ticks(void);

#endif