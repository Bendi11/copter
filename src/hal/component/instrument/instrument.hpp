/// \file instrument.hpp 
/// Instrument interface declarations that attempt to provide an abstract and efficient interface for collecting sensor data

#pragma once
#include <concepts>

#include "hal/task/task.hpp"

template<typename T>
concept Instrument = requires(T v) {
    { v.read() } -> Task;
};
