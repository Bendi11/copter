#pragma once

#include <cstdint>

namespace comptime {

/// Register block wrapper struct allowing compile-time conversion of addresses given by a HAL 
template<typename T, std::uint32_t ADDR>
struct RegisterBlock {
    inline constexpr T* operator->() const { return (T*)ADDR; }
};


}
