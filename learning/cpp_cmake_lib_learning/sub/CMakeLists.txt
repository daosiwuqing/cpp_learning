project(sub)

file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp) # 把源文件名都赋值给变量SRC_LIST
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}) # 设置生成库文件时的输出路径

# MSVC环境下制作库文件
# add_definitions(-DDLL) # 宏定义，如果是生成动态库
# add_definitions(-DEXPORT) # 宏定义，如果是导出动态库
link_directories(../common/Debug) # 包含静态库路径
add_library(${PROJECT_NAME} STATIC ${SRC_LIST}) # 静态库STATIC，动态库SHARED
target_link_libraries(${PROJECT_NAME} PUBLIC common) # 链接静态库
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ../common/include)


