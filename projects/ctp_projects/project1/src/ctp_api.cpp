#include "ctp_api.h"



void market_data_spi::OnFrontConnected()
{
    cout << "开始连接行情api..." << endl;
    ReqUserLogin();
};


void market_data_spi::ReqUserLogin()
{
    CThostFtdcReqUserLoginField req;

    memset(&req, 0, sizeof(req));
    strcpy_s(req.BrokerID, p_account_data_struct->broker_id);
    strcpy_s(req.UserID, p_account_data_struct->investor_id);
    strcpy_s(req.Password, p_account_data_struct->password);

    int error = p_account_data_struct->p_market_data_api->ReqUserLogin(&req, 0);

    if (error != 0)
    {
        cout << "发送行情api用户登录请求失败！" << endl;
    };
};


void market_data_spi::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo && pRspInfo->ErrorID != 0)
    {
        cout << "行情api用户登录失败！" << endl;
        cout << pRspInfo->ErrorMsg << endl;
        cout << pRspInfo->ErrorID << endl;
    }
    else
    {
        cout << "行情api用户登录成功！" << endl;
        SubscribeInstrument();
    };
};


void market_data_spi::SubscribeInstrument()
{
    char* p_instruments_id[] = { "rb2410", "ni2410", "cu2410" };
    p_account_data_struct->p_market_data_api->SubscribeMarketData(p_instruments_id, 3);
};


void market_data_spi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    string instrument_id = (string)pSpecificInstrument->InstrumentID;

    if (pRspInfo && pRspInfo->ErrorID != 0)
    {
        cout << instrument_id << "行情订阅失败！" << endl;
        cout << pRspInfo->ErrorMsg << endl;
        cout << pRspInfo->ErrorID << endl;
    }
    else
    {
        cout << instrument_id << "行情订阅成功！" << endl;
    };
};


void market_data_spi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
    cout << "行情推送：" << pDepthMarketData->InstrumentID << "最新价：" << pDepthMarketData->LastPrice << endl;

    p_market_data_struct->map_last_price[pDepthMarketData->InstrumentID] = pDepthMarketData->LastPrice;
};



void trade_spi::OnFrontConnected()
{
    ReqAuthenticate();
};


void trade_spi::ReqAuthenticate()
{
    CThostFtdcReqAuthenticateField req;
    memset(&req, 0, sizeof(req));
    strcpy_s(req.BrokerID, p_account_data_struct->broker_id);
    strcpy_s(req.UserID, p_account_data_struct->investor_id);
    strcpy_s(req.AppID, p_account_data_struct->app_id);
    strcpy_s(req.AuthCode, p_account_data_struct->auth_code);

    p_account_data_struct->p_trade_api->ReqAuthenticate(&req, 0);
};


void trade_spi::OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo && pRspInfo->ErrorID != 0)
    {
        cout << "交易api认证失败！" << endl;
        cout << pRspInfo->ErrorMsg << endl;
        cout << pRspInfo->ErrorID << endl;
    }
    else
    {
        cout << "交易api认证成功！" << endl;

        ReqUserLogin();
    };
};


void trade_spi::ReqUserLogin()
{
    CThostFtdcReqUserLoginField req;

    memset(&req, 0, sizeof(req));
    strcpy_s(req.BrokerID, p_account_data_struct->broker_id);
    strcpy_s(req.UserID, p_account_data_struct->investor_id);
    strcpy_s(req.Password, p_account_data_struct->password);
    
    p_account_data_struct->p_trade_api->ReqUserLogin(&req, 0);
};


void trade_spi::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo && pRspInfo->ErrorID != 0)
    {
        cout << "交易api登录失败！" << endl;
        cout << pRspInfo->ErrorMsg << endl;
        cout << pRspInfo->ErrorID << endl;
    }
    else
    {
        cout << "交易api登录成功！" << endl;

        p_account_data_struct->front_id = pRspUserLogin->FrontID;
        p_account_data_struct->session_id = pRspUserLogin->SessionID;

        // 将下单编号初始化
        p_account_data_struct->order_ref = atoi(pRspUserLogin->MaxOrderRef) + 1;

        ReqSettlementInfoConfirm();
    };
};


void trade_spi::ReqSettlementInfoConfirm()
{
    CThostFtdcSettlementInfoConfirmField req;
    memset(&req, 0, sizeof(req));
    strcpy_s(req.BrokerID, p_account_data_struct->broker_id);
    strcpy_s(req.InvestorID, p_account_data_struct->investor_id);

    p_account_data_struct->p_trade_api->ReqSettlementInfoConfirm(&req, 0);
};


void trade_spi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    cout << "结算单确认成功！" << endl;
    cout << "交易api连接完成！" << endl;
};


void trade_spi::OnRtnTrade(CThostFtdcTradeField* pTrade)
{
    cout << "成交回报：" << pTrade->InstrumentID << "price" << pTrade->Price << " volume: " << pTrade->Volume << endl;
};