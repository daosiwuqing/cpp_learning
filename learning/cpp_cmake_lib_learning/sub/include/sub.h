﻿#ifndef __SUB_H__
#define __SUB_H__


// 在MSVC编译环境下所特有的宏定义
#ifdef DLL // 如果是生成动态库
#ifdef EXPORT // 如果是导出动态库
#define SUB_API __declspec(dllexport)
#else // 如果是导入动态库
#define SUB_API __declspec(dllimport)
#endif

#else // 如果是生成静态库
#define SUB_API
#endif

#include <iostream>



int SUB_API sub(int x, int y);



#endif