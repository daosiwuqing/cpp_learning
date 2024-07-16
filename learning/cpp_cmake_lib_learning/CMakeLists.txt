project(cpp_cmake_lib_learning)


add_subdirectory(common)
add_subdirectory(add)
add_subdirectory(sub)
add_subdirectory(calculator)


file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp) # 把源文件名都赋值给变量SRC_LIST
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}) # 设置可执行文件的输出路径


# 1、引用库文件
# 1.1、引用静态库和动态库
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/calculator/Debug) # 库路径
add_executable(${PROJECT_NAME} ${SRC_LIST}) # 生成可执行程序
target_link_libraries(${PROJECT_NAME} calculator) # 链接库
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/calculator/include) # 库的头文件

# 1.2、引用eigen库
# set(Eigen3_DIR D:/Application/eigen3)
# include_directories(${Eigen3_DIR})


