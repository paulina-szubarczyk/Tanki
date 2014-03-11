
add_subdirectory(gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(app_test main_test.cpp)
target_link_libraries(app_test gtest gtest_main)
add_test(app_test app_test)
