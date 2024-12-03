function(add_day_test day)

    # Discover all test files for the day
    file(GLOB test_files "${day}/*.c")

    # Check if ${day}_lib exists
    set(day_lib_exists OFF)
    if(TARGET ${day}_lib)
        set(day_lib_exists ON)
    endif()

    # Add a test case for each file
    foreach(test_file ${test_files})
        # Extract file name without the path
        get_filename_component(test_name ${test_file} NAME_WE)

        add_executable(${test_name} ${test_file})

        # Conditionally link ${day}_lib if it exists
        if(day_lib_exists)
            target_link_libraries(${test_name} PRIVATE unity ${day}_lib)
        else()
            target_link_libraries(${test_name} PRIVATE unity)
        endif()

        add_test(NAME ${test_name} COMMAND ${test_name})
    endforeach()

endfunction()
