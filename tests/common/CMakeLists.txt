# Glob all test files in common
file(GLOB_RECURSE COMMON_TESTS "${CMAKE_CURRENT_SOURCE_DIR}/test_*.c")

foreach(TEST_FILE ${COMMON_TESTS})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_FILE})

    target_link_libraries(${TEST_NAME} PRIVATE common)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
