#pragma once
#include"Login.h"
#include"InitialWindow.h"
#include"Merchant.h"
#include"Buyer.h"
#include"Manager.h"
class Control
{
public:
	//执行整个系统
	void play();

	//核实账号密码是否正确
	bool verifyCorrectnessOfAccountPwd(const char* filepath, const std::string& account, const std::string& pwd);
private:
	//登录
	Login m_login;
	//初始界面
	InitialWindow m_initWindow;
	
};

