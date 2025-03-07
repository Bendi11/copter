#include "hal/hal.hpp"
#include "stm32f405xx.h"
#include "system/stm32/target/stm32f405.hpp"

extern "C" int main(void) {
    stm32::f405::Stm32F405Regs peripherals{};
    auto gpioc = peripherals.enable_gpio<GPIOC_BASE>();
    auto pc8 = gpioc.pin<8>().mode_push_pull();
    pc8.push_pull(false);
    for(;;) {}
}

extern "C" void SystemInit(void) {
}
