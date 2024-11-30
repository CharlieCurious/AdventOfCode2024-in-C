function(add_day_test day)
    add_executable(test_${day} ${day}/test_${day}.c)

    target_link_libraries(test_${day} PRIVATE unity)

    add_test(NAME test_${day} COMMAND test_${day})
endfunction()
