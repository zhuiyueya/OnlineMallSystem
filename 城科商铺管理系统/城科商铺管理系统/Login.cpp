#include "Login.h"

void Login::showLoginWindow()
{
	std::cout << "城科商铺管理系统！\n";
	std::cout << "请选择您要登录的用户类型：\n";

	std::cout <<USERTYPE_MERCHANT<< ".商户登录\n";
	std::cout << USERTYPE_BUYER << ".买家登录\n";
	std::cout << USERTYPE_MANAGER <<".系统管理员登录\n";
	
}



int Login::getUserType()
{
again:
	int type = 0;
	std::cin >> type;
	if (type >= USERTYPE_MAX || type <= USERTYPE_MIN) {
		std::cout << "请输入正确的用户类型！\n";
		goto again;
	}
	return type;
}

std::string Login::getAccount()
{
	std::cout << "请输入账号：";
	std::string account;
	std::cin >> account;
	return account;
}

std::string Login::getPwd()
{
	std::cout<<"请输入密码：";
	std::string pwd;
	std::cin >> pwd;
	return pwd;
}

void Login::showRegisterWindow()
{
	std::cout << "城科商铺管理系统！\n";
	std::cout << "请选择您要注册的用户类型：\n";

	std::cout << USERTYPE_MERCHANT << ".商户注册\n";
	std::cout << USERTYPE_BUYER << ".买家注册\n";
	
}

