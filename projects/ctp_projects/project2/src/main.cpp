//该项目的作用：从ctp获取tick行情数据并保存到数据库中
#include "main_thread.h"



int main()
{
	//创建一个主线程类的对象
	main_thread main_thread1;

	//调用它的启动函数
	main_thread1.start_main_thread();

	system("pause");

	return 0;
};


