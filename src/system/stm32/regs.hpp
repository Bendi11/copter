#pragma once

#include <cstdint>

namespace stm32 {

namespace regs {

inline void blocking_wait(std::uint32_t volatile *reg, std::uint32_t mask) {
    while((*reg & mask) == 0) {}
}

}

}
