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
	m_m_merchantApplicationInfoColHeadName = { "�̻���","�̻�����" };

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

		//��վ���Ʒ��¼
		m_merchantApplicationInfo.clear();
		for (int i = 0; i < m_merchantApplicationInfoColMaxLen.size(); i++)m_merchantApplicationInfoColMaxLen[i] = m_m_merchantApplicationInfoColHeadName[i].size();

		std::ifstream ifs(MERCHANT_APPLICAIONS_FILE_PATH);
		std::string content;

		while (std::getline(ifs, content)) {
			std::vector<std::string>singleInfo;
			//����ÿһ�е�������ֳ���
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
	std::cout << "��������Ҫ��׼���̻�����";
	std::string name;
	std::cin >> name;
	int index = findSpecifiedMerchantApplication(name);
	if (index == CANNT_FIND_MERCHANT_APPLICATION) {
		std::cout << "δ�ҵ�ָ���̻�����\n";
		return;
	}
	//��Ҫ��֤��findSpecifiedMerchantApplication���»��������Ҫ�޸�ʱ���µ��̻�����
	
	//�Ƚ�������̻��˺������ļ�
	std::string account = m_merchantApplicationInfo[index][Manager_Merchant_Application_Info_Name];
	std::string pwd= m_merchantApplicationInfo[index][Manager_Merchant_Application_Info_Pwd];
	
	std::ofstream ofs(MERCHANT_FILE_PATH, std::ios_base::out | std::ios_base::app);
	ofs << account;
	ofs << " ";
	ofs << pwd;
	ofs << "\n";
	ofs.close();

	//�ٽ���������ļ���ɾ��
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

	//���»���
	updateTemporaryMerchantApplicationInfo();
}

void Manager::acceptAllMerchantApplication() {

	//�ȼ����̻��˺������ļ�
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

	//�ٽ���������ļ���ɾ��
	m_merchantApplicationInfo.clear();

	ofs = std::ofstream(MERCHANT_APPLICAIONS_FILE_PATH, std::ios_base::out | std::ios_base::trunc);
	ofs.close();

	//���»���
	updateTemporaryMerchantApplicationInfo();
	std::cout<<"��ͨ�������û����룡\n";
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
	std::cout << "ϵͳ����Ա�������棡\n";
	std::cout << Manager_Option_Window_Option_Show_All_Merchant_Applications << ".��ʾ�����������̵��̻�\n";
	std::cout << Manager_Option_Window_Option_Accept_Merchant_Application << ".ͬ��ָ���̻�������\n";
	std::cout << Manager_Option_Window_Option_Accept_All_Merchant_Applications << ".ͨ�������̻�������\n";
	std::cout << Manager_Option_Window_Option_Copy_All_Data_File << ".��������\n";
	std::cout << Manager_Option_Window_Option_Recover_Data << ".�ָ�����\n";
	std::cout << Manager_Option_Window_Option_Init_System << ".��ʼ��ϵͳ\n";
	std::cout << Manager_Option_Window_Option_Delete_Merchant << ".ɾ��ָ���̻��˺�\n";
	std::cout << Manager_Option_Window_Option_Delete_Buyer << ".ɾ��ָ������˺�\n";
	std::cout << Manager_Option_Window_Option_Show_All_Merchant << ".��ʾ�����̻����˺���Ϣ\n";
	std::cout << Manager_Option_Window_Option_Show_All_Buyer << ".��ʾ������ҵ��˺���Ϣ\n";

	std::cout << Manager_Option_Window_Option_Quit << ".�˳�\n";
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

	std::cout << "���س�������......";
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
	std::cout << "�����뱸�ݵ�Ŀ��·��(����·����:";
	std::string dst;
	std::cin >> dst;
	
	namespace fs = std::filesystem;
	fs::path current_working_dir = fs::current_path();
	
	fs::path dstPath=dst;
	fs::path srcPath = fs::absolute(".");
	//���Ŀ¼�������򴴽�
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

	std::cout << "���ݳɹ���\n";

}

void Manager::recoverData()
{
	std::cout << "ע�⣺�ò������������е���������!\n";
	std::cout << "�Ƿ����������(�ǣ�y/Y,��n/N)\n";
	std::string optionYN;
	std::cin >> optionYN;
	if (optionYN == "Y" || optionYN == "y") {

	}
	else {
		return;
	}

	std::cout << "�����뱸����λ�ڵ�·��(����·����:";
	std::string src;
	std::cin >> src;

	namespace fs = std::filesystem;
	fs::path current_working_dir = fs::current_path();
	
	fs::path srcPath = src;
	fs::path dstPath = fs::absolute(".");
	//���ԴĿ¼�������򷵻�
	if (!fs::exists(src)) {
		std::cout << "�ָ�ʧ�ܣ�·�������ڣ�\n";
		return;
	}

	//�Ƚ���ǰĿ¼������Ŀ¼���µ��������
	for (const auto& entry : fs::directory_iterator(dstPath)) {

		if (entry.is_regular_file() && entry.path().extension() == ".txt") {
			if (entry.path().filename() == MANAGER_FILE_NAME)continue;
			fs::remove(entry.path());
		}
	}

	//��ָ��Ŀ¼�е����ݿ�������
	for (const auto& entry : fs::directory_iterator(srcPath)) {
		
		if (entry.is_regular_file() && entry.path().extension() == ".txt") {
			
			fs::path dst_file_path = dstPath / entry.path().filename();
			fs::copy_file(entry.path(), dst_file_path);
		}
	}
	std::cout << "�ָ��ɹ�!\n";
}

void Manager::initSystem()
{
	std::cout << "�Ƿ�ȷ�ϳ�ʼ��ϵͳ��������ϵͳ����Ա�˺ź����������֤!\n" << std::endl;
	std::string account, pwd;
	std::cout << "�������˺ţ�";
	std::cin >> account;
	std::cout << "����������:";
	std::cin >> pwd;
	if (pwd != m_pwd || account != m_account) {
		std::cout << "�˺Ż��������\n";
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
	std::cout << "��ʼ���ɹ���\n";
}

bool Manager::deleteSpecifiedAccount(const char* filePath, std::string account)
{
	

	std::ifstream ifs(filePath);
	std::vector<std::string>info;
	std::string line;
	std::string pwd;
	bool isExist = false;
	//�Ƚ�����ָ���˺ŵ������˺������д洢info
	while (std::getline(ifs, line)) {
		if (account != line.substr(0, line.find(' '))) {
			info.push_back(line);
		}
		else {
			int pos = line.find(' ');
			pwd = line.substr(pos + 1, (int)line.size() - pos-1);

			

			//ɾ���̻���Ʒ��Ϣ�ļ�
			std::filesystem::path filePath = "./" + account + pwd + "Merchandise.txt";
			if (std::filesystem::exists(filePath)) {
				std::filesystem::remove(filePath);
			}
			//ɾ���̻�������Ϣ�ļ�
			filePath = "./" + account + pwd + "TradeInfo.txt";
			if (std::filesystem::exists(filePath)) {
				std::filesystem::remove(filePath);
			}

			//ɾ���̻���Ա����Ϣ�ļ�
			filePath = "./" + account + pwd + "Employee.txt";
			if (std::filesystem::exists(filePath)) {
				std::filesystem::remove(filePath);
			}

			
			
			isExist = true;
		}
	}

	ifs.close();

	//������ָ���û�������
	if (!isExist)return false;

	//��ԭ�ļ���ղ���info�е����ݴ���
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
	std::cout << "��������Ҫע�����̻��˺ţ�";
	std::cin >> account;
	if (deleteSpecifiedAccount(MERCHANT_FILE_PATH, account)) {
		std::cout << "ɾ���̻��˺ţ�" << account << "�ɹ���\n";
	}
	else {
		std::cout << "ɾ��ʧ�ܣ�������" << account << "�̻�!\n";
	}
}

void Manager::deleteSpecifiedBuyerAccount()
{
	std::string account;
	std::cout << "��������Ҫע��������˺ţ�";
	std::cin >> account;
	if (deleteSpecifiedAccount(BUYER_FILE_PATH, account)) {
		std::cout << "ɾ������˺ţ�" << account << "�ɹ���\n";
	}
	else {
		std::cout << "ɾ��ʧ�ܣ�������" << account << "���!\n";
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
	std::cout << std::left << std::setw(colMaxLen[0]) << "�˺�";
	std::cout << std::left << std::setw(colMaxLen[1]) << "����";
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
