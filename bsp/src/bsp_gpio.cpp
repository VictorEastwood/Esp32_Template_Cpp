#include "bsp_gpio.hpp"

//example of GPIO class implementation
// void blink_task()
// {
//     static uint8_t s_led_state = 0;
//         // 获取当前tick时间作为基准
//     BSP::GPIO led(CONFIG_BLINK_GPIO, GPIO_MODE_OUTPUT);
//     while (1)
//     {
//         
//         led.set_level(s_led_state);
//         s_led_state = !s_led_state;
//         std::this_thread::sleep_for(std::chrono::milliseconds(500));

//     }
// }
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


