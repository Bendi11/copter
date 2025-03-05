#pragma once

#include "stm32f405xx.h"
#include <cstdint>
#include "hal/gpio/pin.hpp"

namespace stm32 {

template<typename T, std::uint32_t ADDR>
struct RegisterBlock {
    constexpr T* ptr() const {
        return (T*)ADDR;
    }

    inline constexpr T* operator ->() const {
        return (T*)ADDR;
    }
};

template<std::uint32_t ADDR, std::uint8_t IDX>
struct GpioPin {
public:
    inline void push_pull() {
        REG->MODER |= (1 << (IDX * 2));
    }

    inline void set(bool o) {
        if(o) {
            REG->ODR |= (1 << IDX);
        } else {
            REG->ODR &= ~(1 << IDX);
        }
    }
private:
    static constexpr RegisterBlock<GPIO_TypeDef, ADDR> REG{};
};

static_assert(hal::gpio::OutputPin<GpioPin<GPIOC_BASE, 8>>);

}
