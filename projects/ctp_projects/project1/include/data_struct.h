#ifndef __DATA_STRUCT_H__
#define __DATA_STRUCT_H__

#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"

#include <iostream>
#include <string>
#include <map>
#include <thread>




using namespace std;



// 1、账户登录信息结构体
struct account_data_struct
{
    // 接口使用者需要填入的信息
    TThostFtdcInvestorIDType investor_id; // 账号
    TThostFtdcPasswordType password; // 密码
    TThostFtdcBrokerIDType broker_id; // 期商编码
    TThostFtdcAppIDType app_id; // 客户终端软件代码
    TThostFtdcAuthCodeType auth_code; // 客户终端软件认证码

    char market_data_front_addr[30]; // 行情前置地址
    char trade_front_addr[30]; // 交易前置地址

    CThostFtdcMdApi* p_market_data_api; // 接口的对象
    CThostFtdcTraderApi* p_trade_api; // 接口的对象

    // 接口创建后输入的信息
    TThostFtdcFrontIDType front_id;
    TThostFtdcSessionIDType session_id;
    int order_ref;
};



// 2、行情容器
struct market_data_struct
{
    map<string, double> map_last_price;
};



#endif