#ifndef BSP_THREAD_HPP
#define BSP_THREAD_HPP

#ifdef __cplusplus
extern "C"
{
#endif
    // Include from C

#ifdef __cplusplus
}
#endif
// Include from C++
#include <thread>
#include <chrono>
#include <memory>
#include <string>
#include <sstream>
#include <esp_pthread.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <sdkconfig.h>
#include <iostream>
namespace BSP
{
    class THREAD
    {
    public:
        THREAD();
        THREAD(const char *name, int core_id, int stack, int prio);
        ~THREAD();
        esp_err_t set_cfg();
        esp_err_t set_cfg(const esp_pthread_cfg_t *cfg);
        esp_pthread_cfg_t reset_config(const char *name, int core_id, int stack, int prio);
        void launch_thread(void (*task_function)());
        void launch_thread(const esp_pthread_cfg_t *cfg, void (*task_function)());
        esp_pthread_cfg_t pthread_cfg;
    private:
    const char *name;
    int core_id;
    int stack;
    int prio;

    };

}
#endif
