#ifndef __MAIN_THREAD_H__
#define __MAIN_THREAD_H__

#include "ctp_api.h"
#include "trade_strategy.h"



class main_thread
{
private:
    account_data_struct* p_account_data_struct;
    market_data_struct* p_market_data_struct;

    void init_data_struct();
    void connect_to_market_data();
    void connect_to_trade();
    void start_strategy_thread();

public:
    void start_main_thread();
};



#endif