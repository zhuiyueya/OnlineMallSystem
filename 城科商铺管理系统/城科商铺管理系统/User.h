#pragma once
#include<string>
#include"protocol.h"
//����ʹ���ߵĻ���
class User
{
public:
	User(std::string account, std::string pwd);
	std::string m_account;
	std::string m_pwd;
	
};

