#ifndef __TRADE_STRATEGY_H__
#define __TRADE_STRATEGY_H__

#include "data_struct.h"



void insert_order(account_data_struct* p_account_data_struct, string instrumentID, int volumeToOrder, double priceToOrder, TThostFtdcOffsetFlagType offsetFlag, TThostFtdcDirectionType orderDirection);



void trade_strategy1(account_data_struct* p_account_data_struct, market_data_struct* p_market_data_struct);



#endif