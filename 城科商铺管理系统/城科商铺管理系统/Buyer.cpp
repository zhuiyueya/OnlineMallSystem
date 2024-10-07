#include "Buyer.h"
#include<iostream>
#include<fstream>
void Buyer::showMerchandiseOfOneMerchant()
{
	std::string merchantName;
	std::cout << "��������Ҫ�鿴���̻�����";
	std::cin >> merchantName;
	if (!m_conversion.isMerchantExist(merchantName)) {
		std::cout << "�����ڸ��̻���\n";
		return;
	}
	m_merchandiseInfo.clear();
	m_maxColLen.size();
	m_conversion.searchAllMerchandiseOfSpecifiedMerchant(merchantName, m_merchandiseInfo, m_maxColLen);
	for (int i = 0; i < m_merchandiseInfo.size(); i++) {
		for (int j = 0; j < m_merchandiseInfo[i].size(); j++) {
			std::cout << std::left << std::setw(m_maxColLen[j] + 2) << m_merchandiseInfo[i][j];
		}
		std::cout << std::endl;
	}

	purchaseDesiredMerchandise(merchantName);
	
}

void Buyer::showAllMerchantInfo()
{
	m_merchantsName.clear();
	m_conversion.getAllMerchantName(m_merchantsName);
	for (auto&s:m_merchantsName) {
		std::cout << s << "\t";
	}
	std::cout << std::endl;

	
}

void Buyer::purchaseDesiredMerchandise(std::string name)
{
	std::cout << "������Ҫ�������Ʒ��ID(q/Q�˳��������)��";
	std::string id;
	std::cin >> id;
	if (strcmp("q", id.c_str())==0 || strcmp("Q", id.c_str())==0) {
		return;
	}
	int ID = atoi(id.c_str());
	std::cout << "������Ҫ�������Ʒ������(q/Q�˳��������)��";
	std::string num;
	std::cin >> num;
	if (strcmp("q", num.c_str())==0 || strcmp("Q", num.c_str())==0) {
		return;
	}
	int number = atoi(num.c_str());

	bool ret=m_conversion.purchaseDesiredMerchandise(name, ID, number,m_account);
	if (ret) {
		std::cout << "����ɹ���\n";
		//to do ...
		//�����û���������
	}
	else {
		std::cout << "����ʧ��\n";
	}
}

Buyer::Buyer(std::string account, std::string pwd):User(account,pwd)
{

}
enum Buyer_Option_Window_Option {
	Buyer_Option_Window_Option_Min,
	Buyer_Option_Window_Option_Show_All_Merchant_Info,
	Buyer_Option_Window_Option_Show_Merchandise_Of_One_Merchant,
	Buyer_Option_Window_Option,
	Buyer_Option_Window_Option_Quit,
	Buyer_Option_Window_Option_Max,
};
void Buyer::optionWindow()
{
	system("cls");
	std::cout << "��ѡ����Ҫ�����Ĺ��ܣ�\n";
	std::cout << Buyer_Option_Window_Option_Show_All_Merchant_Info << ".չʾ�����̻�����\n";
	std::cout << Buyer_Option_Window_Option_Show_Merchandise_Of_One_Merchant << ".����ָ���̻�����Ʒ\n";

	std::cout << Buyer_Option_Window_Option_Quit << ".�˳�\n";
	int option = 0;
	std::cin >> option;
	switch (option) {
	case Buyer_Option_Window_Option_Show_All_Merchant_Info: {
		showAllMerchantInfo();
		break;
	}
	case Buyer_Option_Window_Option_Show_Merchandise_Of_One_Merchant:
	{
		showMerchandiseOfOneMerchant();
		break;
	}
	case Buyer_Option_Window_Option_Quit: {
		m_isQuit = true;
		break;
	}
														  
	}


	std::cout << "���س�������......" << std::endl;
	for (int i = 0; i < 2; i++)getchar();
}

void Buyer::play()
{
	while (!m_isQuit) {
		optionWindow();
	}
}
