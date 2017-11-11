cmake_minimum_required (VERSION 2.8)

option (test "Build all tests." OFF)

project (libscoa C CXX)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions (-Wall -Wextra -pedantic -lpthread -std=c++11)

include_directories ("${CMAKE_SOURCE_DIR}/include")

file (GLOB libscoa_src "src/*.cc")

add_library (libscoa_shlib SHARED ${libscoa_src})
install (TARGETS libscoa_shlib DESTINATION /usr/lib)

# if (test)
#   add_subdirectory (third_party/googletest)
#   enable_testing ()
#   include_directories (${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#   add_executable (test_main tests/test_main.cc)
#   target_link_liraries (test_main gtest gtest_main)
#   target_link_liraries (test_main libscoa_shlib)
#   add_test(NAME test-main COMMAND test_main)
# endif()
