cmake_minimum_required(VERSION 2.8)
project( Test )


#	Compile and set up google test
add_subdirectory(gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#	include relevant include/source dirs
include_directories(${App_SOURCE_DIR} ${App_BINARY_DIR})
include_directories(${Client_SOURCE_DIR})
include_directories(${ClientLib_SOURCE_DIR})
include_directories(${GameEngineLib_SOURCE_DIR})

add_executable(app_test main_test.cpp shiptest.cpp SmallGameShipTest.cpp FieldTest.cpp)
target_link_libraries(app_test gtest gtest_main messages lib_client lib_game_engine)
add_test(app_test app_test)
