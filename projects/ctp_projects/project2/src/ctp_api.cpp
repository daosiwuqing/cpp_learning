#include "ctp_api.h"




using namespace std;



//1、ctp_trade_spi类
//打印消息
void ctp_trade_spi::print_new_message(string message)
{
	cout << message.c_str() << endl;
};


//检查ctp返回的信息中是否有错
bool ctp_trade_spi::IsErrorRspInfo(CThostFtdcRspInfoField* pRspInfo)
{
	if (pRspInfo == NULL)
	{
		return false;
	}
	else
	{
		if (pRspInfo->ErrorID != 0)
		{
			print_new_message(__FUNCTION__); //函数名
			print_new_message(to_string(pRspInfo->ErrorID));
			print_new_message(pRspInfo->ErrorMsg);

			return true;
		}
		else
		{
			return false;
		};
	};
};


//当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用
void ctp_trade_spi::OnFrontConnected()
{
	investor_id = string(p_account_info_struct->investor_id);
	print_new_message("开始建立 " + investor_id + " 交易api...");
	//ReqAuthenticate(); //simnow账号请求客户端认证总是失败，真实账号应该不会出现这种情况，现在采取的解决办法是：模拟账号跳过认证，直接登录
	ReqUserLogin();
};


//请求客户端认证
void ctp_trade_spi::ReqAuthenticate()
{
	CThostFtdcReqAuthenticateField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, p_account_info_struct->broker_id);
	strcpy(req.UserID, p_account_info_struct->investor_id);
	strcpy(req.AppID, p_account_info_struct->app_id);
	strcpy(req.AuthCode, p_account_info_struct->auth_code);
		
	int error = p_account_info_struct->p_trade_api->ReqAuthenticate(&req, 0);
	if (error == 0)
	{
		print_new_message("发送账号 " + investor_id + " 穿透式认证请求成功！");
	}
	else
	{
		print_new_message("发送账号 " + investor_id + " 穿透式认证请求失败！");
	};
};


//客户端认证响应
void ctp_trade_spi::OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast)
	{
		//客户端认证失败
		print_new_message("账号 " + investor_id + " 穿透式认证失败！");
		p_account_info_struct->p_trade_api->Release();
	}
	else
	{
		print_new_message("账号 " + investor_id + " 穿透式认证成功，开始发起登录请求！");
		ReqUserLogin();
	};
};


//请求登录用户
void ctp_trade_spi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, p_account_info_struct->broker_id);
	strcpy(req.UserID, p_account_info_struct->investor_id);
	strcpy(req.Password, p_account_info_struct->password);

	int error = p_account_info_struct->p_trade_api->ReqUserLogin(&req, 0);

	if (error == 0)
	{
		print_new_message("发送账号 " + investor_id + " 登录请求成功！");
	}
	else
	{
		print_new_message("发送账号 " + investor_id + " 登录请求失败！");
	};
};


//登录请求响应
void ctp_trade_spi::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast)
	{
		//登录失败
		if (IsErrorRspInfo(pRspInfo))
		{
			print_new_message("账号 " + investor_id + " 登录失败！");
			p_account_info_struct->p_trade_api->Release();
		}
		//登录成功
		else
		{
			print_new_message("账号 " + investor_id + " 登录成功，开始确认结算单！");
			ReqSettlementInfoConfirm();
		};
	};
};


//确认结算单请求
void ctp_trade_spi::ReqSettlementInfoConfirm()
{
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, p_account_info_struct->broker_id);
	strcpy(req.InvestorID, p_account_info_struct->investor_id);

	int error = p_account_info_struct->p_trade_api->ReqSettlementInfoConfirm(&req, 0);
	if (error == 0)
	{
		print_new_message("发送账号 " + investor_id + " 确认结算结果请求成功！");
	}
	else
	{
		print_new_message("发送账号 " + investor_id + " 确认结算结果请求失败！");
	};
};


//确认结算单结果回调
void ctp_trade_spi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		print_new_message("账号 " + investor_id + " 确认结算结果成功，开始查询合约信息！");
		ReqQryInstrument();
	}
	else
	{
		print_new_message("账号 " + investor_id + " 确认结算结果失败！");
	};
};


//查询所有可用合约代码
void ctp_trade_spi::ReqQryInstrument()
{
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));

	//查询所有可用合约代码。如果查询所有合约，第二个参数填成空。这里我们先查询一个
	strcpy(req.InstrumentID, "");

	int error = p_account_info_struct->p_trade_api->ReqQryInstrument(&req, 0);
	if (error == 0)
	{
		print_new_message("账号 " + investor_id + " 发送查询合约列表请求成功！");
	}
	else
	{
		print_new_message("账号 " + investor_id + " 发送查询合约列表请求失败！");
	};
};


//查询所有可用合约的回调函数
void ctp_trade_spi::OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (!IsErrorRspInfo(pRspInfo) && pInstrument != NULL)
	{
		string instrument_code = pInstrument->InstrumentID;

		//只处理期货合约，状态正在交易的合约
		if (pInstrument->ProductClass == THOST_FTDC_PC_Futures && pInstrument->IsTrading)
		{
			//初始化合约信息
			instrument_info_struct* p_instrument_info_struct = new instrument_info_struct;
			p_instrument_info_struct->instrument_id = pInstrument->InstrumentID;
			p_instrument_info_struct->exchange_id = pInstrument->ExchangeID;
			p_instrument_info_struct->instrument_multiplier = pInstrument->VolumeMultiple;
			p_instrument_info_struct->long_margin_ratio = pInstrument->LongMarginRatio;
			p_instrument_info_struct->short_margin_ratio = pInstrument->ShortMarginRatio;
			p_instrument_info_struct->price_tick = pInstrument->PriceTick;

			p_account_info_struct->all_available_instruments_info[instrument_code] = p_instrument_info_struct;
		};
	};

	if (bIsLast)
	{
		//交易api连接完成
		p_account_info_struct->b_is_trade_api_connected = true;
		print_new_message(investor_id + " 交易api建立完成！");
	};
};



//2、ctp_market_data_spi类
//打印消息
void ctp_market_data_spi::print_new_message(string message)
{
	printf("%s \n", message.c_str());
};


//检查ctp返回的信息中是否有错
bool ctp_market_data_spi::IsErrorRspInfo(CThostFtdcRspInfoField* pRspInfo)
{
	if (pRspInfo == NULL)
	{
		return false;
	}
	else
	{
		if (pRspInfo->ErrorID != 0)
		{
			print_new_message(__FUNCTION__);
			print_new_message(to_string(pRspInfo->ErrorID));
			print_new_message(pRspInfo->ErrorMsg);

			return true;
		}
		else
		{
			return false;
		};
	};
};


//档客户端与交易后台建立起连接时（还未登录前），该方法被调用
void ctp_market_data_spi::OnFrontConnected()
{
	investor_id = string(p_account_info_struct->investor_id);
	print_new_message("开始建立" + investor_id + " 行情api...");

	ReqUserLogin();
};


//发送用户登录请求
void ctp_market_data_spi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));

	//账号，密码随便填写，也是可以联通的
	strcpy(req.UserID, p_account_info_struct->investor_id);
	strcpy(req.Password, p_account_info_struct->password);
	strcpy(req.BrokerID, p_account_info_struct->broker_id);

	int error = p_account_info_struct->p_market_data_api->ReqUserLogin(&req, 0);

	if (error == 0)
	{
		print_new_message("发送账号 " + investor_id + " 登录请求成功！");
	}
	else
	{
		print_new_message("发送账号 " + investor_id + " 登录请求失败！");
	};
};


//行情登录请求的响应
void ctp_market_data_spi::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast)
	{
		if (!IsErrorRspInfo(pRspInfo))
		{
			print_new_message("账号 " + investor_id + " 登录成功，开始订阅所有期货合约行情！");
			SubscribeAllFutureInstrument();
		}
		else
		{
			print_new_message("账号 " + investor_id + " 行情登录失败！");
		};
	};
};


//订阅所有期货合约行情
void ctp_market_data_spi::SubscribeAllFutureInstrument()
{
	for (map<string, instrument_info_struct*>::const_iterator iter = p_account_info_struct->all_available_instruments_info.begin(); iter != p_account_info_struct->all_available_instruments_info.end(); ++iter)
	{
		char* p_instrument_id = (char*)(iter->first).data();
		char** pp_instrument_id = &p_instrument_id;

		int error = p_account_info_struct->p_market_data_api->SubscribeMarketData(pp_instrument_id, 1);
	};
	print_new_message(investor_id + " 合约订阅完毕，行情api建立完成！");
	p_account_info_struct->b_is_market_data_api_connected = true;
};


//订阅行情应答
void ctp_market_data_spi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	string instrument_id = (string)pSpecificInstrument->InstrumentID;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		print_new_message("订阅 " + instrument_id + " 行情成功！");
	}
	else
	{
		print_new_message("订阅 " + instrument_id + " 行情失败！");
	};
};


//深度行情通知
void ctp_market_data_spi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	tick_data_object tick_data_object;

	tick_data_object.instrument_id = pDepthMarketData->InstrumentID;
	tick_data_object.update_date = pDepthMarketData->TradingDay;
	tick_data_object.update_time = pDepthMarketData->UpdateTime;
	tick_data_object.update_milli_second = to_string(pDepthMarketData->UpdateMillisec);
	tick_data_object.bid_price1 = pDepthMarketData->BidPrice1;
	tick_data_object.ask_price1 = pDepthMarketData->AskPrice1;
	tick_data_object.last_price = pDepthMarketData->LastPrice;
	tick_data_object.bid_volume1 = pDepthMarketData->BidVolume1;
	tick_data_object.ask_volume1 = pDepthMarketData->AskVolume1;
	tick_data_object.last_traded_volume = pDepthMarketData->Volume;
	tick_data_object.open_interest = pDepthMarketData->OpenInterest;

	print_new_message(tick_data_object.instrument_id + " :" + to_string(tick_data_object.last_price));

	p_tick_data_struct->mut_tick_data.lock(); //加锁
	p_tick_data_struct->vec_tick_data.push_back(tick_data_object); //将订阅返回的数据写在队列里面
	p_tick_data_struct->mut_tick_data.unlock(); //解锁
};


//行情连接中断
void ctp_market_data_spi::OnFrontDisconnected(int nReason)
{
	print_new_message("行情api连接中断！");
};