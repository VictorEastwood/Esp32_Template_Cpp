#ifndef BSP_GPIO_HPP
#define BSP_GPIO_HPP

#ifdef __cplusplus
extern "C"
{
#endif

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

#ifdef __cplusplus
}
#endif
namespace BSP
{
    class GPIO
    {
    public:
        esp_err_t set_level(uint32_t set_level);
        GPIO(gpio_num_t pin, gpio_mode_t mode);
        ~GPIO();

    private:
        gpio_num_t pin;   // GPIO pin number
        gpio_mode_t mode; // GPIO mode (input, output, etc.)
    };
}

#endif // BSP_GPIO_HPP
