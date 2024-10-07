#include "Manager.h"
#include<iostream>
#include<fstream>
#define MERCHANT_APPLICATION_INFO_NUM 2
#define CANNT_FIND_MERCHANT_APPLICATION -1

enum Manager_Merchant_Application_Info {
	Manager_Merchant_Application_Info_Name,
	Manager_Merchant_Application_Info_Pwd,
};

Manager::Manager(const std::string& account, const std::string& pwd):User(account,pwd)
{
	auto now = std::chrono::system_clock::now();

	m_merchantApplicationInfoFileLastModifyTime
		= std::filesystem::file_time_type(std::chrono::duration_cast<std::filesystem::file_time_type::duration>(
		now.time_since_epoch()
	));
	m_merchantApplicationInfoColMaxLen.resize(MERCHANT_APPLICATION_INFO_NUM, 0);
	m_m_merchantApplicationInfoColHeadName = { "商户名","商户密码" };

	m_isQuit = false;
}

void Manager::showAllAppliedMerchant()
{
	updateTemporaryMerchantApplicationInfo();
	for (int i = 0; i < m_m_merchantApplicationInfoColHeadName.size(); i++) {
		std::cout << std::left << std::setw(m_merchantApplicationInfoColMaxLen[i] + 2) << m_m_merchantApplicationInfoColHeadName[i];
	}
	std::cout << std::endl;

	for (int i = 0; i < m_merchantApplicationInfo.size(); i++) {
		for (int j = 0; j < m_merchantApplicationInfoColMaxLen.size(); j++) {
			std::cout << std::left << std::setw(m_merchantApplicationInfoColMaxLen[j] + 2) << m_merchantApplicationInfo[i][j];
		}
		std::cout << std::endl;
	}

	acceptMerchantApplication();
}

void Manager::updateTemporaryMerchantApplicationInfo()
{
	bool isModify = true;
	std::filesystem::path filePath(MERCHANT_APPLICAIONS_FILE_PATH);
	if (std::filesystem::exists(filePath)) {
		auto lastModifyTime = std::filesystem::last_write_time(filePath);
		if (lastModifyTime == m_merchantApplicationInfoFileLastModifyTime) {
			isModify = false;
		}
		else {
			m_merchantApplicationInfoFileLastModifyTime = lastModifyTime;
		}
	}

	if (isModify)
	{

		//清空旧商品记录
		m_merchantApplicationInfo.clear();
		for (int i = 0; i < m_merchantApplicationInfoColMaxLen.size(); i++)m_merchantApplicationInfoColMaxLen[i] = m_m_merchantApplicationInfoColHeadName[i].size();

		std::ifstream ifs(MERCHANT_APPLICAIONS_FILE_PATH);
		std::string content;

		while (std::getline(ifs, content)) {
			std::vector<std::string>singleInfo;
			//更新每一列的最大文字长度
			int j = 0;
			for (int i = 0; i < m_merchantApplicationInfoColMaxLen.size(); i++) {
				int start = j;
				while (j < content.size() && content[j] != ' ')j++;
				//std::cout << j << std::endl;
				m_merchantApplicationInfoColMaxLen[i] = std::max(m_merchantApplicationInfoColMaxLen[i], j - start);
				singleInfo.push_back(content.substr(start, j - start));
				j++;
			}

			m_merchantApplicationInfo.push_back(singleInfo);

		}
		ifs.close();
	}
}

void Manager::acceptMerchantApplication()
{
	std::cout << "请输入您要批准的商户名：";
	std::string name;
	std::cin >> name;
	int index = findSpecifiedMerchantApplication(name);
	if (index == CANNT_FIND_MERCHANT_APPLICATION) {
		std::cout << "未找到指定商户名！\n";
		return;
	}
	//需要保证在findSpecifiedMerchantApplication更新缓存后到这里要修改时无新的商户申请
	
	//先将其加入商户账号密码文件
	std::string account = m_merchantApplicationInfo[index][Manager_Merchant_Application_Info_Name];
	std::string pwd= m_merchantApplicationInfo[index][Manager_Merchant_Application_Info_Pwd];
	
	std::ofstream ofs(MERCHANT_FILE_PATH, std::ios_base::out | std::ios_base::app);
	ofs << account;
	ofs << " ";
	ofs << pwd;
	ofs << "\n";
	ofs.close();

	//再将其从申请文件中删除
	m_merchantApplicationInfo.erase(m_merchantApplicationInfo.begin() + index);
	
	ofs = std::ofstream(MERCHANT_APPLICAIONS_FILE_PATH,std::ios_base::out|std::ios_base::trunc);
	for (auto &info:m_merchantApplicationInfo) {
		for (int i = 0; i < info.size();i++) {
			ofs << info[i];
			if (i < (int)info.size() - 1) {
				ofs << " ";
			}

		}
		ofs << "\n";
	}
	ofs.close();

	//更新缓存
	updateTemporaryMerchantApplicationInfo();
}

void Manager::acceptAllMerchantApplication() {

	//先加入商户账号密码文件
	std::ofstream ofs(MERCHANT_FILE_PATH, std::ios_base::out | std::ios_base::app);
	for (int i = 0; i < m_merchantApplicationInfo.size(); i++) {
		std::string account = m_merchantApplicationInfo[i][Manager_Merchant_Application_Info_Name];
		std::string pwd = m_merchantApplicationInfo[i][Manager_Merchant_Application_Info_Pwd];

		ofs << account;
		ofs << " ";
		ofs << pwd;
		ofs << "\n";
		std::cout << account << " " << pwd << std::endl;
	}
	ofs.close();

	//再将其从申请文件中删除
	m_merchantApplicationInfo.clear();

	ofs = std::ofstream(MERCHANT_APPLICAIONS_FILE_PATH, std::ios_base::out | std::ios_base::trunc);
	ofs.close();

	//更新缓存
	updateTemporaryMerchantApplicationInfo();
	std::cout<<"已通过所有用户申请！\n";
}

int Manager::findSpecifiedMerchantApplication(const std::string& name)
{
	updateTemporaryMerchantApplicationInfo();
	for (int i = 0; i < m_merchantApplicationInfo.size(); i++) {
		if (m_merchantApplicationInfo[i][Manager_Merchant_Application_Info_Name] == name) {
			return i;
		}
	}
	return CANNT_FIND_MERCHANT_APPLICATION;
}

enum Manager_Option_Window_Option {
	Manager_Option_Window_Option_Min,
	Manager_Option_Window_Option_Show_All_Merchant_Applications,
	Manager_Option_Window_Option_Accept_Merchant_Application,
	Manager_Option_Window_Option_Accept_All_Merchant_Applications,
	Manager_Option_Window_Option_Copy_All_Data_File,
	Manager_Option_Window_Option_Recover_Data,

	Manager_Option_Window_Option_Init_System,
	Manager_Option_Window_Option_Delete_Merchant,
	Manager_Option_Window_Option_Delete_Buyer,
	Manager_Option_Window_Option_Show_All_Merchant,
	Manager_Option_Window_Option_Show_All_Buyer,
	Manager_Option_Window_Option_Quit,
	Manager_Option_Window_Option_Max,
};

void Manager::optionWindow() {
	system("cls");
	std::cout << "系统管理员操作界面！\n";
	std::cout << Manager_Option_Window_Option_Show_All_Merchant_Applications << ".显示所有申请商铺的商户\n";
	std::cout << Manager_Option_Window_Option_Accept_Merchant_Application << ".同意指定商户的申请\n";
	std::cout << Manager_Option_Window_Option_Accept_All_Merchant_Applications << ".通过所有商户的申请\n";
	std::cout << Manager_Option_Window_Option_Copy_All_Data_File << ".备份数据\n";
	std::cout << Manager_Option_Window_Option_Recover_Data << ".恢复数据\n";
	std::cout << Manager_Option_Window_Option_Init_System << ".初始化系统\n";
	std::cout << Manager_Option_Window_Option_Delete_Merchant << ".删除指定商户账号\n";
	std::cout << Manager_Option_Window_Option_Delete_Buyer << ".删除指定买家账号\n";
	std::cout << Manager_Option_Window_Option_Show_All_Merchant << ".显示所有商户的账号信息\n";
	std::cout << Manager_Option_Window_Option_Show_All_Buyer << ".显示所有买家的账号信息\n";

	std::cout << Manager_Option_Window_Option_Quit << ".退出\n";
	int option = 0;
	std::cin >> option;
	switch (option) {
	case Manager_Option_Window_Option_Show_All_Buyer:
	{
		showAllBuyer();
	}
	case Manager_Option_Window_Option_Show_All_Merchant:
	{
		showAllMerchant();
		break;
	}
	case Manager_Option_Window_Option_Delete_Buyer:
	{
		deleteSpecifiedBuyerAccount();
		break;
	}
	case Manager_Option_Window_Option_Delete_Merchant:
	{
		deleteSpecifiedMerchantAccount();
		break;
	}
	case Manager_Option_Window_Option_Show_All_Merchant_Applications:
	{
		showAllAppliedMerchant();
		break;
	}
	case Manager_Option_Window_Option_Accept_Merchant_Application:
	{
		acceptMerchantApplication();
		break;
	}
	case Manager_Option_Window_Option_Accept_All_Merchant_Applications:
	{
		acceptAllMerchantApplication();
		break;
	}
	case Manager_Option_Window_Option_Quit:
	{
		m_isQuit = true;
		break;
	}
	case Manager_Option_Window_Option_Copy_All_Data_File:
	{
		copyAllDataFile();
		break;
	}
	case Manager_Option_Window_Option_Init_System:
	{
		initSystem();
		break;
	}
	case Manager_Option_Window_Option_Recover_Data:
	{
		recoverData();
		break;
	}
	}

	std::cout << "按回车键继续......";
	getchar();
	getchar();

}

void Manager::play() {
	while (!m_isQuit) {
		optionWindow();
	}
}

void Manager::copyAllDataFile()
{
	std::cout << "请输入备份的目的路径(绝对路径）:";
	std::string dst;
	std::cin >> dst;
	
	namespace fs = std::filesystem;
	fs::path current_working_dir = fs::current_path();
	
	fs::path dstPath=dst;
	fs::path srcPath = fs::absolute(".");
	//如果目录不存在则创建
	if (!fs::exists(dstPath)) {
		fs::create_directories(dstPath);
	}

	for (const auto& entry : fs::directory_iterator(srcPath)) {
		 
		if (entry.is_regular_file() && entry.path().extension() == ".txt") {
			if (entry.path().filename() == MANAGER_FILE_NAME)continue;
			fs::path dst_file_path = dstPath / entry.path().filename();
			fs::copy_file(entry.path(), dst_file_path);
		}
	}

	std::cout << "备份成功！\n";

}

void Manager::recoverData()
{
	std::cout << "注意：该操作将覆盖现有的所有数据!\n";
	std::cout << "是否继续操作？(是：y/Y,否：n/N)\n";
	std::string optionYN;
	std::cin >> optionYN;
	if (optionYN == "Y" || optionYN == "y") {

	}
	else {
		return;
	}

	std::cout << "请输入备份所位于的路径(绝对路径）:";
	std::string src;
	std::cin >> src;

	namespace fs = std::filesystem;
	fs::path current_working_dir = fs::current_path();
	
	fs::path srcPath = src;
	fs::path dstPath = fs::absolute(".");
	//如果源目录不存在则返回
	if (!fs::exists(src)) {
		std::cout << "恢复失败！路径不存在！\n";
		return;
	}

	//先将当前目录（工作目录）下的数据清空
	for (const auto& entry : fs::directory_iterator(dstPath)) {

		if (entry.is_regular_file() && entry.path().extension() == ".txt") {
			if (entry.path().filename() == MANAGER_FILE_NAME)continue;
			fs::remove(entry.path());
		}
	}

	//将指定目录中的数据拷贝过来
	for (const auto& entry : fs::directory_iterator(srcPath)) {
		
		if (entry.is_regular_file() && entry.path().extension() == ".txt") {
			
			fs::path dst_file_path = dstPath / entry.path().filename();
			fs::copy_file(entry.path(), dst_file_path);
		}
	}
	std::cout << "恢复成功!\n";
}

void Manager::initSystem()
{
	std::cout << "是否确认初始化系统？请输入系统管理员账号和密码进行验证!\n" << std::endl;
	std::string account, pwd;
	std::cout << "请输入账号：";
	std::cin >> account;
	std::cout << "请输入密码:";
	std::cin >> pwd;
	if (pwd != m_pwd || account != m_account) {
		std::cout << "账号或密码错误！\n";
		return;
	}
	namespace fs = std::filesystem;
	fs::path srcPath = fs::absolute(".");

	for (const auto& entry : fs::directory_iterator(srcPath)) {

		if (entry.is_regular_file() && entry.path().extension() == ".txt") {
			if (entry.path().filename() == MANAGER_FILE_NAME)continue;
			fs::remove(entry.path());
		}
	}
	std::cout << "初始化成功！\n";
}

bool Manager::deleteSpecifiedAccount(const char* filePath, std::string account)
{
	

	std::ifstream ifs(filePath);
	std::vector<std::string>info;
	std::string line;
	std::string pwd;
	bool isExist = false;
	//先将除了指定账号的其他账号密码行存储info
	while (std::getline(ifs, line)) {
		if (account != line.substr(0, line.find(' '))) {
			info.push_back(line);
		}
		else {
			int pos = line.find(' ');
			pwd = line.substr(pos + 1, (int)line.size() - pos-1);

			

			//删除商户商品信息文件
			std::filesystem::path filePath = "./" + account + pwd + "Merchandise.txt";
			if (std::filesystem::exists(filePath)) {
				std::filesystem::remove(filePath);
			}
			//删除商户交易信息文件
			filePath = "./" + account + pwd + "TradeInfo.txt";
			if (std::filesystem::exists(filePath)) {
				std::filesystem::remove(filePath);
			}

			//删除商户的员工信息文件
			filePath = "./" + account + pwd + "Employee.txt";
			if (std::filesystem::exists(filePath)) {
				std::filesystem::remove(filePath);
			}

			
			
			isExist = true;
		}
	}

	ifs.close();

	//不存在指定用户，返回
	if (!isExist)return false;

	//将原文件清空并把info中的数据传入
	std::ofstream ofs(filePath,std::ios_base::out|std::ios_base::trunc);
	for (auto& s : info) {
		ofs << s;
		ofs << "\n";
	}
	ofs.close();
	return true;
}

void Manager::deleteSpecifiedMerchantAccount()
{
	std::string account;
	std::cout << "请输入您要注销的商户账号：";
	std::cin >> account;
	if (deleteSpecifiedAccount(MERCHANT_FILE_PATH, account)) {
		std::cout << "删除商户账号：" << account << "成功！\n";
	}
	else {
		std::cout << "删除失败，不存在" << account << "商户!\n";
	}
}

void Manager::deleteSpecifiedBuyerAccount()
{
	std::string account;
	std::cout << "请输入您要注销的买家账号：";
	std::cin >> account;
	if (deleteSpecifiedAccount(BUYER_FILE_PATH, account)) {
		std::cout << "删除买家账号：" << account << "成功！\n";
	}
	else {
		std::cout << "删除失败，不存在" << account << "买家!\n";
	}
}

void Manager::showUserInfo(const char* filePath)
{
	std::vector<std::vector<std::string>>info;
	std::vector<int>colMaxLen(2, 0);
	colMaxLen[0] = 2;
	colMaxLen[1] = 2;
	std::ifstream ifs(filePath);
	std::string line;
	while (std::getline(ifs, line)) {
		std::vector<std::string>row;
		int pos = line.find(' ');
		
		row.push_back(line.substr(0, pos));
		row.push_back(line.substr(pos + 1, (int)line.size() - pos - 1));
		colMaxLen[0] = std::max(colMaxLen[0], pos);
		colMaxLen[1] = std::max(colMaxLen[1], (int)line.size() - pos - 1);
		info.push_back(row);
		
	}
	std::cout << std::left << std::setw(colMaxLen[0]) << "账号";
	std::cout << std::left << std::setw(colMaxLen[1]) << "密码";
	std::cout << std::endl;
	for (auto& a : info) {
		for (int i = 0; i < colMaxLen.size(); i++) {
			std::cout << std::left << std::setw(colMaxLen[i]) << a[i];
		}
		std::cout << std::endl;
	}

}

void Manager::showAllMerchant()
{
	showUserInfo(MERCHANT_FILE_PATH);
}

void Manager::showAllBuyer()
{
	showUserInfo(BUYER_FILE_PATH);
}
