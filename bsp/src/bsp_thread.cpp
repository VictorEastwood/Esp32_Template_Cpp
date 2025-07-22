#include "bsp_thread.hpp"

// // example usage:
// #include "bsp_thread.hpp"
// void my_task_function()
// {
//     // Task code here
//     TickType_t xLastWakeTime = xTaskGetTickCount();
//     while (1)
//     {
//         // std::this_thread::sleep_for(std::chrono::milliseconds(1));
//         vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
//     }
// }
// int main()
// {
//     BSP::THREAD my_thread("my_thread", 0, 2048, 5);
//     my_thread.launch_thread(my_task_function);
//     while (1)
//     {
//         // Main loop code here
//     }
//     return 0;
// }

namespace BSP
{
    THREAD::THREAD()
    {
        name = "default_task";
        core_id = 0;
        stack = 2048;
        prio = 5;
        pthread_cfg = esp_pthread_get_default_config();
    }
    THREAD::THREAD(const char *name, int core_id, int stack, int prio)
        : name(name), core_id(core_id), stack(stack), prio(prio)
    {
        pthread_cfg = esp_pthread_get_default_config();
        pthread_cfg.thread_name = name;
        pthread_cfg.pin_to_core = core_id;
        pthread_cfg.stack_size = stack;
        pthread_cfg.prio = prio;
    }
    THREAD::~THREAD() {};

    esp_pthread_cfg_t THREAD::reset_config(const char *name, int core_id, int stack, int prio)
    {
        esp_pthread_cfg_t cfg = esp_pthread_get_default_config();
        cfg.thread_name = name;
        cfg.pin_to_core = core_id;
        cfg.stack_size = stack;
        cfg.prio = prio;
        pthread_cfg = cfg; // Update the class member with
        return cfg;
    }
    esp_err_t THREAD::set_cfg()
    {
        return esp_pthread_set_cfg(&pthread_cfg);
    }

    esp_err_t THREAD::set_cfg(const esp_pthread_cfg_t *cfg)
    {
        pthread_cfg = *cfg;
        return esp_pthread_set_cfg(&pthread_cfg);
    }
    void THREAD::launch_thread(void (*task_function)())
    {
        esp_pthread_set_cfg(&pthread_cfg);
        // Create a FreeRTOS task for the thread
        std::thread thread(task_function);
        // Detach the thread to allow it to run independently
        thread.detach();
    }
    void THREAD::launch_thread(const esp_pthread_cfg_t *cfg, void (*task_function)())
    {
        pthread_cfg = *cfg;
        esp_pthread_set_cfg(&pthread_cfg);
        std::thread thread(task_function);
        thread.detach();
    }
}