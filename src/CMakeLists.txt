add_subdirectory(common)

if(DAY)
    add_advent_day("${DAY}")
else()
    message(FATAL_ERROR "DAY is not set or invalid.")
endif()
