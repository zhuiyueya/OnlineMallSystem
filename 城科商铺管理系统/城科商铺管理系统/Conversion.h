#pragma once
//ת�����ģ�����1.�н����buyer��ȡ�̻���Ϣ���������ֱ�ӽӴ�������Ϣ
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
	//��ȡ�����̻���
	void getAllMerchantName(std::vector<std::string>& merchantsName);

	//�ж�ĳ���̻��Ƿ����
	bool isMerchantExist(std::string name);

	//��ѯĳ���̻�����Ʒ
	void searchAllMerchandiseOfSpecifiedMerchant(std::string name, std::vector<std::vector<std::string>>& merchandise, std::vector<int>&maxColLen);

	//��ָ����Ʒ
	void getSpecifiedMerchandise(int id, std::string merchandiseName, int num);

    //�жϸ����ڴ��л���������̻�����Ϣ
	void updateTemporaryMerchantInfo();

	//����ָ��������ָ����Ʒ
	bool purchaseDesiredMerchandise(std::string merchantName, int merchandiseID, int merchandiseNum, const std::string& buyerName);
private:

	std::vector<std::string>m_merchants;
	std::vector<std::string>m_merchantsName;
	std::filesystem::file_time_type m_lastModifyTimeOfMerchantFIle;
};

