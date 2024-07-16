project(project1)

file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp) # 把源文件名都赋值给变量SRC_LIST
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}) # 设置可执行文件的输出路径

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/ctp_api/lib) # 包含ctp_api动态库路径
add_executable(${PROJECT_NAME} ${SRC_LIST}) # 生成可执行程序
target_link_libraries(${PROJECT_NAME} thostmduserapi_se thosttraderapi_se) # 链接动态库
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # 引入头文件
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ctp_api/include) # 引入ctp_api头文件


