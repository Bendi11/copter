#include "stm32f405xx.h"
#include "system/stm32/gpio.hpp"

#include "system/comptime.hpp"

namespace stm32 {

namespace f405 {

struct Stm32F405Peripherals {
    stm32::gpio::Block<GPIOA_BASE> gpioa{};
    stm32::gpio::Block<GPIOB_BASE> gpiob{};
    stm32::gpio::Block<GPIOC_BASE> gpioc{};
    stm32::gpio::Block<GPIOD_BASE> gpiod{};
    stm32::gpio::Block<GPIOE_BASE> gpioe{};
    stm32::gpio::Block<GPIOF_BASE> gpiof{};
};

}

}
