#include "Login.h"

void Login::showLoginWindow()
{
	std::cout << "�ǿ����̹���ϵͳ��\n";
	std::cout << "��ѡ����Ҫ��¼���û����ͣ�\n";

	std::cout <<USERTYPE_MERCHANT<< ".�̻���¼\n";
	std::cout << USERTYPE_BUYER << ".��ҵ�¼\n";
	std::cout << USERTYPE_MANAGER <<".ϵͳ����Ա��¼\n";
	
}



int Login::getUserType()
{
again:
	int type = 0;
	std::cin >> type;
	if (type >= USERTYPE_MAX || type <= USERTYPE_MIN) {
		std::cout << "��������ȷ���û����ͣ�\n";
		goto again;
	}
	return type;
}

std::string Login::getAccount()
{
	std::cout << "�������˺ţ�";
	std::string account;
	std::cin >> account;
	return account;
}

std::string Login::getPwd()
{
	std::cout<<"���������룺";
	std::string pwd;
	std::cin >> pwd;
	return pwd;
}

void Login::showRegisterWindow()
{
	std::cout << "�ǿ����̹���ϵͳ��\n";
	std::cout << "��ѡ����Ҫע����û����ͣ�\n";

	std::cout << USERTYPE_MERCHANT << ".�̻�ע��\n";
	std::cout << USERTYPE_BUYER << ".���ע��\n";
	
}

