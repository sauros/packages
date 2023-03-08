cmake_minimum_required(VERSION 3.5)
project (net)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

set(CMAKE_CXX_STANDARD 20)

add_library(net_lib SHARED package.cpp)
set_target_properties(net_lib PROPERTIES PREFIX "" SUFFIX ".lib" OUTPUT_NAME "net")
