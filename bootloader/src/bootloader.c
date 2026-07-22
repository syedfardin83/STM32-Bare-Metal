#include "common-defines.h"
#include "libopencm3/stm32/memorymap.h"

#define BOOTLOADER_SIZE            (0x1388)
#define MAIN_APP_START_ADDRESS     (FLASH_BASE + BOOTLOADER_SIZE)




void jump_to_main(){
    uint32_t* reset_vector_entry = (uint32_t*)(MAIN_APP_START_ADDRESS+4U);
    void* reset_vector = (void*)(*reset_vector_entry);
    void (*jump_func)(void);
    jump_func = (void (*)(void))reset_vector;

    jump_func();
}


int main(){
    jump_to_main();
    return 0;
}