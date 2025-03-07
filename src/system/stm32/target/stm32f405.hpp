#include "stm32f405xx.h"
#include "system/stm32/regs.hpp"
#include "system/stm32/gpio.hpp"

#include "system/comptime.hpp"

namespace stm32 {

namespace f405 {

namespace _ {

template<addr_t ADDR>
struct RccEnMsk;

template<> struct RccEnMsk<GPIOA_BASE> { static inline constexpr std::uint32_t MSK = RCC_AHB1ENR_GPIOAEN_Msk; };
template<> struct RccEnMsk<GPIOB_BASE> { static inline constexpr std::uint32_t MSK = RCC_AHB1ENR_GPIOBEN_Msk; };
template<> struct RccEnMsk<GPIOC_BASE> { static inline constexpr std::uint32_t MSK = RCC_AHB1ENR_GPIOCEN_Msk; };
template<> struct RccEnMsk<GPIOD_BASE> { static inline constexpr std::uint32_t MSK = RCC_AHB1ENR_GPIODEN_Msk; };

}

template<addr_t ADDR>
static constexpr std::uint32_t RccEnableMask = _::RccEnMsk<ADDR>::MSK;

struct Stm32F405Regs {
    template<addr_t ADDR>
    inline constexpr gpio::Block<ADDR> enable_gpio() const {
        rcc->AHB1ENR |= RccEnableMask<ADDR>;
        return gpio::Block<ADDR>();
    }

    static inline constexpr comptime::RegisterBlock<RCC_TypeDef, RCC_BASE> rcc{};
};

}

}
