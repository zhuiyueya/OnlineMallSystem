#include "Merchant.h"
#include<iostream>
#include<algorithm>

#define MERCHANT_CANNT_FIND_MERCHANDISE_INFO -1

int findS(std::string s, char ch, int pos) {
	int i;
	for (i = pos; i < s.size(); i++) {
		if (s[i] == ch)break;
	}
	return i;
}
enum Merchant_Merchandise_Info {
	Merchant_Merchandise_Info_Id,
	Merchant_Merchandise_Info_Name, 
	Merchant_Merchandise_Info_RestNum,
	Merchant_Merchandise_Info_saledNum,
	Merchant_Merchandise_Info_TotalNum,
	Merchant_Merchandise_Info_Type,
	Merchant_Merchandise_Info_Price,
	Merchant_Merchandise_Info_Income,
};
Merchant::Merchant(std::string account, std::string pwd):User(account,pwd)
{
	m_employeeFilePath = account + pwd + "Employee.txt";
	m_merchandiseFilePath = account + pwd + "Merchandise.txt";
	m_tradeInfoFilePath = account + pwd + "TradeInfo.txt";
	
	m_maxInfoLen.resize(MERCHANDISE_INFO_NUM,0);
	
	m_colHeadName = { "��ƷID" , "��Ʒ��" , "��Ʒʣ������" , "��Ʒ��������" , "��Ʒ������" , "��Ʒ���","�۸�","����"};

	m_tradeInfoColMaxLen.resize(TRADEINFO_NUM,0);

	m_tradeInfoColHeadName = { "������","��ƷID","��Ʒ��","��������","����","��֧�����" };

	auto now = std::chrono::system_clock::now();

	// �����ȥ��ʱ��㣬���� 1 Сʱ֮ǰ
	//auto pastTime = now - std::chrono::hours(1);

	m_lastModifyTime = std::filesystem::file_time_type(std::chrono::duration_cast<std::filesystem::file_time_type::duration>(
		now.time_since_epoch()
	));
	m_tradeInfoFileLastModifyTime = m_lastModifyTime;
	m_isQuit = false;
}

void Merchant::addMerchandise()
{
	Merchandise m;

	std::cout << "��������Ʒ����";
	std::cin >> m.name;
	while (searchSpecifiedMerchandiseInfoByName(m.name) != MERCHANT_CANNT_FIND_MERCHANDISE_INFO) {
		std::cout << "ͬ����Ʒ�Ѿ����ڣ����������룺";
		std::cin >> m.name;
	}
	std::cout << "��������ƷID��";
	std::cin >> m.id;
	while (searchSpecifiedMerchandiseInfoByID(m.id) != MERCHANT_CANNT_FIND_MERCHANDISE_INFO) {
		std::cout << "ͬID��Ʒ�Ѿ����ڣ����������룺";
		std::cin >> m.id;
	}

	std::cout << "��������Ʒ��������";
	std::cin >> m.totalNum;
	m.restNum = m.totalNum;
	m.saledNum = 0;
	std::cout << "��������Ʒ���ID��";
	std::cin >> m.type;
	std::cout << "��������Ʒ�ĵ��ۣ�";
	std::cin >> m.price;
	m.income = 0;
	std::ofstream ofs(m_merchandiseFilePath, std::ios::out | std::ios::app);
	
	ofs << m.id;
	ofs << " ";
	ofs << m.name;
	ofs << " ";
	
	ofs << m.restNum;
	ofs << " ";
	ofs << m.saledNum;
	ofs << " ";
	ofs << m.totalNum;
	ofs << " ";
	ofs << m.type;
	ofs << " ";
	ofs << m.price;
	ofs << " ";
	ofs << m.income;
	ofs << "\n";
	ofs.close();


}

//����Ʒ��Ϣ�ı�̫��ʱ����ʾ������⣺ÿ����Ʒ��Ϣ֮����ֿ��У��Ǵ������⣬�Ŵ󴰿ھͺ���
void Merchant::showSalesPerformance()
{
	//bool isModify = true;
	//std::filesystem::path filePath(m_merchandiseFilePath);
	//if (std::filesystem::exists(filePath)) {
	//	auto lastModifyTime = std::filesystem::last_write_time(filePath);
	//	if (lastModifyTime == m_lastModifyTime) {
	//		isModify = false;
	//	}
	//	else {
	//		m_lastModifyTime = lastModifyTime;
	//	}
	//}
	//
	//if(isModify)
	//{
	//	
	//	//��վ���Ʒ��¼
	//	m_merchandiseInfo.clear();
	//	for (int i = 0; i < m_maxInfoLen.size(); i++)m_maxInfoLen[i] = m_colHeadName[i].size();
	//
	//	std::ifstream ifs(m_merchandiseFilePath);
	//	std::string content;
	//	int index = 1;
	//	//std::cout << "���\t" << "��ƷID\t" << "��Ʒ��\t" << "��Ʒʣ������\t" << "��Ʒ��������\t" << "��Ʒ������\t" << "��Ʒ���\t" << std::endl;
	//	while (std::getline(ifs, content)) {
	//
	//		//����ÿһ�е�������ֳ���
	//		int j = 0;
	//		for (int i = 0; i < m_maxInfoLen.size(); i++) {
	//			int start = j;
	//			while (j < content.size() && content[j] != ' ')j++;
	//			//std::cout << j << std::endl;
	//			m_maxInfoLen[i] = std::max(m_maxInfoLen[i], j - start);
	//			j++;
	//		}
	//		
	//		//std::replace(content.begin(), content.end(), ' ', '\t');
	//		m_merchandiseInfo.push_back(content);
	//		//std::cout << index << ".\t" << content << std::endl;
	//
	//		index++;
	//	}
	//	ifs.close();
	//}
	updateTemporaryMerchandiseInfo();

	for (int j = 0; j < m_maxInfoLen.size(); j++) {
		std::cout << std::left << std::setw(m_maxInfoLen[j]+2) << m_colHeadName[j];
	}
	std::cout << std::endl;
	//�����Ʒ��Ϣ
	for (int i = 0; i < m_merchandiseInfo.size(); i++) {
		//int index = 0;
		
		for (int j = 0; j < m_maxInfoLen.size(); j++) {
			//int pos = findS(m_merchandiseInfo[i], ' ', index);
			//int pos = m_merchandiseInfo[i].find(' ', index);
			
				//m_merchandiseInfo[i].substr(index, pos)
			//std::string(m_merchandiseInfo[i].begin() + index, m_merchandiseInfo[i].begin() + pos)
			//�ӣ�substr�ڶ��������Ǹ���
			//std::cout << std::left << std::setw(m_maxInfoLen[j]+2) << m_merchandiseInfo[i].substr(index, pos-index);
			std::cout << std::left << std::setw(m_maxInfoLen[j] + 2) << m_merchandiseInfo[i][j];
			//index = pos + 1;
		}
		
		std::cout << std::endl;
		
	}


}

void Merchant::showInventory()
{
	updateTemporaryMerchandiseInfo();
	//��ʾ��ͷ
	for(int j=0;j<3;j++)
	std::cout << std::left << std::setw(m_maxInfoLen[j] + 2) << m_colHeadName[j];
	std::cout << std::endl;

	for (int i = 0; i < m_merchandiseInfo.size(); i++) {
		for (int j = 0; j < 3; j++)
			std::cout << std::left << std::setw(m_maxInfoLen[j] + 2) << m_merchandiseInfo[i][j];
		std::cout << std::endl;
	}
}

void Merchant::showIncome()
{
	updateTemporaryMerchandiseInfo();
	//��ʾ��ͷ
	for (int j = 0; j < 2; j++)
		std::cout << std::left << std::setw(m_maxInfoLen[j] + 2) << m_colHeadName[j];
	std::cout << std::left << std::setw(m_maxInfoLen[Merchant_Merchandise_Info_Income] + 2) << m_colHeadName[Merchant_Merchandise_Info_Income];
	std::cout << std::endl;

	int totalIncome = 0;

	for (int i = 0; i < m_merchandiseInfo.size(); i++) {
		for (int j = 0; j < 2; j++)
			std::cout << std::left << std::setw(m_maxInfoLen[j] + 2) << m_merchandiseInfo[i][j];
		std::cout << std::left << std::setw(m_maxInfoLen[Merchant_Merchandise_Info_Income] + 2) << m_merchandiseInfo[i][Merchant_Merchandise_Info_Income];
		std::cout << std::endl;
		totalIncome += atoi(m_merchandiseInfo[i][Merchant_Merchandise_Info_Income].c_str());

	}
	
	std::cout << "�����룺" << totalIncome << std::endl;
	
}

enum Merchant_Specified_Merchandise_Info_Option {
	Merchant_Specified_Merchandise_Info_Option_MIN,
	Merchant_Specified_Merchandise_Info_Option_NAME,
	Merchant_Specified_Merchandise_Info_Option_ID,
	Merchant_Specified_Merchandise_Info_Option_MAX,
};

void Merchant::findSpecifiedMerchandiseInfo()
{
	system("cls");
	std::cout << "��ѡ����Ҫ��ѯ�ķ�ʽ��\n";
	std::cout << "1.��Ʒ��\n";
	std::cout << "2.��ƷID\n";
	int option = 1;
	std::cin >> option;
	while (option <= Merchant_Specified_Merchandise_Info_Option_MIN || option >= Merchant_Specified_Merchandise_Info_Option_MAX) {
		std::cout << "��������ȷ�Ĳ�ѯ��ʽ�ı�ţ�";
		std::cin >> option;
	}
	switch (option) {
	case Merchant_Specified_Merchandise_Info_Option_NAME: 
	{
		std::cout << "��������Ҫ��ѯ����Ʒ����";
		std::string name;
		std::cin >> name;
		int ret=searchSpecifiedMerchandiseInfoByName(name);
		if (ret == MERCHANT_CANNT_FIND_MERCHANDISE_INFO) {//δ��ѯ��
			std::cout << "δ��ѯ��ָ�����ֵ���Ʒ!\n";
		}
		else {
			//��ʾ��ͷ
			for (int j = 0; j < m_maxInfoLen.size(); j++) {
				std::cout << std::left << std::setw(m_maxInfoLen[j] + 2) << m_colHeadName[j];
			}
			std::cout << std::endl;

			//��ʾ��Ʒ��Ϣ
			for(int j=0;j<m_maxInfoLen.size();j++)
				std::cout << std::left << std::setw(m_maxInfoLen[j] + 2) << m_merchandiseInfo[ret][j];
			std::cout << std::endl;

		}
		break;
	}
	case Merchant_Specified_Merchandise_Info_Option_ID:
	{
		std::cout << "��������Ҫ��ѯ����Ʒ��ţ�";
		int id;
		std::cin >> id;
		int ret = searchSpecifiedMerchandiseInfoByID(id);
		if (ret == MERCHANT_CANNT_FIND_MERCHANDISE_INFO) {//δ��ѯ��
			std::cout << "δ��ѯ��ָ����ŵ���Ʒ!\n";
		}
		else {
			//��ʾ��ͷ
			for (int j = 0; j < m_maxInfoLen.size(); j++) {
				std::cout << std::left << std::setw(m_maxInfoLen[j] + 2) << m_colHeadName[j];
			}
			std::cout << std::endl;

			//��ʾ��Ʒ��Ϣ
			for (int j = 0; j < m_maxInfoLen.size(); j++)
				std::cout << std::left << std::setw(m_maxInfoLen[j] + 2) << m_merchandiseInfo[ret][j];
			std::cout << std::endl;

		}
		break;
	}
	}
	
	
	//updateTemporaryMerchandiseInfo();

}

int Merchant::searchSpecifiedMerchandiseInfoByName(const std::string& name)
{
	updateTemporaryMerchandiseInfo();
	for (int i = 0; i < m_merchandiseInfo.size(); i++) {
		if (name == m_merchandiseInfo[i][Merchant_Merchandise_Info_Name]) {
			return i;
		}
	}
	return MERCHANT_CANNT_FIND_MERCHANDISE_INFO;
}

int Merchant::searchSpecifiedMerchandiseInfoByID(int id) {
	updateTemporaryMerchandiseInfo();
	for (int i = 0; i < m_merchandiseInfo.size(); i++) {
		if (id == atoi(m_merchandiseInfo[i][Merchant_Merchandise_Info_Id].c_str())) {
			return i;
		}
	}
	return MERCHANT_CANNT_FIND_MERCHANDISE_INFO;
}

void Merchant::updateTemporaryMerchandiseInfo()
{
	bool isModify = true;
	std::filesystem::path filePath(m_merchandiseFilePath);
	if (std::filesystem::exists(filePath)) {
		auto lastModifyTime = std::filesystem::last_write_time(filePath);
		if (lastModifyTime == m_lastModifyTime) {
			isModify = false;
		}
		else {
			m_lastModifyTime = lastModifyTime;
		}
	}

	if (isModify)
	{

		//��վ���Ʒ��¼
		m_merchandiseInfo.clear();
		for (int i = 0; i < m_maxInfoLen.size(); i++)m_maxInfoLen[i] = m_colHeadName[i].size();

		std::ifstream ifs(m_merchandiseFilePath);
		std::string content;
		
		//std::cout << "���\t" << "��ƷID\t" << "��Ʒ��\t" << "��Ʒʣ������\t" << "��Ʒ��������\t" << "��Ʒ������\t" << "��Ʒ���\t" << std::endl;
		while (std::getline(ifs, content)) {
			std::vector<std::string>singleInfo;
			//����ÿһ�е�������ֳ���
			int j = 0;
			for (int i = 0; i < m_maxInfoLen.size(); i++) {
				int start = j;
				while (j < content.size() && content[j] != ' ')j++;
				//std::cout << j << std::endl;
				m_maxInfoLen[i] = std::max(m_maxInfoLen[i], j - start);
				singleInfo.push_back(content.substr(start, j - start));
				j++;
			}

			//std::replace(content.begin(), content.end(), ' ', '\t');
			m_merchandiseInfo.push_back(singleInfo);
			//std::cout << index << ".\t" << content << std::endl;

			
		}
		ifs.close();
	}
}

enum Merchant_Option_Window_Option {
	Merchant_Option_Window_Option_Min,
	Merchant_Option_Window_Option_Add_Merchandise,
	Merchant_Option_Window_Option_Show_All_Merchandise_Sale_Performance,
	Merchant_Option_Window_Option_Search_Specified_Merchandise_Sale_Performance,
	Merchant_Option_Window_Option_Show_Inventory,
	Merchant_Option_Window_Option_Show_Income,
	Merchant_Option_Window_Option_Show_TradeInfo,
	Merchant_Option_Window_Option_Quit,
	Merchant_Option_Window_Option_Max,
};

void Merchant::getMerchandiseInfoForBuyer(std::vector<std::vector<std::string>>& merchandise,std::vector<int>& maxColLen)
{
	updateTemporaryMerchandiseInfo();
	std::vector<std::string>colHead;
	for (int i = 0; i < m_colHeadName.size(); i++) {
		if (i == Merchant_Merchandise_Info_TotalNum || i == Merchant_Merchandise_Info_Income) {
			continue;
		}
		colHead.push_back(m_colHeadName[i]);
	}
	merchandise.push_back(colHead);
	for (auto& a : m_merchandiseInfo) {
		std::vector<std::string>info;
		for (int i = 0; i < a.size(); i++) {
			if (i == Merchant_Merchandise_Info_TotalNum || i == Merchant_Merchandise_Info_Income) {
				continue;
			}
			info.push_back(a[i]);
		}
		merchandise.push_back(info);
	}

	for (int i = 0; i < m_maxInfoLen.size(); i++) {
		if (i == Merchant_Merchandise_Info_TotalNum || i == Merchant_Merchandise_Info_Income) {
			continue;
		}
		maxColLen.push_back(m_maxInfoLen[i]);
	}
}

bool Merchant::purchaseSpecifiedMerchandise_Buyer(int merchandiseID, int merchandiseNum, const std::string& buyerName)
{
	//���ڵ��øú���ʱ����������һ�����޸�ʱ���˶�ȡ�ļ����²�׼ȷ
	updateTemporaryMerchandiseInfo();

	bool canFindSpecifiedID = false;
	//�޸���ʱ����m_merchandiseInfo��ָ��ID����Ʒ���������ٽ��޸ķ�Ӧ���ļ���
	for (auto& a : m_merchandiseInfo) {
		if (atoi(a[Merchant_Merchandise_Info_Id].c_str()) == merchandiseID) {
			canFindSpecifiedID = true;
			//�޸Ķ�ӦID��Ʒ������
			int merchandiseRestNum = atoi(a[Merchant_Merchandise_Info_RestNum].c_str());
			if (merchandiseRestNum >= merchandiseNum) {
				merchandiseRestNum -= merchandiseNum;
				char restNum[32] = { 0 };
				_itoa_s(merchandiseRestNum, restNum, 10);
				a[Merchant_Merchandise_Info_RestNum] = restNum;//���޸Ļ����е�ʣ����������ѭ�����޸��ļ��е�
				
				//�޸��۳�����
				memset(restNum, 0, 32);
				int merchandiseSaledNum= atoi(a[Merchant_Merchandise_Info_saledNum].c_str())+ merchandiseNum;
				_itoa_s(merchandiseSaledNum, restNum, 10);
				a[Merchant_Merchandise_Info_saledNum] = restNum;

				//�޸���Ʒ������
				int iniIncome = atoi(a[Merchant_Merchandise_Info_Income].c_str());
				int price = atoi(a[Merchant_Merchandise_Info_Price].c_str());
				memset(restNum, 0, 32);
				_itoa_s(iniIncome + price * merchandiseNum, restNum, 10);
				a[Merchant_Merchandise_Info_Income] = restNum;
				
				//��ӹ�����Ϣ��������Ϣ�ļ���
				addTradeInfo(buyerName, merchandiseID, a[Merchant_Merchandise_Info_Name], merchandiseNum, atoi(a[Merchant_Merchandise_Info_Price].c_str()));

				break;
			}
			else {
				return false;//����ʧ��
			}
		}
	}
	
	//��û�ҵ���ӦID����Ʒ������false
	if (!canFindSpecifiedID)return false;

	
	

	//���޸�ӳ�䵽�ļ���
	std::ofstream ofs(m_merchandiseFilePath,std::ios_base::out|std::ios_base::trunc);

	for (auto& merchandise : m_merchandiseInfo) {
		for (int i = 0; i < merchandise.size();i++) {
			ofs << merchandise[i];
			if(i!=merchandise.size()-1)
			ofs << " ";
		}
		ofs << "\n";
	}

	ofs.close();
	return true;
}

enum Merchant_TradeInfo {
	Merchant_TradeInfo_BuyerName,
	Merchant_TradeInfo_MerchandiseID,
	Merchant_TradeInfo_MerchandiseName,
	Merchant_TradeInfo_purchaseQuantity,
	Merchant_TradeInfo_Price,
	Merchant_TradeInfo_Income,
};

void Merchant::addTradeInfo(const std::string& buyerName, int merchandiseId, std::string merchandiseName, int purchaseQuantity, int price)
{
	std::ofstream ofs(m_tradeInfoFilePath, std::ios_base::out | std::ios_base::app);

	ofs << buyerName;
	ofs << " ";

	ofs << merchandiseId;
	ofs << " ";

	ofs << merchandiseName;
	ofs << " ";

	ofs << purchaseQuantity;
	ofs << " ";

	ofs << price;
	ofs << " ";

	ofs << price* purchaseQuantity;
	ofs << "\n";

	

}

void Merchant::updateTemporaryTradeInfo()
{
	bool isModify = true;
	std::filesystem::path filePath(m_tradeInfoFilePath);
	if (std::filesystem::exists(filePath)) {
		auto lastModifyTime = std::filesystem::last_write_time(filePath);
		if (lastModifyTime == m_tradeInfoFileLastModifyTime) {
			isModify = false;
		}
		else {
			m_tradeInfoFileLastModifyTime = lastModifyTime;
		}
	}

	if (isModify)
	{

		//��վ���Ʒ��¼
		m_tradeInfo.clear();
		for (int i = 0; i < m_tradeInfoColMaxLen.size(); i++)m_tradeInfoColMaxLen[i] = m_tradeInfoColHeadName[i].size();

		std::ifstream ifs(m_tradeInfoFilePath);
		std::string content;

		//std::cout << "���\t" << "��ƷID\t" << "��Ʒ��\t" << "��Ʒʣ������\t" << "��Ʒ��������\t" << "��Ʒ������\t" << "��Ʒ���\t" << std::endl;
		while (std::getline(ifs, content)) {
			std::vector<std::string>singleInfo;
			//����ÿһ�е�������ֳ���
			int j = 0;
			for (int i = 0; i < m_tradeInfoColMaxLen.size(); i++) {
				int start = j;
				while (j < content.size() && content[j] != ' ')j++;
				//std::cout << j << std::endl;
				m_tradeInfoColMaxLen[i] = std::max(m_tradeInfoColMaxLen[i], j - start);
				singleInfo.push_back(content.substr(start, j - start));
				j++;
			}
			m_tradeInfo.push_back(singleInfo);
			
		}
		ifs.close();
	}
}

void Merchant::showAllTradeInfo()
{
	//���»�����
	updateTemporaryTradeInfo();

	//�����ͷ
	for (int j = 0; j < m_tradeInfoColMaxLen.size(); j++) {
		std::cout << std::left << std::setw(m_tradeInfoColMaxLen[j] + 2) << m_tradeInfoColHeadName[j];
	}
	std::cout << std::endl;
	//���������Ϣ
	for (int i = 0; i < m_tradeInfo.size(); i++) {
		
		for (int j = 0; j < m_tradeInfoColMaxLen.size(); j++) {
			std::cout << std::left << std::setw(m_tradeInfoColMaxLen[j] + 2) << m_tradeInfo[i][j];
		}

		std::cout << std::endl;
	}
}

void Merchant::optionWindow()
{
	system("cls");
	std::cout << "��ӭ������������ϵͳ��\n";
	std::cout << "��ѡ����Ҫʹ�õĹ��ܣ�\n";
	std::cout << Merchant_Option_Window_Option_Add_Merchandise<< ".�����Ʒ\n";
	std::cout << Merchant_Option_Window_Option_Show_All_Merchandise_Sale_Performance<<".�鿴������Ʒ���������\n";
	std::cout << Merchant_Option_Window_Option_Search_Specified_Merchandise_Sale_Performance<< ".����ָ����Ʒ������Ϣ\n";
	std::cout << Merchant_Option_Window_Option_Show_Inventory << ".�鿴������Ʒ������\n";
	std::cout << Merchant_Option_Window_Option_Show_Income << ".�鿴�������\n";
	std::cout << Merchant_Option_Window_Option_Show_TradeInfo << ".�鿴������Ϣ\n";

	std::cout << Merchant_Option_Window_Option_Quit << ".�˳�\n";
	
	std::cout << "\n";
	int option = 0;
	std::cin >> option;
	while (option <= Merchant_Option_Window_Option_Min || option >= Merchant_Option_Window_Option_Max) {
		std::cout << "��������ȷ��ѡ���Ӧ���:";
		std::cin >> option;
	}

	switch (option) {
	case Merchant_Option_Window_Option_Add_Merchandise:
	{
		addMerchandise();
		break;
	}
	case Merchant_Option_Window_Option_Show_All_Merchandise_Sale_Performance:
	{
		showSalesPerformance();
		break;
	}
	case Merchant_Option_Window_Option_Search_Specified_Merchandise_Sale_Performance:
	{
		findSpecifiedMerchandiseInfo();
		break;
	}
	case Merchant_Option_Window_Option_Quit:
	{
		m_isQuit = true;
		break;
	}
	case Merchant_Option_Window_Option_Show_Inventory:
	{
		showInventory();
		break;
	}
	case Merchant_Option_Window_Option_Show_Income:
	{
		showIncome();
		break;
	}
	case Merchant_Option_Window_Option_Show_TradeInfo:
	{
		showAllTradeInfo();
	}
	}
	std::cout << "�����������......\n";
	
	getchar();
	getchar();
}

void Merchant::play()
{
	while (!m_isQuit) {
		optionWindow();
	}
}
