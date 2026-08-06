#include "../../inc/core/timer.h"
#include "libopencm3/stm32/timer.h"
#include <libopencm3/stm32/rcc.h>


#define PRESCALER (32)
#define ARR_VALUE (1000)

// GPIO PA0 --> TIM2_CH1
void timer_setup(void){
    rcc_periph_clock_enable(RCC_TIM2);

    //  High level timer setup
    timer_set_mode(TIM2,TIM_CR1_CKD_CK_INT,TIM_CR1_CMS_EDGE,TIM_CR1_DIR_UP);

    //  Set the mode to PWM on channel 2.
    timer_set_oc_mode(TIM2,TIM_OC1,TIM_OCM_PWM1);
    

    //  Enable counter
    timer_enable_counter(TIM2);
    timer_enable_oc_output(TIM2,TIM_OC1);

    //  Setup frequency and resolution
    //  Both of these parameters determine the frequency/time period of one cycle
    timer_set_prescaler(TIM2,PRESCALER-1);
    timer_set_period(TIM2,ARR_VALUE-1);

}

void timer_pwm_set_duty_cycle(float duty_cycle){
    const float raw_value = (float)ARR_VALUE * (duty_cycle/100.0f);
    timer_set_oc_value(TIM2,TIM_OC1,(uint32_t)raw_value);
}