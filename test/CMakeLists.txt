set(TEST_NAME tests-for-channel)
set(SOURCE_FILES run_tests.c builders.c builders.h)
set(CMAKE_C_STANDARD 11)
enable_testing()
find_package(cgreen)

add_executable(${TEST_NAME})
target_sources(${TEST_NAME} PRIVATE ${SOURCE_FILES})
target_link_libraries(${TEST_NAME} src cgreen)
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
