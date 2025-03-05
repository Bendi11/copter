#include "stm32f405xx.h"
#include <cstdint>

extern "C" std::uint32_t _STACK_START;
extern "C" void (*ResetHandler)();

const std::uint32_t ISR_TBL[] __attribute__((section(".isr_vector"))) = {
    _STACK_START,
    reinterpret_cast<std::uint32_t>(ResetHandler),
};
