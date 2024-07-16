#ifndef __ADD_H__
#define __ADD_H__


// 在MSVC编译环境下所特有的宏定义
#ifdef DLL // 如果是生成动态库
#ifdef EXPORT // 如果是导出动态库
#define ADD_API __declspec(dllexport)
#else // 如果是导入动态库
#define ADD_API __declspec(dllimport)
#endif

#else // 如果是生成静态库
#define ADD_API
#endif

#include <iostream>



int ADD_API add(int x, int y);



#endif