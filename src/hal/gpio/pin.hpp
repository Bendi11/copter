#pragma once

#include <type_traits>
#include <concepts>
#include <utility>

namespace hal {

namespace gpio {

/// 
template<typename T>
concept PushPullPin = requires(T& v) {
    { v.push_pull(std::declval<bool>()) };
};

}

}
