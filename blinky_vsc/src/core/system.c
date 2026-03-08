#include "../../inc/core/system.h"
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/rcc.h>


volatile uint64_t ticks=0;
void sys_tick_handler(void){
    ticks++;
}

uint64_t system_get_ticks(void){
    return ticks;
}

void rcc_setup(void){
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_CONFIG_HSI_32MHZ]);
}

void systick_setup(void){
    systick_set_frequency(SYSTICK_FREQ, CLOCK_FREQ);
    systick_counter_enable();
    systick_interrupt_enable();
}

void system_setup(void){
    rcc_setup();
    systick_setup();
}

// void system_setup(void);
// uint64_t system_get_ticks(void);