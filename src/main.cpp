#include "hal/hal.hpp"
#include "system/stm32/target/stm32f405.hpp"

extern "C" int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    stm32::f405::Stm32F405Peripherals peripherals{};
    auto gpioc = peripherals.gpioc;

    stm32::gpio::Pin<GPIOC_BASE, 8> pc8 = gpioc.pin<8>();
    pc8.push_pull();
    pc8.push_pull(false);
    for(;;) {}
}

extern "C" void SystemInit(void) {

}
