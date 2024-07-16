#include "main_thread.h"



void main_thread::start_main_thread()
{
    cout << "主线程开启" << endl;

    init_data_struct();
    connect_to_market_data();
    connect_to_trade();
    start_strategy_thread();
};



void main_thread::init_data_struct()
{
    p_account_data_struct = new account_data_struct;
    strcpy_s(p_account_data_struct->investor_id, "118941");
    strcpy_s(p_account_data_struct->password, "09221017Zjk");
    strcpy_s(p_account_data_struct->broker_id, "9999");
    strcpy_s(p_account_data_struct->market_data_front_addr, "tcp://180.168.146.187:10211"); //第一套
    strcpy_s(p_account_data_struct->trade_front_addr, "tcp://180.168.146.187:10201"); //第一套
    // strcpy_s(p_account_data_struct->market_data_front_addr, "tcp://180.168.146.187:10131"); //第二套
    // strcpy_s(p_account_data_struct->trade_front_addr, "tcp://180.168.146.187:10130"); //第二套
    strcpy_s(p_account_data_struct->app_id, "simnow_client_test");
    strcpy_s(p_account_data_struct->auth_code, "0000000000000000");

    p_market_data_struct = new market_data_struct;
};



void main_thread::connect_to_market_data()
{
    // 创建spi对象
    market_data_spi* p_market_data_spi = new market_data_spi;
    
    // 创建api对象（使用udp的通讯模式接收行情）
    p_account_data_struct->p_market_data_api = CThostFtdcMdApi::CreateFtdcMdApi("", true);
    // 将任务队列指针传给spi，由spi处理回调事务
    p_market_data_spi->p_account_data_struct = p_account_data_struct;
    p_market_data_spi->p_market_data_struct = p_market_data_struct;
    // 将spi注册给api
    p_account_data_struct->p_market_data_api->RegisterSpi(p_market_data_spi);
    // 连接行情前置服务器
    p_account_data_struct->p_market_data_api->RegisterFront(p_account_data_struct->market_data_front_addr);
    // 自动创建线程，创建后调用spi中的OnFrontConnect函数
    p_account_data_struct->p_market_data_api->Init();
};



void main_thread::connect_to_trade()
{
    //  创建spi对象
    trade_spi* p_trade_spi = new trade_spi;
    p_account_data_struct->p_trade_api = CThostFtdcTraderApi::CreateFtdcTraderApi();

    // 将任务队列指针传给spi，由spi处理回调事务
    p_trade_spi->p_account_data_struct = p_account_data_struct;
    // 将spi注册给api
    p_account_data_struct->p_trade_api->RegisterSpi(p_trade_spi);
    // 连接交易前置服务器
    p_account_data_struct->p_trade_api->RegisterFront(p_account_data_struct->trade_front_addr);
    p_account_data_struct->p_trade_api->SubscribePublicTopic(THOST_TERT_QUICK);
    p_account_data_struct->p_trade_api->SubscribePrivateTopic(THOST_TERT_QUICK);
    // 自动创建线程，创建后调用spi中的OnFrontConnect函数
    p_account_data_struct->p_trade_api->Init();
};



void main_thread::start_strategy_thread()
{
    thread thread(trade_strategy1, p_account_data_struct, p_market_data_struct);
    thread.detach();
};