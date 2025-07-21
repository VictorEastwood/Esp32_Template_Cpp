idf_component_register(SRCS "src/main.cpp"
                    INCLUDE_DIRS "include")
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++11)