#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

// ─── Clock Setup ────────────────────────────────────────────────────────────
static void clock_setup(void)
{
    // Your libopencm3 contribution — HSI at 32MHz
    rcc_osc_on(RCC_HSI);
    rcc_wait_for_osc_ready(RCC_HSI);
    rcc_set_sysclk_source(RCC_HSI);

    // Enable clocks for GPIOA and USART2
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART2);
}

// ─── GPIO Setup ─────────────────────────────────────────────────────────────
static void gpio_setup(void)
{
    // PA2 = USART2_TX, PA3 = USART2_RX
    // Alternate function 4 for USART2 on STM32L0
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE,
                    GPIO2 | GPIO3);

    gpio_set_af(GPIOA, GPIO_AF4, GPIO2 | GPIO3);
}

// ─── USART Setup ────────────────────────────────────────────────────────────
static void usart_setup(void)
{
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
void uart_putc(char c)
{
    usart_send_blocking(USART2, (uint8_t)c);
}

// Send null terminated string
void uart_puts(const char* str)
{
    while (*str) {
        uart_putc(*str++);
    }
}

// Send string with newline — useful for debug output
void uart_println(const char* str)
{
    uart_puts(str);
    uart_putc('\r');
    uart_putc('\n');
}

// ─── Integer to String (no printf, no stdlib) ────────────────────────────────
// Bare metal — you have no printf, so roll your own itoa
void uart_print_int(int32_t value)
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

    uart_puts(p);
}

// Print integer with label — useful for sensor debug
// Usage: uart_print_labeled("accel_x", raw_ax);
void uart_print_labeled(const char* label, int32_t value)
{
    uart_puts(label);
    uart_puts(": ");
    uart_print_int(value);
    uart_puts("\r\n");
}

// ─── Main ───────────────────────────────────────────────────────────────────
int main(void)
{
    clock_setup();
    gpio_setup();
    usart_setup();

    uart_println("STM32L072 bare metal UART initialized");
    uart_println("libopencm3 - no HAL, no CubeMX");

    uint32_t counter = 0;

    while (1) {
        uart_puts("count: ");
        uart_print_int(counter++);
        uart_puts("\r\n");

        // Simple delay — replace with SysTick later
        for (volatile int i = 0; i < 100000; i++);
    }

    return 0;
}