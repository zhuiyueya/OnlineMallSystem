#include "Conversion.h"
#include<fstream>

Conversion::Conversion()
{
	auto now = std::chrono::system_clock::now();
	m_lastModifyTimeOfMerchantFIle = std::filesystem::file_time_type(std::chrono::duration_cast<std::filesystem::file_time_type::duration>(
		now.time_since_epoch()
	));
}

void Conversion::getAllMerchantName(std::vector<std::string>& merchantsName)
{
	updateTemporaryMerchantInfo();
	merchantsName = m_merchantsName;
}

bool Conversion::isMerchantExist(std::string name)
{
	updateTemporaryMerchantInfo();
	for (auto& s : m_merchantsName) {
		if (s == name)return true;
	}
	return false;
}

void Conversion::searchAllMerchandiseOfSpecifiedMerchant(std::string name, std::vector<std::vector<std::string>>& merchandise,std::vector<int>&maxColLen)
{ 
	updateTemporaryMerchantInfo();
	std::string pwd;
	for (int i = 0; i < m_merchantsName.size(); i++) {
		if (name == m_merchantsName[i]) {
			int blanketPos = m_merchants[i].find(' ', 0);
			pwd = m_merchants[i].substr(blanketPos + 1, (int)m_merchants[i].size() - blanketPos - 1);
			break;
		}
	}
	
	Merchant m(name, pwd);
	m.getMerchandiseInfoForBuyer(merchandise, maxColLen);
}

void Conversion::updateTemporaryMerchantInfo()
{
	bool isModify = true;
	std::filesystem::path filePath(MERCHANT_FILE_PATH);
	if (std::filesystem::exists(filePath)) {
		auto lastModifyTime = std::filesystem::last_write_time(filePath);
		if (lastModifyTime == m_lastModifyTimeOfMerchantFIle) {
			isModify = false;
		}
		else {
			m_lastModifyTimeOfMerchantFIle = lastModifyTime;
		}
	}
	if (isModify) {
		m_merchants.clear();
		m_merchantsName.clear();
		std::ifstream ifs(MERCHANT_FILE_PATH);
		std::string info;
		while (std::getline(ifs, info)) {
			m_merchants.push_back(info);
			m_merchantsName.push_back(info.substr(0, info.find(' ', 0)));
		}

		ifs.close();
	}
}

bool Conversion::purchaseDesiredMerchandise(std::string merchantName, int merchandiseID, int merchandiseNum, const std::string& buyerName)
{
	updateTemporaryMerchantInfo();
	std::string pwd;
	for (int i = 0; i < m_merchantsName.size(); i++) {
		if (merchantName == m_merchantsName[i]) {
			int blanketPos = m_merchants[i].find(' ', 0);
			pwd = m_merchants[i].substr(blanketPos + 1, (int)m_merchants[i].size() - blanketPos - 1);
			break;
		}
	}

	Merchant m(merchantName, pwd);
	return m.purchaseSpecifiedMerchandise_Buyer(merchandiseID, merchandiseNum, buyerName);
}
