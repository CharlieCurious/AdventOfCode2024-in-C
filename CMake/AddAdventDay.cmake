function(add_advent_day day_name)
    set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/${day_name}/src")
    # Locate all .c files int the specified day's directory
    file(GLOB SOURCES "${src_dir}/*.c")

    # Separate main.c from other source files in order to create a lib and an excutable
    set(main_file "")
    set(lib_files "")

    foreach(file ${SOURCES})
        get_filename_component(filename ${file} NAME)
        if(filename STREQUAL "main.c")
            set(main_file ${file})
        else()
            list(APPEND lib_files ${file})
        endif()
    endforeach()

    if(NOT main_file)
        message(FATAL_ERROR "No main.c file found in ${src_dir}")
    endif()

    # If there are lib files, create a static library with all source files except main.c
    if (lib_files)
        add_library(${day_name}_lib STATIC ${lib_files})
        target_include_directories(${day_name}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${day_name}/headers)
        target_link_libraries(${day_name}_lib PUBLIC common)
        set(link_libs ${day_name}_lib)
    else()
        set(link_libs)
    endif()

    # Create the executable with main.c and link it to the library
    add_executable(${day_name} ${main_file})
    target_link_libraries(${day_name} PRIVATE ${link_libs} common)

endfunction()
