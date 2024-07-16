#ifndef __MAIN_THREAD_H__
#define __MAIN_THREAD_H__

#include <fstream>

#include "ctp_api.h"
#include "task_process_thread.h"



//主线程类
class main_thread
{
private:
	//结构
	account_info_struct* p_account_info_struct; //定义一个结构体类型的指针，空指针，使用之前需要初始化
	tick_data_struct* p_tick_data_struct; //tick数据队列
	mysql_connection_info_struct* p_mysql_connection_info_struct;

	//线程类
	mysql_tick_data_save_thread* p_mysql_tick_data_save_thread; //定时将tick数据存入mysql的线程

	//方法
	void print_new_message(string message); //打印信息，封装了cout <<
	void init_data_pointers(); //初始化结构体指针，用到的所有的结构体，在1个函数里面全部初始化
	void read_account_setting_file(); //读取ctp账户配置信息，通过本地配置文件实现
	void read_instruments_list_file(); //读取合约信息列表配置文件
	void read_mysql_setting_file(); //读取mysql连接配置信息
	bool connect_to_mysql(); //连接mysql
	bool disconnect_to_mysql(); //断开mysql
	void create_mysql_table();  //动态创建mysql表
	void connect_to_market_data_api(); //连接行情api
	void connect_to_trade_api(); //连接交易api
	void save_instrument_info(); //保存行情合约信息
	void create_task_process_thread(); //启动任务处理线程

public:
	void start_main_thread(); //主线程启动接口
};



#endif