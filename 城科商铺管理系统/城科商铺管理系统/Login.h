#pragma once
#include<iostream>
#include"protocol.h"
#include<string>
class Login
{
public:
	//��ʾ��¼����
	void showLoginWindow();
	//��ȡ�û�ѡ��ĵ�¼�û�����
	int getUserType();
	//��ȡ�˺�
	std::string getAccount();
	//��ȡ����
	std::string getPwd();
	//��ʾע�ᴰ��
	void showRegisterWindow();
	
};

