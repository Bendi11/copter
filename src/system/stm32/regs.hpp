#pragma once

#include <cstdint>

namespace stm32 {

using addr_t = std::uint32_t;
using reg_t  = volatile std::uint32_t;

namespace regs {

inline void blocking_wait(std::uint32_t volatile *reg, std::uint32_t mask) {
    while((*reg & mask) == 0) {}
}

}

}
