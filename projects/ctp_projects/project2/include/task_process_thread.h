#ifndef __TASK_PROCESS_THREAD_H__
#define __TASK_PROCESS_THREAD_H__

#include "data_struct.h"
#include "tool_function.h"



//定时将tick数据存入mysql的线程
class mysql_tick_data_save_thread
{
private:
	int save_data_time_interval;

	void print_new_message(string message);
	void create_thread();
	bool connect_to_mysql();
	bool disconnect_to_mysql();
	void save_tick_data();

public:
	mysql_connection_info_struct* p_mysql_connection_info_struct;
	tick_data_struct* p_tick_data_struct;

	void start();
};



#endif