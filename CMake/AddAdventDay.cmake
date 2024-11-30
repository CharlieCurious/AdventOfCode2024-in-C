function(add_advent_day day_name)
    # Locate all .c files int the specified day's directory
    file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${day_name}/*.c")

    # Check if source files were found
    if(SOURCES)
        add_executable(${day_name} ${SOURCES})
        target_link_libraries(${day_name} PRIVATE common)
    else()
        message(FATAL_ERROR "No source files found for ${day_name}")
    endif()
endfunction()
