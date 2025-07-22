#include "main.hpp"

#define CONFIG_BLINK_GPIO GPIO_NUM_2
#define CONFIG_BLINK_PERIOD 1000


// void blink_task()
// {
//     static const char *blink_task_tag = "blink_task";
//     static uint8_t s_led_state = 0;
//         // 获取当前tick时间作为基准
//     BSP::GPIO led(CONFIG_BLINK_GPIO, GPIO_MODE_OUTPUT);
//     while (1)
//     {
//         ESP_LOGI(blink_task_tag, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
//         led.set_level(s_led_state);
//         s_led_state = !s_led_state;
//         std::this_thread::sleep_for(std::chrono::milliseconds(500));

//     }
// }
void blink_task()
{
    static const char *blink_task_tag = "blink_task";
    static float s_led_state = 0;
    static int8_t flag = 1; // Flag to control the direction of duty cycle change
        // 获取当前tick时间作为基准
    BSP::LEDC ledc((2), (50)); // Initialize LEDC with GPIO and frequency
    while (1)
    {
        ESP_LOGI(blink_task_tag, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        ledc.set_duty_percent(s_led_state); // Set duty cycle
        s_led_state = s_led_state + (float)0.01 * flag;
        if (s_led_state >= 1.0)
        {
            s_led_state = 1.0;
            flag = -1; // Reverse direction
        }
        else if(s_led_state <= 0.0)
        {
            s_led_state = 0.0;
            flag = 1; // Reverse direction
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));

    }
}
extern "C" void app_main(void)
{
    static const char *main_tag = "main";
    std::cout << "Hello, World!" << std::endl;

    BSP::THREAD blink_task_thread("blink_task", 0, 2048, 5);
    blink_task_thread.launch_thread(blink_task);
    // Create a FreeRTOS task for blinking the LED
    while (1)
    {
        ESP_LOGI(main_tag, "Main loop running...");
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}