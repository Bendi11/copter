/// \file task.hpp
/// Definition for an asynchronous task that may be executed on the 

#include <coroutine>

template<typename T>
concept SuspendResult = std::same_as<T, std::suspend_always> || std::same_as<T, std::suspend_never>;

template<typename T>
concept Promise = requires(T v) {
    { v.get_return_object() } -> std::convertible_to<std::coroutine_handle<T>>;
    { v.initial_suspend() } noexcept -> SuspendResult;
    { v.final_suspend() } noexcept -> SuspendResult;
    { v.return_void() } noexcept;
};

template<typename T>
concept Task = requires() {
    { T::promise_type } -> Promise;
};
