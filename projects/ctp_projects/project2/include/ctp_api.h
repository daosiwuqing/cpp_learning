#ifndef __CTP_API_H__
#define __CTP_API_H__

#include "data_struct.h"



//1、trade_spi类
class ctp_trade_spi : public CThostFtdcTraderSpi
{
private:
	string investor_id;

	void print_new_message(string message);

	bool IsErrorRspInfo(CThostFtdcRspInfoField* pRspInfo);
	void ReqAuthenticate();
	void ReqUserLogin();
	void ReqSettlementInfoConfirm();
	void ReqQryInstrument();

public:
	account_info_struct* p_account_info_struct;

	//连接前台
	virtual void OnFrontConnected();
	//客户端认证响应
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	//用户登录结果返回
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	//结算单结果确认
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	//查询所有期货可用合约
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
};



//2、market_data_spi类
class ctp_market_data_spi : public CThostFtdcMdSpi
{
private:
	string investor_id;

	void print_new_message(string message);

	bool IsErrorRspInfo(CThostFtdcRspInfoField* pRspInfo);
	void ReqUserLogin();
	void SubscribeAllFutureInstrument();

public:
	account_info_struct* p_account_info_struct;
	tick_data_struct* p_tick_data_struct;

	//当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用
	virtual void OnFrontConnected();
	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData);
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);
};



#endif