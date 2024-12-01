include(CTest)

# Include the src directory to access src/common and other components
include_directories(${CMAKE_SOURCE_DIR}/solutions)

# Add common tests
add_subdirectory(common)

# Add the common test
add_day_test("${DAY}")
