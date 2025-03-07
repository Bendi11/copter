#pragma once

#include <cstdint>
#include "hal/gpio/pin.hpp"
#include "hal/types.hpp"
#include "system/comptime.hpp"
#include "system/stm32/regs.hpp"

namespace stm32::gpio {

namespace _ {

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

struct GpioRegBlockDescriptor {
    addr_t ADDR;
};

template<typename T>
types::Empty GpioRegBlockData;

template<typename T>
concept GpioBlock = requires() {
    { GpioRegBlockData<T> } -> std::same_as<GpioRegBlockDescriptor>;
};

template<GpioRegBlockDescriptor Regs>
struct Block;

template<GpioRegBlockDescriptor Regs, std::uint8_t IDX>
struct PushPullPin;

template<GpioRegBlockDescriptor Regs, std::uint8_t IDX>
struct Pin {
public:
    [[gnu::always_inline]]
    inline constexpr PushPullPin<Regs, IDX> mode_push_pull() const {
        REG->MODER |= (1 << (IDX << 1));
        return PushPullPin<Regs, IDX>();
    }
protected:
    inline constexpr Pin() {}
    static inline constexpr comptime::RegisterBlock<_::GPIO, Regs.ADDR> REG{};
private:
    friend struct Block<Regs>;
};

template<GpioRegBlockDescriptor Regs, std::uint8_t IDX>
struct PushPullPin : public Pin<Regs, IDX> {
public:
    [[gnu::always_inline]]
    inline constexpr void push_pull(bool output) const {
        Pin<Regs, IDX>::REG->BSRR |= (1 << IDX) << (!output << 4);
    }
private:
    PushPullPin() {}
    friend struct Pin<Regs, IDX>;
};


template<GpioRegBlockDescriptor ADDR>
struct Block {
public:
    template<std::uint8_t IDX>
    static inline constexpr Pin<ADDR, IDX> pin(void) { return Pin<ADDR, IDX>{}; }
};


}
