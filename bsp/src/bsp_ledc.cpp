#include "bsp_ledc.hpp"


// void blink_task()
// {
//     static const char *blink_task_tag = "blink_task";
//     static float s_led_state = 0;
//     static int8_t flag = 1; // Flag to control the direction of duty cycle change
//         // 获取当前tick时间作为基准
//     BSP::LEDC ledc((2), (50)); // Initialize LEDC with GPIO and frequency
//     while (1)
//     {
//         ESP_LOGI(blink_task_tag, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
//         ledc.set_duty_percent(s_led_state); // Set duty cycle
//         s_led_state = s_led_state + (float)0.01 * flag;
//         if (s_led_state >= 1.0)
//         {
//             s_led_state = 1.0;
//             flag = -1; // Reverse direction
//         }
//         else if(s_led_state <= 0.0)
//         {
//             s_led_state = 0.0;
//             flag = 1; // Reverse direction
//         }
//         std::this_thread::sleep_for(std::chrono::milliseconds(5));

//     }
// }


#define LEDC_TIMER_DEFAULT LEDC_TIMER_0
#define LEDC_MODE_DEFAULT LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO (2) // Define the output GPIO
#define LEDC_CHANNEL_DEFAULT LEDC_CHANNEL_0
#define LEDC_DUTY_RES_DEFAULT LEDC_TIMER_14_BIT // Set duty resolution to 14 bits
#define LEDC_DUTY_DEFAULT (8192)                // Set duty to 50%. (2 ** 14) * 50% = 8192
#define LEDC_FREQUENCY_DEFAULT (50)             // Frequency in Hertz. Set frequency at  50Hz(servo motor)

namespace BSP
{

    LEDC::LEDC()
    {
        // Initialize the timer configuration
        ledc_timer_cfg.speed_mode = LEDC_MODE_DEFAULT;
        ledc_timer_cfg.duty_resolution = LEDC_DUTY_RES_DEFAULT;
        ledc_timer_cfg.freq_hz = LEDC_FREQUENCY_DEFAULT;
        ledc_timer_cfg.clk_cfg = LEDC_AUTO_CLK; // Automatically select the clock source
        ledc_timer_cfg.timer_num = LEDC_TIMER_DEFAULT;
        ledc_timer_cfg.deconfigure = false; // Do not de-configure the timer
        // Configure the channel
        ledc_channel_cfg.speed_mode = LEDC_MODE_DEFAULT;
        ledc_channel_cfg.channel = LEDC_CHANNEL_DEFAULT;
        ledc_channel_cfg.timer_sel = LEDC_TIMER_DEFAULT;
        ledc_channel_cfg.intr_type = LEDC_INTR_DISABLE;
        ledc_channel_cfg.gpio_num = LEDC_OUTPUT_IO;
        ledc_channel_cfg.duty = LEDC_DUTY_DEFAULT;
        ledc_channel_cfg.hpoint = 0; // Default hpoint value
        ledc_timer_config(&ledc_timer_cfg);
        ledc_channel_config(&ledc_channel_cfg);
    }
    LEDC::LEDC(int gpio_num, uint32_t frequency)
    {
        // Initialize the timer configuration
        ledc_timer_cfg.speed_mode = LEDC_MODE_DEFAULT;
        ledc_timer_cfg.duty_resolution = LEDC_DUTY_RES_DEFAULT;
        ledc_timer_cfg.freq_hz = frequency;
        ledc_timer_cfg.clk_cfg = LEDC_AUTO_CLK; // Automatically select the clock source
        ledc_timer_cfg.timer_num = LEDC_TIMER_DEFAULT;
        ledc_timer_cfg.deconfigure = false; // Do not de-configure the timer
        // Configure the channel
        ledc_channel_cfg.speed_mode = LEDC_MODE_DEFAULT;
        ledc_channel_cfg.channel = LEDC_CHANNEL_DEFAULT;
        ledc_channel_cfg.timer_sel = LEDC_TIMER_DEFAULT;
        ledc_channel_cfg.intr_type = LEDC_INTR_DISABLE;
        ledc_channel_cfg.gpio_num = gpio_num;
        ledc_channel_cfg.duty = LEDC_DUTY_DEFAULT;
        ledc_channel_cfg.hpoint = 0; // Default hpoint value
        ledc_timer_config(&ledc_timer_cfg);
        ledc_channel_config(&ledc_channel_cfg);
    }
    LEDC::LEDC(int gpio_num, uint32_t frequency, ledc_timer_t timer_num, ledc_channel_t channel_num)
    {
        // Initialize the timer configuration
        ledc_timer_cfg.speed_mode = LEDC_MODE_DEFAULT;
        ledc_timer_cfg.duty_resolution = LEDC_DUTY_RES_DEFAULT;
        ledc_timer_cfg.freq_hz = frequency;
        ledc_timer_cfg.clk_cfg = LEDC_AUTO_CLK; // Automatically select the clock source
        ledc_timer_cfg.timer_num = timer_num;
        ledc_timer_cfg.deconfigure = false; // Do not de-configure the timer
        // Configure the channel
        ledc_channel_cfg.speed_mode = LEDC_MODE_DEFAULT;
        ledc_channel_cfg.channel = channel_num;
        ledc_channel_cfg.timer_sel = timer_num;
        ledc_channel_cfg.intr_type = LEDC_INTR_DISABLE;
        ledc_channel_cfg.gpio_num = gpio_num;
        ledc_channel_cfg.duty = LEDC_DUTY_DEFAULT;
        ledc_channel_cfg.hpoint = 0; // Default hpoint value
        ledc_timer_config(&ledc_timer_cfg);
        ledc_channel_config(&ledc_channel_cfg);
    }
    LEDC::LEDC(const ledc_timer_config_t *timer_conf, const ledc_channel_config_t *channel_conf)
    {
        if (timer_conf != nullptr)
        {
            ledc_timer_cfg = *timer_conf;
        }
        if (channel_conf != nullptr)
        {
            ledc_channel_cfg = *channel_conf;
        }
        ledc_timer_config(&ledc_timer_cfg);
        ledc_channel_config(&ledc_channel_cfg);
    }
    LEDC::~LEDC()
    {
    }
    int LEDC::timer_reconfig(const ledc_timer_config_t *timer_conf)
    {
        if (timer_conf == nullptr)
        {
            return ESP_ERR_INVALID_ARG;
        }
        ledc_timer_cfg = *timer_conf;
        return ledc_timer_config(&ledc_timer_cfg);
    }
    int LEDC::channel_reconfig(const ledc_channel_config_t *channel_conf)
    {
        if (channel_conf == nullptr)
        {
            return ESP_ERR_INVALID_ARG;
        }
        ledc_channel_cfg = *channel_conf;
        return ledc_channel_config(&ledc_channel_cfg);
    }
    void LEDC::set_duty(uint32_t duty)
    {
        // 检查占空比是否超出范围
        uint32_t max_duty = (1 << ledc_timer_cfg.duty_resolution) - 1;
        if (duty > max_duty)
        {
            duty = max_duty; // 限制占空比在最大值范围内
        }

        // 设置占空比
        ESP_ERROR_CHECK(ledc_set_duty(ledc_channel_cfg.speed_mode, ledc_channel_cfg.channel, duty));
        ESP_ERROR_CHECK(ledc_update_duty(ledc_channel_cfg.speed_mode, ledc_channel_cfg.channel));

        // 更新占空比使其生效
    }
    void LEDC::set_duty_percent(float duty_percent)
    {
        // 检查百分比范围
        if (duty_percent < 0.0f )
        {
            duty_percent = 0.0f; // 限制占空比在最小值范围内
        }
        else if (duty_percent > 1.0f)
        {
            duty_percent = 1.0f; // 限制占空比在最大值范围内
        }

        // 计算实际占空比值
        uint32_t max_duty = (1 << ledc_timer_cfg.duty_resolution) - 1;
        uint32_t duty = (uint32_t)(duty_percent * max_duty);
        ESP_ERROR_CHECK(ledc_set_duty(ledc_channel_cfg.speed_mode, ledc_channel_cfg.channel, duty)  );
        ESP_ERROR_CHECK(ledc_update_duty(ledc_channel_cfg.speed_mode, ledc_channel_cfg.channel));
    }
    void LEDC::set_pulse_width(float ms)
    {
        // 计算占空比
        float duty_percent = ms / (1000.0f / ledc_timer_cfg.freq_hz);
        if (duty_percent < 0.0f )
        {
            duty_percent = 0.0f; // 限制占空比在最小值范围内
        }
        else if (duty_percent > 1.0f)
        {
            duty_percent = 1.0f; // 限制占空比在最大值范围内
        }
        ESP_ERROR_CHECK(ledc_set_duty(ledc_channel_cfg.speed_mode, ledc_channel_cfg.channel, (uint32_t)(duty_percent * ((1 << ledc_timer_cfg.duty_resolution) - 1))));
        ESP_ERROR_CHECK(ledc_update_duty(ledc_channel_cfg.speed_mode, ledc_channel_cfg.channel));
    }
}
