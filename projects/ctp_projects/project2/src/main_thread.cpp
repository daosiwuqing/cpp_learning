#include "main_thread.h"

#define DATABUFFSIZE 1024



//主启动函数
void main_thread::start_main_thread()
{
	print_new_message("ctp_tick数据存储系统开始启动...");

	//初始化指针
	init_data_pointers();

	//读取配置文件
	read_account_setting_file();
	read_mysql_setting_file();

	//创建当前所有的mysql表
	create_mysql_table();

	print_new_message("开始连接ctp...");

	//连接交易账号
	connect_to_trade_api();

	//等待交易api连接完成
	while (true)
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		if (p_account_info_struct->b_is_trade_api_connected)
		{
			break;
		};
	};

	//连接行情api
	connect_to_market_data_api();

	//等待行情api连接完成
	while (true)
	{
	this_thread::sleep_for(std::chrono::milliseconds(1000));
		if (p_account_info_struct->b_is_market_data_api_connected)
		{
			break;
		};
	};

	//保存期货合约信息
	save_instrument_info();

	//启动任务处理线程
	create_task_process_thread();

	print_new_message("ctp_tick数据存储系统启动完成！");
};


//打印信息
void main_thread::print_new_message(string message)
{
	cout << message.c_str() << endl;
};


//初始化结构体指针
void main_thread::init_data_pointers()
{
	p_account_info_struct = new account_info_struct;
	p_account_info_struct->b_is_trade_api_connected = false;
	p_account_info_struct->b_is_market_data_api_connected = false;

	p_tick_data_struct = new tick_data_struct;
	p_mysql_connection_info_struct = new mysql_connection_info_struct;
};


//读取ctp账户配置信息
void main_thread::read_account_setting_file()
{
	ifstream in_file("D:/LearningAndWorking/VSCode/cpp/ctp_projects/project2/others/account_setting2.txt", ios::in); //读取了txt的配置文件
	if (!in_file)
	{
		print_new_message("账户信息配置文件不存在");

		return;
	};
	in_file >> p_account_info_struct->investor_id
		>> p_account_info_struct->password >> p_account_info_struct->broker_id
		>> p_account_info_struct->market_data_front_addr >> p_account_info_struct->trade_front_addr
		>> p_account_info_struct->app_id >> p_account_info_struct->auth_code;
	in_file.close();
};


//读取合约列表配置文件
void main_thread::read_instruments_list_file()
{

};


//读取mysql连接配置信息
void main_thread::read_mysql_setting_file()
{
	ifstream in_file("D:/LearningAndWorking/VSCode/cpp/ctp_projects/project2/others/mysql_setting.txt", ios::in);
	if (!in_file)
	{
		print_new_message("mysql配置文件不存在！");
		return;
	};
	in_file >> p_mysql_connection_info_struct->user_name
		>> p_mysql_connection_info_struct->password >> p_mysql_connection_info_struct->host_name
		>> p_mysql_connection_info_struct->database_name >> p_mysql_connection_info_struct->port_num;
	in_file.close();
};


//连接mysql
bool main_thread::connect_to_mysql()
{
	//数据类型转换
	char* user_name = (char*)(p_mysql_connection_info_struct->user_name).data();
	char* password = (char*)(p_mysql_connection_info_struct->password).data();
	char* host_name = (char*)(p_mysql_connection_info_struct->host_name).data();
	char* database_name = (char*)(p_mysql_connection_info_struct->database_name.data());
	int port_num = p_mysql_connection_info_struct->port_num;

	//初始化mysql对象
	p_mysql_connection_info_struct->p_mysql_object = mysql_init(NULL);

	//连接数据库及database
	if (mysql_real_connect(p_mysql_connection_info_struct->p_mysql_object, host_name, user_name, password, database_name, port_num, NULL, 0))
	{
		//关闭自动commit（默认式每存入1条就提交1次，这样对于存入很多条tick数据，就会很慢）
		mysql_autocommit(p_mysql_connection_info_struct->p_mysql_object, 0);
		//设置编码格式，保存中文字段应设置为UTF8
		mysql_query(p_mysql_connection_info_struct->p_mysql_object, "SET NAMES UTF8");
		//关闭安全模式（想执行比如删除表等语句，必须关闭安全模式）
		mysql_query(p_mysql_connection_info_struct->p_mysql_object, "SET SQL_SAFE_UPDATES = 0");
		//增加连接超时时间（比如10分钟没有任何操作，连接就断开了）
		//好像这个设置是没有起作用的
		mysql_query(p_mysql_connection_info_struct->p_mysql_object, "SET INTERACTIVE_TIMEOUT = 28800");
		//增加连接数
		mysql_query(p_mysql_connection_info_struct->p_mysql_object, "set global max_allowed_packet = 1024*1024*16");

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


//断开mysql
bool main_thread::disconnect_to_mysql()
{
	mysql_close(p_mysql_connection_info_struct->p_mysql_object);

	return true;
}


//创建mysql表
void main_thread::create_mysql_table()
{
	//生成表名，后缀为日期
	p_mysql_connection_info_struct->instrument_info_table_name = "instrument_info" + get_int_string_current_date() + "_table";
	p_mysql_connection_info_struct->tick_data_table_name = "tick_data" + get_int_string_current_date() + "_table";

	char buff[DATABUFFSIZE] = { 0 };

	//连接mysql
	if (!connect_to_mysql())
	{
		print_new_message("连接mysql数据库失败！");

		return;
	};

	//创建合约信息表，当前table是否存在
	snprintf(buff, DATABUFFSIZE, "select * from %s", p_mysql_connection_info_struct->instrument_info_table_name);
	//合约信息表不存在，需要创建
	if (mysql_query(p_mysql_connection_info_struct->p_mysql_object, buff))
	{
		char v_buff_createTable[DATABUFFSIZE] = { 0 };
		snprintf(v_buff_createTable, DATABUFFSIZE, "create table %s (instrumentID varchar(30),\
		exchangeID varchar(12),volumeMultiplier double,longMarginRatio double,shortMarginRatio double,\
		priceTick double)", p_mysql_connection_info_struct->instrument_info_table_name.c_str());

		//合约信息表创建成功
		if (!mysql_query(p_mysql_connection_info_struct->p_mysql_object, v_buff_createTable))
		{
			print_new_message(p_mysql_connection_info_struct->instrument_info_table_name + "表格创建成功！");
		}
		else
		{
			print_new_message(p_mysql_connection_info_struct->instrument_info_table_name + "表格创建失败！");
			print_new_message(mysql_error(p_mysql_connection_info_struct->p_mysql_object));
		};
	}
	//若table已经存在，需要释放查询结果，否则无法进行后续查询或者插入数据
	else
	{
		MYSQL_RES* p_result = mysql_store_result(p_mysql_connection_info_struct->p_mysql_object);
		mysql_free_result(p_result);
	};

	//创建tick表，当前table是否存在
	snprintf(buff, DATABUFFSIZE, "select * from %s", p_mysql_connection_info_struct->tick_data_table_name);
	//tick表不存在，需要创建
	if (mysql_query(p_mysql_connection_info_struct->p_mysql_object, buff))
	{
		char buff_create_table[DATABUFFSIZE] = { 0 };
		snprintf(buff_create_table, DATABUFFSIZE, "create table %s (instrumentID varchar(30),updateDate date,\
		updateTIme varchar(12),bidPricel double,askPricel double,lastPrice double,\
		bidVolumel int,askVolumel int,lastTradedVolume int,openInterest double)", p_mysql_connection_info_struct->tick_data_table_name.c_str());
		//创建表格成功
		if (!mysql_query(p_mysql_connection_info_struct->p_mysql_object, buff_create_table))
		{
			print_new_message(p_mysql_connection_info_struct->tick_data_table_name + " 表格创建成功！");
		}
		else
		{
			print_new_message(p_mysql_connection_info_struct->tick_data_table_name + " 表格创建失败！");
			print_new_message(mysql_error(p_mysql_connection_info_struct->p_mysql_object));
		};
	}
	//若tick表已存在，需要释放查询结果，否则无法进行后续查询或者插入数据
	else {
		MYSQL_RES* v_pResult = mysql_store_result(p_mysql_connection_info_struct->p_mysql_object);
		mysql_free_result(v_pResult);
	};

	//全部保存完毕后，指向一次commit
	mysql_commit(p_mysql_connection_info_struct->p_mysql_object);
	disconnect_to_mysql();
};


//连接交易api
void main_thread::connect_to_trade_api()
{
	//交易api对象初始化
	p_account_info_struct->p_trade_api = CThostFtdcTraderApi::CreateFtdcTraderApi();

	//创建虚机类的对象，创建spi对象
	ctp_trade_spi* p_ctp_trade_spi = new ctp_trade_spi;

	//将任务队列指针传给spi，由spi处理回调事务
	p_ctp_trade_spi->p_account_info_struct = p_account_info_struct;

	//将spi注册给api
	p_account_info_struct->p_trade_api->RegisterSpi(p_ctp_trade_spi);

	//连接交易前置服务器
	p_account_info_struct->p_trade_api->RegisterFront(p_account_info_struct->trade_front_addr);
	p_account_info_struct->p_trade_api->SubscribePublicTopic(THOST_TERT_QUICK);
	p_account_info_struct->p_trade_api->SubscribePrivateTopic(THOST_TERT_QUICK);

	//自动创建线程，创建后调用spi中的OnFrontConnect函数
	p_account_info_struct->p_trade_api->Init();
};


//连接行情api
void main_thread::connect_to_market_data_api()
{
	//创建spi对象
	ctp_market_data_spi* p_ctp_market_data_spi = new ctp_market_data_spi;

	//创建api对象
	//使用udp的通讯模式接收行情
	p_account_info_struct->p_market_data_api = CThostFtdcMdApi::CreateFtdcMdApi("", true);

	//将任务队列指针传给spi，由spi处理回调事务
	p_ctp_market_data_spi->p_account_info_struct = p_account_info_struct;
	p_ctp_market_data_spi->p_tick_data_struct = p_tick_data_struct;

	//将spi注册给api
	p_account_info_struct->p_market_data_api->RegisterSpi(p_ctp_market_data_spi);

	//连接行情前置服务器，这个IP地址必须填写正确，否则连不上柜台
	p_account_info_struct->p_market_data_api->RegisterFront(p_account_info_struct->market_data_front_addr);

	//自动创建线程，创建后调用spi中OnFrontConnect函数
	p_account_info_struct->p_market_data_api->Init();
};


//保存期货合约信息到mysql
void main_thread::save_instrument_info()
{
	if (!connect_to_mysql())
	{
		print_new_message("连接数据库失败！");

		return;
	};

	//开启事务
	mysql_query(p_mysql_connection_info_struct->p_mysql_object, "START TRANSACTION");

	//存入mysql
	for (map<string, instrument_info_struct*>::const_iterator iter = p_account_info_struct->all_available_instruments_info.begin(); iter != p_account_info_struct->all_available_instruments_info.end(); ++iter)
	{
		char buff[DATABUFFSIZE] = { 0 };
		snprintf(buff, DATABUFFSIZE, "insert into %s values('%s','%s',%.1f,%.1f,%.1f,%.1f)",
			p_mysql_connection_info_struct->instrument_info_table_name.c_str(),
			iter->second->instrument_id.c_str(), iter->second->exchange_id.c_str(),
			iter->second->instrument_multiplier, iter->second->long_margin_ratio, iter->second->short_margin_ratio);
		cout << iter->second->instrument_id << endl;
		//若出错则打印错误信息
		if (mysql_query(p_mysql_connection_info_struct->p_mysql_object, buff))
		{
			printf(mysql_error(p_mysql_connection_info_struct->p_mysql_object));
			continue;
		};
	};

	//全部保存完毕后，执行一次commit
	mysql_commit(p_mysql_connection_info_struct->p_mysql_object);
	print_new_message("期货合约信息保存成功！");
	disconnect_to_mysql();
};


//创建任务处理线程
void main_thread::create_task_process_thread()
{
	//创建定时将数据存入mysql的线程
	p_mysql_tick_data_save_thread = new mysql_tick_data_save_thread;

	p_mysql_tick_data_save_thread->p_mysql_connection_info_struct = p_mysql_connection_info_struct;
	p_mysql_tick_data_save_thread->p_tick_data_struct = p_tick_data_struct;

	p_mysql_tick_data_save_thread->start();
};