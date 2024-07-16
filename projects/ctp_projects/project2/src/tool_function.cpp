#include "tool_function.h"



//获取string格式的当前时间，时分秒
string get_string_current_time()
{
	time_t time1 = time(&time1);
	char buff[64];
	strftime(buff, sizeof(buff), "%H:%M:%S", localtime(&time1));

	return buff;
};


//获取string格式的当前日期，年月日
string get_string_current_date()
{
	time_t time1 = time(&time1);
	char buff[64];
	strftime(buff, sizeof(buff), "%Y-%m-%d", localtime(&time1));

	return buff;
};


//获取int格式的当前日期，20220418格式
string get_int_string_current_date()
{
	time_t time1 = time(&time1);
	char buff[64];
	strftime(buff, sizeof(buff), "%Y%m%d", localtime(&time1));

	return buff;
};


//获取string格式的当前日期时间
string get_string_current_datetime()
{
	time_t time1 = time(&time1);
	char buff[64];
	strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", localtime(&time1));

	return buff;
};