#pragma once
#include"Login.h"
#include"InitialWindow.h"
#include"Merchant.h"
#include"Buyer.h"
#include"Manager.h"
class Control
{
public:
	//ִ������ϵͳ
	void play();

	//��ʵ�˺������Ƿ���ȷ
	bool verifyCorrectnessOfAccountPwd(const char* filepath, const std::string& account, const std::string& pwd);
private:
	//��¼
	Login m_login;
	//��ʼ����
	InitialWindow m_initWindow;
	
};

