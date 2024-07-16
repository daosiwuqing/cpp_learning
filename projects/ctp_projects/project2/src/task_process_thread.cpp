#include "task_process_thread.h"

#define DATABUFFSIZE 1024



//1、mysql_tick_data_save_thread类
//1.1.1、打印消息
void mysql_tick_data_save_thread::print_new_message(string message)
{
	cout << message.c_str() << endl;
};


//1.1.2、任务处理主函数
void mysql_tick_data_save_thread::create_thread()
{
	//设定保存数据间隔，5秒保存一次
	save_data_time_interval = 5;
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(save_data_time_interval));
		if (connect_to_mysql())
		{
			//保存tick数据
			print_new_message(get_string_current_time() + ":开始保存tick数据...");
			save_tick_data();
			print_new_message(get_string_current_datetime() + ":tick数据保存完成！");

			disconnect_to_mysql();
		};
	};
};


//1.1.3、启动线程
void mysql_tick_data_save_thread::start()
{
	std::thread thread(&mysql_tick_data_save_thread::create_thread, this);
	thread.detach();
};


//1.2.1、连接mysql
bool mysql_tick_data_save_thread::connect_to_mysql()
{
	char* user_name = (char*)(p_mysql_connection_info_struct->user_name).data();
	char* password = (char*)(p_mysql_connection_info_struct->password).data();
	char* host_name = (char*)(p_mysql_connection_info_struct->host_name).data();
	char* database_name = (char*)(p_mysql_connection_info_struct->database_name).data();
	int port_num = p_mysql_connection_info_struct->port_num;

	//初始化mysql对象
	p_mysql_connection_info_struct->p_mysql_object = mysql_init(NULL);

	//连接数据库及database
	if (mysql_real_connect(p_mysql_connection_info_struct->p_mysql_object, host_name, user_name, password, database_name, port_num, NULL, 0))
	{
		//关闭自动commit
		mysql_autocommit(p_mysql_connection_info_struct->p_mysql_object, 0);
		//设置编码格式，保存中文字段应设置为UTF8
		mysql_query(p_mysql_connection_info_struct->p_mysql_object, "SET NAMES UTF8");
		//关闭安全模式
		mysql_query(p_mysql_connection_info_struct->p_mysql_object, "SET SQL_SAFE_UPDATES = 0");
		//增加连接超时时间
		mysql_query(p_mysql_connection_info_struct->p_mysql_object, "SET INTERACTIVE_TIMEOUT = 28800");

		print_new_message("mysql数据库连接成功！");

		return true;
	}
	else
	{
		print_new_message("mysql数据库连接失败！");
		print_new_message(mysql_error(p_mysql_connection_info_struct->p_mysql_object));
		mysql_close(p_mysql_connection_info_struct->p_mysql_object);

		return false;
	};
};


//1.2.2、保存tick数据
void mysql_tick_data_save_thread::save_tick_data()
{
	//开启事务
	mysql_query(p_mysql_connection_info_struct->p_mysql_object, "START TRANSACTION");

	//将数据复制到本地并清空原始数据
	p_tick_data_struct->mut_tick_data.lock();
	vector<tick_data_object> vec_tick_data = p_tick_data_struct->vec_tick_data;
	p_tick_data_struct->vec_tick_data.clear();
	p_tick_data_struct->mut_tick_data.unlock();

	//存入mysql
	for (tick_data_object tick_data_object : vec_tick_data)
	{
		string update_time = tick_data_object.update_time + "." + tick_data_object.update_milli_second;

		char buff[DATABUFFSIZE] = { 0 };
		snprintf(buff, DATABUFFSIZE, "insert into %s values('%s','%s','%s',%.1f,%.1f,%.1f,%i,%i,%i,%f);",
			p_mysql_connection_info_struct->tick_data_table_name.c_str(),
			tick_data_object.instrument_id.c_str(), tick_data_object.update_date.c_str(), update_time.c_str(),
			tick_data_object.bid_price1, tick_data_object.ask_price1, tick_data_object.last_price,
			tick_data_object.bid_volume1, tick_data_object.ask_volume1, tick_data_object.last_traded_volume,
			tick_data_object.open_interest);

		//若出错则打印错误信息
		if (mysql_query(p_mysql_connection_info_struct->p_mysql_object, buff))
		{
			printf(mysql_error(p_mysql_connection_info_struct->p_mysql_object));
			continue;
		};
	};

	//全部保存完毕后执行一次commit
	mysql_commit(p_mysql_connection_info_struct->p_mysql_object);
};


//1.2.3、断开mysql
bool mysql_tick_data_save_thread::disconnect_to_mysql()
{
	mysql_close(p_mysql_connection_info_struct->p_mysql_object);

	return true;
};