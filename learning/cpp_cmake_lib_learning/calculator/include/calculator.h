#ifndef __CALC_H__
#define __CALC_H__


// 在MSVC编译环境下所特有的宏定义
#ifdef DLL // 如果是生成动态库
#ifdef EXPORT // 如果是导出动态库
#define CALC_API __declspec(dllexport)
#else // 如果是导入动态库
#define CALC_API __declspec(dllimport)
#endif

#else // 如果是生成静态库
#define CALC_API
#endif



class CALC_API Calculator
{
public:
    int calc_add(int x, int y);
    int calc_sub(int x, int y);
};



#endif