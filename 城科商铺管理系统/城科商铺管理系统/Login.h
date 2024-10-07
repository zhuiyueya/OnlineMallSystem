#pragma once
#include<iostream>
#include"protocol.h"
#include<string>
class Login
{
public:
	//显示登录窗口
	void showLoginWindow();
	//获取用户选择的登录用户类型
	int getUserType();
	//获取账号
	std::string getAccount();
	//获取密码
	std::string getPwd();
	//显示注册窗口
	void showRegisterWindow();
	
};

