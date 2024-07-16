#ifndef __CTP_API_H__
#define __CTP_API_H__

#include "data_struct.h"



class market_data_spi : public CThostFtdcMdSpi
{
private:
    // 发送用户登录请求
    void ReqUserLogin();
    // 订阅所有期货合约行情
    void SubscribeInstrument();

public:
    account_data_struct* p_account_data_struct;
    market_data_struct* p_market_data_struct;

    //当客户端与交易后台建立起连接时（还未登录前），该方法被调用
    virtual void OnFrontConnected();
    //行情登录请求的响应
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
    ///订阅行情应答
    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
    ///深度行情通知
    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData);
};



class trade_spi : public CThostFtdcTraderSpi
{
private:
    // 进行穿透式认证
    void ReqAuthenticate();
    // 发送用户登录请求
    void ReqUserLogin();
    // 发送结算单请求
    void ReqSettlementInfoConfirm();

public:
    account_data_struct* p_account_data_struct;

	//连接前台
	virtual void OnFrontConnected();
	//客户端认证响应
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	//用户登录结果返回
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	//结算单结果确认
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
    // 成交回报
    virtual void OnRtnTrade(CThostFtdcTradeField* pTrade);
};



#endif