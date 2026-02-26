#include <libopencm3/include/libopencm3/stm32/rcc.h>

static void rcc_setup(void){

//     struct rcc_clock_scale {
// 	uint8_t pll_mul;
// 	uint16_t pll_div;
// 	uint8_t pll_source;
// 	uint8_t flash_waitstates;
// 	enum pwr_vos_scale voltage_scale;
// 	uint8_t hpre;
// 	uint8_t ppre1;
// 	uint8_t ppre2;
// 	// FIXME enum pwr_vos_scale voltage_scale;
// 	uint32_t ahb_frequency;
// 	uint32_t apb1_frequency;
// 	uint32_t apb2_frequency;
// 	uint8_t msi_range;
// };

    /* Custom Clock Preset for 32MHz on STM32L0 */
const struct rcc_clock_scale my_32mhz_config = {
    .pll_mul = RCC_CFGR_PLLMUL_MUL4,       // 16MHz (HSI) * 4 = 64MHz
    .pll_div = RCC_CFGR_PLLDIV_DIV2,       // 64MHz / 2 = 32MHz
    .pll_source = RCC_CFGR_PLLSRC_HSI16_CLK,  // Use Internal 16MHz Clock
    .flash_waitstates = 1,              // Required for 32MHz
    .voltage_scale = PWR_SCALE1,        // Max performance mode
    .hpre = RCC_CFGR_HPRE_NODIV,        // AHB = 32MHz
    .ppre1 = RCC_CFGR_PPRE1_NODIV,      // APB1 = 32MHz
    .ppre2 = RCC_CFGR_PPRE2_NODIV,      // APB2 = 32MHz
    .ahb_frequency = 32000000,
    .apb1_frequency = 32000000,
    .apb2_frequency = 32000000,
};
    // rcc_clock_setup_pll();
    // rcc_clock_set
}

int main(){
    while(1){

    }
    return 0;
}