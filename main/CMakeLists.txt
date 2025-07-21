idf_component_register(SRCS "src/main.cpp"
                    INCLUDE_DIRS 
                    "include"
                    REQUIRES freertos driver esp_common log bsp)
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++11)