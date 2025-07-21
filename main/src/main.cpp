#include "main.hpp"

#define CONFIG_BLINK_GPIO GPIO_NUM_2
#define CONFIG_BLINK_PERIOD 1000

static const char *TAG = "main";

static uint8_t s_led_state = 0;
extern "C" void app_main(void)
{
    std::cout << "Hello, World!" << std::endl;
    BSP::GPIO led(CONFIG_BLINK_GPIO, GPIO_MODE_OUTPUT);
    while (1)
    {
        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        led.set_level(s_led_state);
        s_led_state = !s_led_state;
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}