cmake_minimum_required(VERSION 3.0)
project(libscoa C CXX)

# Main library
add_library(libscoa_lib include/libscoa.h)

# Unit testing using GTest
enable_testing()
find_package(GTest REQUIRED)

add_executable(test_suite test/test.cc)
target_link_libraries(test_suite GTest::GTest GTest::Main)

add_test(libscoa_test test_suite)
