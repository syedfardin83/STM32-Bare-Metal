#include "inc/core/timer.h"
#include "libopencm3/stm32/timer.h"
#include <libopencm3/stm32/rcc.h>


// GPIO PB3 --> TIM2_CH2
void timer_setup(void){
    rcc_periph_clock_enable(RCC_TIM2);
    timer_set_mode(TIM2,TIM_CR1_CKD_CK_INT,TIM_CR1_CMS_EDGE,TIM_CR1_DIR_UP);
}

void timer_pwm_set_duty_cycle(float duty_cycle){

}