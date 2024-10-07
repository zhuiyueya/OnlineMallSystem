#pragma once
//转换中心，用于1.承接买家buyer获取商户信息，避免买家直接接触卖家信息
#include"protocol.h"
#include<vector>
#include<string>
#include<filesystem>
#include<chrono>
#include"Merchant.h"
class Conversion
{
public:
	Conversion();
	//获取所有商户名
	void getAllMerchantName(std::vector<std::string>& merchantsName);

	//判断某个商户是否存在
	bool isMerchantExist(std::string name);

	//查询某个商户的商品
	void searchAllMerchandiseOfSpecifiedMerchant(std::string name, std::vector<std::vector<std::string>>& merchandise, std::vector<int>&maxColLen);

	//买指定商品
	void getSpecifiedMerchandise(int id, std::string merchandiseName, int num);

    //判断更新内存中缓存的所有商户名信息
	void updateTemporaryMerchantInfo();

	//购买指定数量的指定商品
	bool purchaseDesiredMerchandise(std::string merchantName, int merchandiseID, int merchandiseNum, const std::string& buyerName);
private:

	std::vector<std::string>m_merchants;
	std::vector<std::string>m_merchantsName;
	std::filesystem::file_time_type m_lastModifyTimeOfMerchantFIle;
};

