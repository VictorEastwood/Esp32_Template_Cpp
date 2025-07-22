#ifndef BSP_LEDC_HPP
#define BSP_LEDC_HPP

#ifdef __cplusplus
extern "C"
{
#endif
    // C Includes

#ifdef __cplusplus
}
#endif

#include "driver/ledc.h"
#include "esp_err.h"
// C++ Includes
namespace BSP
{
    class LEDC
    {
    public:
        LEDC();
        LEDC(int gpio_num, uint32_t frequency);
        LEDC(int gpio_num, uint32_t frequency, ledc_timer_t timer_num, ledc_channel_t channel_num);
        LEDC(const ledc_timer_config_t *timer_conf, const ledc_channel_config_t *channel_conf);
        ~LEDC();
        int timer_reconfig(const ledc_timer_config_t *timer_conf);
        int channel_reconfig(const ledc_channel_config_t *channel_conf);
        void set_duty(uint32_t duty);              // set duty[0, (2**duty_resolution)]
        void set_duty_percent(float duty_percent); // set duty percent[0, 1]
        void set_pulse_width(float ms);            // set pulse width in milliseconds[0,1/frequency* 1000]
        ledc_timer_config_t ledc_timer_cfg;
        ledc_channel_config_t ledc_channel_cfg;

    private:
    };
}

#endif
