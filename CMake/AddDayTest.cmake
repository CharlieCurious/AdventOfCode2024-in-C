function(add_day_test day)

    # Discover all test files for the day
    file(GLOB test_files "${day}/*.c")

    # Add a test case for each file
    foreach(test_file ${test_files})
        # Extract file name without the path
        get_filename_component(test_name ${test_file} NAME_WE)

        add_executable(${test_name} ${test_file})

        target_link_libraries(${test_name} PRIVATE unity ${day}_lib)

        add_test(NAME ${test_name} COMMAND ${test_name})
    endforeach()

endfunction()
