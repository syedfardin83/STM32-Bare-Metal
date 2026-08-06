#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include "system.h"
#include "timer.h"

#define LED_PORT      (GPIOB)
#define LED_PIN       (GPIO6)

// GPIO PB3 --> TIM2_CH2
static void gpio_setup(void){
    rcc_periph_clock_enable(RCC_GPIOB);
    gpio_mode_setup(LED_PORT,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,LED_PIN);
    // gpio_set_af(LED_PORT,GPIO_AF2,LED_PIN);
}


int main(){
    system_setup();
    gpio_setup();
    timer_setup();

    // uint64_t start_time = system_get_ticks();
    // float duty_cycle = 0.0f;
     
    // timer_pwm_set_duty_cycle(duty_cycle);

    while(1){
        // if(system_get_ticks()-start_time >= 10){
        //     duty_cycle = duty_cycle>=99 ? 0:duty_cycle+1.0f;
        //     timer_pwm_set_duty_cycle(duty_cycle);
        //     start_time = system_get_ticks();
        // }
        gpio_port_write(LED_PORT,LED_PIN);
    }
    return 0;
}