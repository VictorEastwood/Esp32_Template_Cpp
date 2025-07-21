#include "bsp_gpio.hpp"
namespace BSP
{
    GPIO::GPIO(gpio_num_t init_pin, gpio_mode_t init_mode)
    {
        this->pin = init_pin;
        this->mode = init_mode;
        gpio_set_direction(init_pin, init_mode);
    }
    GPIO::~GPIO()
    {
        gpio_set_direction(this->pin, GPIO_MODE_DISABLE);
    }

    esp_err_t GPIO::set_level(uint32_t set_level)
    {
        return gpio_set_level(this->pin, set_level);
    }
}


