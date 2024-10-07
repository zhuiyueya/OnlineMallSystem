#pragma once
#include<string>
#include"protocol.h"
//各种使用者的基类
class User
{
public:
	User(std::string account, std::string pwd);
	std::string m_account;
	std::string m_pwd;
	
};

