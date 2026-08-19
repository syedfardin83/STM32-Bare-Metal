#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include "serial.h"

// ─── Clock Setup ────────────────────────────────────────────────────────────
static void clock_setup(void)
{
    // Your libopencm3 contribution — HSI at 32MHz
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_CONFIG_HSI_32MHZ]);


}

// ─── GPIO Setup ─────────────────────────────────────────────────────────────
static void gpio_setup(void)
{
    // PA2 = USART2_TX, PA3 = USART2_RX
    // Alternate function 4 for USART2 on STM32L0

}


// ─── Main ───────────────────────────────────────────────────────────────────
int main(void)
{
    clock_setup();
    gpio_setup();
    serial_setup();


    serial_println("STM32L072 bare metal UART initialized");
    serial_println("libopencm3 - no HAL, no CubeMX");

    uint32_t counter = 0;

    while (1) {
        serial_puts("count value is : ");
        serial_print_int(counter++);
        serial_puts("\r\n");

        // Simple delay — replace with SysTick later
        for (volatile int i = 0; i < 100000; i++);
    }

    return 0;
}