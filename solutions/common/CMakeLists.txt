file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(common STATIC ${SOURCES})

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
