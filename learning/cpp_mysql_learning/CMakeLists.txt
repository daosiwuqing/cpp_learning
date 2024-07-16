project(cpp_mysql_learning)

file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp) # 把源文件名都赋值给变量SRC_LIST
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}) # 设置可执行文件的输出路径

link_directories(D:/Application/MySQL/mysql-8.0.28-winx64/lib) # 包含mysql动态库路径
add_executable(${PROJECT_NAME} ${SRC_LIST}) # 生成可执行程序
target_link_libraries(${PROJECT_NAME} libmysql) # 链接动态库
target_include_directories(${PROJECT_NAME} PUBLIC D:/Application/MySQL/mysql-8.0.28-winx64/include) # 引入mysql的头文件


