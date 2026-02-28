#include <libopencm3/include/libopencm3/stm32/rcc.h>

static void rcc_setup(void){

    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_CONFIG_HSI_32MHZ]);
}

int main(){
    while(1){

    }
    return 0;
}