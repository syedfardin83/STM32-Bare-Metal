#include "serial.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

// ─── USART Setup ────────────────────────────────────────────────────────────
void serial_setup(void)
{
        // Enable clocks for GPIOA and USART2
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART2);

        gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE,
                    GPIO2 | GPIO3);

    gpio_set_af(GPIOA, GPIO_AF4, GPIO2 | GPIO3);


    usart_set_baudrate(USART2, 115200);
    usart_set_databits(USART2, 8);
    usart_set_stopbits(USART2, USART_STOPBITS_1);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
    usart_set_mode(USART2, USART_MODE_TX_RX);

    usart_enable(USART2);
}

// ─── Transmit Primitives ─────────────────────────────────────────────────────

// Send single character — blocks until TX register empty
void serial_putc(char c)
{
    usart_send_blocking(USART2, (uint8_t)c);
}

// Send null terminated string
void serial_puts(const char* str)
{
    while (*str) {
        serial_putc(*str++);
    }
}

// Send string with newline — useful for debug output
void serial_println(const char* str)
{
    serial_puts(str);
    serial_putc('\r');
    serial_putc('\n');
}

// ─── Integer to String (no printf, no stdlib) ────────────────────────────────
// Bare metal — you have no printf, so roll your own itoa
void serial_print_int(int32_t value)
{
    char buf[12];  // enough for -2147483648 + null
    char* p = buf + sizeof(buf) - 1;
    *p = '\0';

    uint8_t negative = 0;
    if (value < 0) {
        negative = 1;
        value = -value;
    }

    // Build string backwards
    do {
        *--p = '0' + (value % 10);
        value /= 10;
    } while (value);

    if (negative) {
        *--p = '-';
    }

    serial_puts(p);
}

// Print integer with label — useful for sensor debug
// Usage: serial_print_labeled("accel_x", raw_ax);
void serial_print_labeled(const char* label, int32_t value)
{
    serial_puts(label);
    serial_puts(": ");
    serial_print_int(value);
    serial_puts("\r\n");
}
