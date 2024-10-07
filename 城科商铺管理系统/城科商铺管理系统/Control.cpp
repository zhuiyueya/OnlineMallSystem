#include "Control.h"
#include<fstream>
void Control::play()
{
	while (1) {
		system("cls");
		m_initWindow.draw();
		int inputFunctionOption = m_initWindow.getInputFunction();
		system("cls");
		switch (inputFunctionOption) {
		case IW_OPTION_LOGIN: {
			
			m_login.showLoginWindow();
			int userType = m_login.getUserType();
			std::string account=m_login.getAccount();
			std::string pwd=m_login.getPwd();

			switch (userType) {
			case USERTYPE_MERCHANT: {
				while(!verifyCorrectnessOfAccountPwd(MERCHANT_FILE_PATH, account, pwd)) {
					std::cout << "�˺�/�������\n";
					account = m_login.getAccount();
					pwd=m_login.getPwd();
				}
				//��¼�ɹ�
				Merchant merchant(account, pwd);
				merchant.play();
				break;
			}
			case USERTYPE_BUYER:
			{
				while (!verifyCorrectnessOfAccountPwd(BUYER_FILE_PATH, account, pwd)) {
					std::cout << "�˺�/�������\n";
					account = m_login.getAccount();
					pwd = m_login.getPwd();
				}
				Buyer buyer(account, pwd);
				buyer.play();
				break;
			}
			case USERTYPE_MANAGER:
			{
				while (!verifyCorrectnessOfAccountPwd(MANAGER_FILE_PATH, account, pwd)) {
					std::cout << "�˺�/�������\n";
					account = m_login.getAccount();
					pwd = m_login.getPwd();
				}
				Manager manager(account, pwd);
				manager.play();
				break;
			}
			}

			
			
			break;
		}
		case IW_OPTION_REGISTER:
		{
			m_login.showRegisterWindow();
			int userType = m_login.getUserType();
			std::string account = m_login.getAccount();
			std::string pwd = m_login.getPwd();
			switch (userType) {
			case USERTYPE_BUYER:
			{
				std::ofstream ofs(BUYER_FILE_PATH,std::ios_base::out|std::ios_base::app);
				ofs << account;
				ofs << " ";
				ofs << pwd;
				ofs << "\n";
				ofs.close();
				std::cout << "ע��ɹ���\n";
				break;
			}
			case USERTYPE_MERCHANT:
			{
				//to do ��ע��ʱ�ṩ������Ϣ�Ա�ȷ��
				std::ofstream ofs(MERCHANT_APPLICAIONS_FILE_PATH, std::ios_base::out | std::ios_base::app);
				ofs << account;
				ofs << " ";
				ofs << pwd;
				ofs << "\n";
				ofs.close();
				std::cout << "�ȴ�ϵͳ����Աͨ����......\n";
				break;
			}
			case USERTYPE_MANAGER: 
			{
				std::cout << "ä�����㷢����ä�㡣\nϵͳ����Ա��֧��ע��Ŷ!\n";
				break;
			}
			}

			break;
		}
		case IW_OPTION_EXIT:
			std::cout << "��ӭ�ٴ�ʹ��!\n";
			exit(1);
			break;
		}

	}
}

bool Control::verifyCorrectnessOfAccountPwd(const char* filepath, const std::string& account, const std::string& pwd)
{
	std::ifstream ifs(filepath);
	std::string twin;
	while (std::getline(ifs, twin)) {
		size_t pos = twin.find(' ');
		//std::cout << twin << std::endl;
		std::string ac(twin.begin(), twin.begin()+pos);
		if (ac == account && std::string(twin.begin() + pos + 1, twin.end()) == pwd) {
			ifs.close();
			return true;
		}
	}
	ifs.close();
	return false;
}
