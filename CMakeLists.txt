cmake_minimum_required(VERSION 3.0)

project(StackMachine CXX)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)


set(CMAKE_CXX_FLAGS "   ${CMAKE_CXX_FLAGS} -std=gnu++11")

set(CMAKE_CXX_FLAGS "   ${CMAKE_CXX_FLAGS} -DWINVER=0x0500")


add_subdirectory(src)
add_subdirectory(tests)