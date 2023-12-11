#ifndef MICROPY_INCLUDED_STM32F4XX_HAL_CONF_H
#define MICROPY_INCLUDED_STM32F4XX_HAL_CONF_H

#include "boards/stm32f4xx_hal_conf_base.h"

// Oscillator values in Hz
#if WEACT_STUDIO_HSE_IS_8MHZ == 1
#define HSE_VALUE    ((uint32_t)8000000)
#else
#define HSE_VALUE    ((uint32_t)25000000)
#endif

#define LSE_VALUE (32768)
#define EXTERNAL_CLOCK_VALUE (12288000)

// Oscillator timeouts in ms
#define HSE_STARTUP_TIMEOUT (100)
#define LSE_STARTUP_TIMEOUT (5000)

#endif // MICROPY_INCLUDED_STM32F4XX_HAL_CONF_H
