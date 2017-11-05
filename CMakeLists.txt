cmake_minimum_required (VERSION 2.8)

option (test "Build all tests." OFF)

set (PROJECT_NAME libscoa)
project (${PROJECT_NAME} C CXX)

include_directories (include)

file (GLOB SOURCES "src/*.cc")

add_library (libscoa_shlib SHARED ${SOURCES})
install (TARGETS libscoa_shlib DESTINATION /usr/lib)

if (test)
  add_subdirectory (third_party/googletest)
  enable_testing ()
  include_directories (${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  add_executable (test_main test_main.cc)
  target_link_liraries (test_main gtest gtest_main)
  target_link_liraries (test_main libscoa_shlib)
  add_test(NAME test-main COMMAND test_main)
endif()
