#ifndef __DATA_STRUCT_H__
#define __DATA_STRUCT_H__

#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <mutex>

#include <mysql.h>




using namespace std;



//1、保存期货合约及相关信息的结构体，由trade_api读取后填入
struct instrument_info_struct
{
	string instrument_id; //合约代码
	string exchange_id;	//交易所
	double instrument_multiplier; //合约乘数
	double long_margin_ratio; //多头保证金率
	double short_margin_ratio; //空头保证金率
	double price_tick; //最小变动价位
};



//2、账户登录信息结构体
struct account_info_struct
{
	//接口使用者需要填入的信息
	TThostFtdcInvestorIDType investor_id; //账号
	TThostFtdcPasswordType password; //密码
	TThostFtdcBrokerIDType broker_id; //期商编码
	TThostFtdcAppIDType app_id; //客户终端软件代码
	TThostFtdcAuthCodeType auth_code; //客户终端软件认证码

	char market_data_front_addr[30]; //行情前置地址
	char trade_front_addr[30]; //交易前置地址

	CThostFtdcMdApi* p_market_data_api; //接口的对象
	CThostFtdcTraderApi* p_trade_api; //接口的对象

	bool b_is_market_data_api_connected; //标记行情的api是否已经连接
	bool b_is_trade_api_connected; //标记交易的api是否已经连接

	//保存所有可用的期货合约及合约信息的map
	map<string, instrument_info_struct*> all_available_instruments_info;
};



//3、保存tick数据所用到的结构体
//3.1、tick数据对象
struct tick_data_object
{
	string instrument_id;

	//交易所更新时间
	string update_date; //更新日期，格式为yyyy-MM-dd
	string update_time; //更新时间，格式为hh:mm:ss
	string update_milli_second; //毫秒时间戳

	double bid_price1;
	double ask_price1;
	double last_price;
	int bid_volume1;
	int ask_volume1;
	int last_traded_volume;
	double open_interest;
};


//3.2、用于保存tick数据的队列
struct tick_data_struct
{
	mutex mut_tick_data;
	vector<tick_data_object> vec_tick_data;
};



//4、mysql连接信息结构体
struct mysql_connection_info_struct
{
	MYSQL* p_mysql_object; //mysql连接对象

	//连接所有参数
	string user_name;
	string password;
	string host_name;
	string database_name;
	int port_num;

	//合约信息表表名
	string instrument_info_table_name;

	//tick数据表表名
	string tick_data_table_name;
};



#endif