set(src_dirs
        src
   )

set(include_dirs
        include
         )

set(requires
            driver)
idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++11)