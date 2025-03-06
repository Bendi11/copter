#pragma once

#include <cstdint>
#include "hal/gpio/pin.hpp"
#include "system/comptime.hpp"

namespace stm32::gpio {

namespace _ {

using reg_t = volatile std::uint32_t;

struct GPIO {
  reg_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  reg_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  reg_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  reg_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  reg_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  reg_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  reg_t BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
  reg_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  reg_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
};

}

template<std::uint32_t ADDR>
struct Block;

template<std::uint32_t ADDR, std::uint8_t IDX>
struct Pin {
public:
    inline constexpr void push_pull() {
        REG->MODER |= (1 << (IDX * 2));
    }
    

    [[gnu::always_inline]]
    inline constexpr void push_pull(bool o) {
        REG->BSRR |= (1 << IDX) << ((std::uint8_t)(!o) << 4);
    }
private:
    inline constexpr Pin() {}
    friend struct Block<ADDR>;

    static inline constexpr comptime::RegisterBlock<_::GPIO, ADDR> REG{};
};

static_assert(hal::gpio::PushPullPin<Pin<0, 0>>);

template<std::uint32_t ADDR, std::uint8_t IDX>
struct PushPullPin : public Pin<ADDR, IDX> {
    
};

template<std::uint32_t ADDR>
struct Block {
public:
    template<std::uint8_t IDX>
    static inline constexpr Pin<ADDR, IDX> pin(void) { return Pin<ADDR, IDX>{}; }
};


}
