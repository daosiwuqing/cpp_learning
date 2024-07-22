cmake_minimum_required(VERSION 3.15)

project(Option_pricing)

file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp) # 把源文件名都赋值给变量SRC_LIST

# 引用eigen库
set(Eigen3_DIR D:/Application/eigen3)
include_directories(${Eigen3_DIR})

# 引用pybind11库
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pybind11-master)

pybind11_add_module(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # 引入头文件


