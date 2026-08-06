#include "../../inc/core/timer.h"
#include "libopencm3/stm32/timer.h"
#include <libopencm3/stm32/rcc.h>


#define PRESCALER (32)
#define ARR_VALUE (1000)

// GPIOB GPIO5 --> TIM3_CH2
void timer_setup(void){
    rcc_periph_clock_enable(RCC_TIM3);

    //  High level timer setup
    timer_set_mode(TIM3,TIM_CR1_CKD_CK_INT,TIM_CR1_CMS_EDGE,TIM_CR1_DIR_UP);

    //  Set the mode to PWM on channel 2.
    timer_set_oc_mode(TIM3,TIM_OC2,TIM_OCM_PWM1);
    

    //  Enable counter
    timer_enable_counter(TIM3);
    timer_enable_oc_output(TIM3,TIM_OC2);

    //  Setup frequency and resolution
    //  Both of these parameters determine the frequency/time period of one cycle
    timer_set_prescaler(TIM3,PRESCALER-1);
    timer_set_period(TIM3,ARR_VALUE-1);

}

void timer_pwm_set_duty_cycle(float duty_cycle){
    const float raw_value = (float)ARR_VALUE * (duty_cycle/100.0f);
    timer_set_oc_value(TIM3,TIM_OC2,(uint32_t)raw_value);
}