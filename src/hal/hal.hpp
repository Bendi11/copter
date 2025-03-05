#pragma once

#include <cstdint>
#include <concepts>
#include <type_traits>

namespace hal {

using DmaAddress = std::uint32_t volatile*;

template<typename T>
concept DmaSourceBuffer = requires(T const& v) {
    { v.dma_source_addr() } -> std::same_as<DmaAddress>;
};

}
