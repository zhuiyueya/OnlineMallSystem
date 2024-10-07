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
	
	m_colHeadName = { "商品ID" , "商品名" , "商品剩余数量" , "商品销售数量" , "商品总数量" , "商品类别","价格","收入"};

	m_tradeInfoColMaxLen.resize(TRADEINFO_NUM,0);

	m_tradeInfoColHeadName = { "购买者","商品ID","商品名","购买数量","单价","总支付金额" };

	auto now = std::chrono::system_clock::now();

	// 计算过去的时间点，例如 1 小时之前
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

	std::cout << "请输入商品名：";
	std::cin >> m.name;
	while (searchSpecifiedMerchandiseInfoByName(m.name) != MERCHANT_CANNT_FIND_MERCHANDISE_INFO) {
		std::cout << "同名商品已经存在！请重新输入：";
		std::cin >> m.name;
	}
	std::cout << "请输入商品ID：";
	std::cin >> m.id;
	while (searchSpecifiedMerchandiseInfoByID(m.id) != MERCHANT_CANNT_FIND_MERCHANDISE_INFO) {
		std::cout << "同ID商品已经存在！请重新输入：";
		std::cin >> m.id;
	}

	std::cout << "请输入商品总数量：";
	std::cin >> m.totalNum;
	m.restNum = m.totalNum;
	m.saledNum = 0;
	std::cout << "请输入商品类别ID：";
	std::cin >> m.type;
	std::cout << "请输入商品的单价：";
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

//当商品信息文本太宽时，显示会出问题：每行商品信息之间出现空行，非代码问题，放大窗口就好了
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
	//	//清空旧商品记录
	//	m_merchandiseInfo.clear();
	//	for (int i = 0; i < m_maxInfoLen.size(); i++)m_maxInfoLen[i] = m_colHeadName[i].size();
	//
	//	std::ifstream ifs(m_merchandiseFilePath);
	//	std::string content;
	//	int index = 1;
	//	//std::cout << "序号\t" << "商品ID\t" << "商品名\t" << "商品剩余数量\t" << "商品销售数量\t" << "商品总数量\t" << "商品类别\t" << std::endl;
	//	while (std::getline(ifs, content)) {
	//
	//		//更新每一列的最大文字长度
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
	//输出商品信息
	for (int i = 0; i < m_merchandiseInfo.size(); i++) {
		//int index = 0;
		
		for (int j = 0; j < m_maxInfoLen.size(); j++) {
			//int pos = findS(m_merchandiseInfo[i], ' ', index);
			//int pos = m_merchandiseInfo[i].find(' ', index);
			
				//m_merchandiseInfo[i].substr(index, pos)
			//std::string(m_merchandiseInfo[i].begin() + index, m_merchandiseInfo[i].begin() + pos)
			//坑：substr第二个参数是个数
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
	//显示标头
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
	//显示标头
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
	
	std::cout << "总收入：" << totalIncome << std::endl;
	
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
	std::cout << "请选择您要查询的方式：\n";
	std::cout << "1.商品名\n";
	std::cout << "2.商品ID\n";
	int option = 1;
	std::cin >> option;
	while (option <= Merchant_Specified_Merchandise_Info_Option_MIN || option >= Merchant_Specified_Merchandise_Info_Option_MAX) {
		std::cout << "请输入正确的查询方式的编号：";
		std::cin >> option;
	}
	switch (option) {
	case Merchant_Specified_Merchandise_Info_Option_NAME: 
	{
		std::cout << "请输入您要查询的商品名：";
		std::string name;
		std::cin >> name;
		int ret=searchSpecifiedMerchandiseInfoByName(name);
		if (ret == MERCHANT_CANNT_FIND_MERCHANDISE_INFO) {//未查询到
			std::cout << "未查询到指定名字的商品!\n";
		}
		else {
			//显示标头
			for (int j = 0; j < m_maxInfoLen.size(); j++) {
				std::cout << std::left << std::setw(m_maxInfoLen[j] + 2) << m_colHeadName[j];
			}
			std::cout << std::endl;

			//显示商品信息
			for(int j=0;j<m_maxInfoLen.size();j++)
				std::cout << std::left << std::setw(m_maxInfoLen[j] + 2) << m_merchandiseInfo[ret][j];
			std::cout << std::endl;

		}
		break;
	}
	case Merchant_Specified_Merchandise_Info_Option_ID:
	{
		std::cout << "请输入您要查询的商品编号：";
		int id;
		std::cin >> id;
		int ret = searchSpecifiedMerchandiseInfoByID(id);
		if (ret == MERCHANT_CANNT_FIND_MERCHANDISE_INFO) {//未查询到
			std::cout << "未查询到指定编号的商品!\n";
		}
		else {
			//显示标头
			for (int j = 0; j < m_maxInfoLen.size(); j++) {
				std::cout << std::left << std::setw(m_maxInfoLen[j] + 2) << m_colHeadName[j];
			}
			std::cout << std::endl;

			//显示商品信息
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

		//清空旧商品记录
		m_merchandiseInfo.clear();
		for (int i = 0; i < m_maxInfoLen.size(); i++)m_maxInfoLen[i] = m_colHeadName[i].size();

		std::ifstream ifs(m_merchandiseFilePath);
		std::string content;
		
		//std::cout << "序号\t" << "商品ID\t" << "商品名\t" << "商品剩余数量\t" << "商品销售数量\t" << "商品总数量\t" << "商品类别\t" << std::endl;
		while (std::getline(ifs, content)) {
			std::vector<std::string>singleInfo;
			//更新每一列的最大文字长度
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
	//可在调用该函数时加锁，避免一个在修改时有人读取文件导致不准确
	updateTemporaryMerchandiseInfo();

	bool canFindSpecifiedID = false;
	//修改临时数据m_merchandiseInfo中指定ID的商品的数量，再将修改反应到文件中
	for (auto& a : m_merchandiseInfo) {
		if (atoi(a[Merchant_Merchandise_Info_Id].c_str()) == merchandiseID) {
			canFindSpecifiedID = true;
			//修改对应ID商品的数量
			int merchandiseRestNum = atoi(a[Merchant_Merchandise_Info_RestNum].c_str());
			if (merchandiseRestNum >= merchandiseNum) {
				merchandiseRestNum -= merchandiseNum;
				char restNum[32] = { 0 };
				_itoa_s(merchandiseRestNum, restNum, 10);
				a[Merchant_Merchandise_Info_RestNum] = restNum;//先修改缓存中的剩余数量，再循环外修改文件中的
				
				//修改售出数量
				memset(restNum, 0, 32);
				int merchandiseSaledNum= atoi(a[Merchant_Merchandise_Info_saledNum].c_str())+ merchandiseNum;
				_itoa_s(merchandiseSaledNum, restNum, 10);
				a[Merchant_Merchandise_Info_saledNum] = restNum;

				//修改商品总收入
				int iniIncome = atoi(a[Merchant_Merchandise_Info_Income].c_str());
				int price = atoi(a[Merchant_Merchandise_Info_Price].c_str());
				memset(restNum, 0, 32);
				_itoa_s(iniIncome + price * merchandiseNum, restNum, 10);
				a[Merchant_Merchandise_Info_Income] = restNum;
				
				//添加购买信息到交易信息文件中
				addTradeInfo(buyerName, merchandiseID, a[Merchant_Merchandise_Info_Name], merchandiseNum, atoi(a[Merchant_Merchandise_Info_Price].c_str()));

				break;
			}
			else {
				return false;//购买失败
			}
		}
	}
	
	//若没找到对应ID的商品，返回false
	if (!canFindSpecifiedID)return false;

	
	

	//将修改映射到文件中
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

		//清空旧商品记录
		m_tradeInfo.clear();
		for (int i = 0; i < m_tradeInfoColMaxLen.size(); i++)m_tradeInfoColMaxLen[i] = m_tradeInfoColHeadName[i].size();

		std::ifstream ifs(m_tradeInfoFilePath);
		std::string content;

		//std::cout << "序号\t" << "商品ID\t" << "商品名\t" << "商品剩余数量\t" << "商品销售数量\t" << "商品总数量\t" << "商品类别\t" << std::endl;
		while (std::getline(ifs, content)) {
			std::vector<std::string>singleInfo;
			//更新每一列的最大文字长度
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
	//更新缓冲区
	updateTemporaryTradeInfo();

	//输出标头
	for (int j = 0; j < m_tradeInfoColMaxLen.size(); j++) {
		std::cout << std::left << std::setw(m_tradeInfoColMaxLen[j] + 2) << m_tradeInfoColHeadName[j];
	}
	std::cout << std::endl;
	//输出交易信息
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
	std::cout << "欢迎来到店主管理系统！\n";
	std::cout << "请选择你要使用的功能：\n";
	std::cout << Merchant_Option_Window_Option_Add_Merchandise<< ".添加商品\n";
	std::cout << Merchant_Option_Window_Option_Show_All_Merchandise_Sale_Performance<<".查看各种商品的销售情况\n";
	std::cout << Merchant_Option_Window_Option_Search_Specified_Merchandise_Sale_Performance<< ".搜索指定商品销售信息\n";
	std::cout << Merchant_Option_Window_Option_Show_Inventory << ".查看各种商品库存情况\n";
	std::cout << Merchant_Option_Window_Option_Show_Income << ".查看收入情况\n";
	std::cout << Merchant_Option_Window_Option_Show_TradeInfo << ".查看交易信息\n";

	std::cout << Merchant_Option_Window_Option_Quit << ".退出\n";
	
	std::cout << "\n";
	int option = 0;
	std::cin >> option;
	while (option <= Merchant_Option_Window_Option_Min || option >= Merchant_Option_Window_Option_Max) {
		std::cout << "请输入正确的选项对应编号:";
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
	std::cout << "按任意键继续......\n";
	
	getchar();
	getchar();
}

void Merchant::play()
{
	while (!m_isQuit) {
		optionWindow();
	}
}
