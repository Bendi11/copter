#include "stm32f405xx.h"
#include "system/stm32/gpio.hpp"
#include "hal/hal.hpp"

extern "C" int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    stm32::GpioPin<GPIOC_BASE, 8> pc8;
    pc8.push_pull();
    pc8.set(false);
    for(;;) {}
}

extern "C" void SystemInit(void) {

}
