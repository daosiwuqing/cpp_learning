#include "Windows.h"

#include "trade_strategy.h"



void insert_order(account_data_struct* p_account_data_struct, string instrument_id, int volume_to_order, double price_to_order, TThostFtdcOffsetFlagType offset_flag, TThostFtdcDirectionType order_direction)
{
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));
    strcpy_s(req.BrokerID, p_account_data_struct->broker_id);
    strcpy_s(req.InvestorID, p_account_data_struct->investor_id);
    strcpy_s(req.InstrumentID, instrument_id.c_str());
    strcpy_s(req.ExchangeID, "SHFE");

    // 买卖方向
    req.Direction = order_direction;
    // 组合开平标志
    req.CombOffsetFlag[0] = offset_flag;
    // 价格
    req.LimitPrice = price_to_order;
    // 下单量
    req.VolumeTotalOriginal = volume_to_order;
    // 报单价格条件
    req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
    // 组合投机套保标志
    req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    // 最小成交量
    req.MinVolume = 1;
    // 触发条件
    req.ContingentCondition = THOST_FTDC_CC_Immediately;
    // 强平原因：非强平
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    // 自动挂起标志
    req.IsAutoSuspend = 0;
    // 用户强平标志
    req.UserForceClose = 0;
    // 有效期类型
    req.TimeCondition = THOST_FTDC_TC_GFD;
    // 成交量类型
    req.VolumeCondition = THOST_FTDC_VC_AV;

    // 累加单号
    int order_ref = ++ p_account_data_struct->order_ref;
    sprintf_s(req.OrderRef, "%i", order_ref);

    p_account_data_struct->p_trade_api->ReqOrderInsert(&req, 0);
};



void trade_strategy1(account_data_struct* p_account_data_struct, market_data_struct* p_market_data_struct)
{
    cout << "策略线程启动成功！" << endl;

    while (true)
    {
        Sleep(3 * 1000);

        double  last_price = p_market_data_struct->map_last_price["rb2410"];

        if (last_price > 3515)
        {
            insert_order(p_account_data_struct, "rb2410", 1, last_price, THOST_FTDC_OF_Open, THOST_FTDC_D_Buy);
        };
    };

    cout << "策略报单完成！" << endl;
};