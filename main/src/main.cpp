#include "main.hpp"

#define CONFIG_BLINK_GPIO GPIO_NUM_2
#define CONFIG_BLINK_PERIOD 1000


void blink_task()
{
    static const char *blink_thread_tag = "blink_thread";
    static uint8_t s_led_state = 0;
    BSP::GPIO led(CONFIG_BLINK_GPIO, GPIO_MODE_OUTPUT);
    while (1)
    {
        ESP_LOGI(blink_thread_tag, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        led.set_level(s_led_state);
        s_led_state = !s_led_state;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

extern "C" void app_main(void)
{
    static const char *main_tag = "main";
    std::cout << "Hello, World!" << std::endl;

    BSP::THREAD thread_1("blink_thread", 0, 2048, 5);
    // auto cfg = thread_1.reset_config("blink_thread", 0, 2048, 5);
    // esp_pthread_set_cfg(&cfg);
    thread_1.launch_thread(blink_task);
    // Create a FreeRTOS task for blinking the LED
    // std::thread blink_thread(blink_task);
    while (1)
    {
        ESP_LOGI(main_tag, "Main loop running...");
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}