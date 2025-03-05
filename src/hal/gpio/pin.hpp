#pragma once

#include <type_traits>
#include <concepts>
#include <utility>

namespace hal {

namespace gpio {

template<typename T>
concept OutputPin = requires(T& v) {
    { v.set(std::declval<bool>()) };
};

}

}
