cmake_minimum_required(VERSION 2.8.12)
project(pclwrapper)

find_package(PCL 1.10 REQUIRED)
find_package(VTK 8.0 REQUIRED)
#find_package(pybind11 REQUIRED)




#include(${VTK_USE_FILE})
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_subdirectory(pybind11)
pybind11_add_module(pclwrapper src/main.cpp)
target_link_libraries (pclwrapper PRIVATE ${PCL_LIBRARIES})
