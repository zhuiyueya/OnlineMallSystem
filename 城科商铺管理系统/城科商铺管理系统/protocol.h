#pragma once
#include<string>
//����-������-��C++���Ա�׼-��C++17
#define MERCHANT_FILE_PATH "./merchant.txt"//�洢�̻��˺������ļ�·��
#define BUYER_FILE_PATH "./buyer.txt"//�洢����˺������ļ�·��
#define MANAGER_FILE_PATH "./manager.txt"//�洢ϵͳ����Ա�˺������ļ�·��
#define MANAGER_FILE_NAME "manager.txt"

#define MERCHANT_APPLICAIONS_FILE_PATH "./merchantApplications.txt"//�洢����ע���̻���������ļ�·��

#define MERCHANDISE_INFO_NUM 8//��Ʒ��Ϣ����
#define allGoodsFilePath "./allgoods.txt"//�洢ϵͳ�������̻���������Ʒ���ļ�·��

#define TRADEINFO_NUM 6//������Ϣ����
enum merchandiseType {
	MT_FOOD,
	MT_CLOTHES,
	MT_BOOK,
	
};

enum userType {
	USERTYPE_MIN=0,
	USERTYPE_MERCHANT,
	USERTYPE_BUYER,
	USERTYPE_MANAGER,
	USERTYPE_MAX,
};
//��ʼ�����ѡ���
enum INITIA_WINDOW_OPTION {
	IW_OPTION_MIN,
	IW_OPTION_LOGIN,
	IW_OPTION_REGISTER,
	IW_OPTION_EXIT,
	IW_OPTION_MAX,
};
/*
	��Ʒ��Ϣ���
		1.��Ʒ���
		2.��Ʒ��
		3.��Ʒʣ������
		4.��Ʒ������
		5.��Ʒ����������
		6.��Ʒ���
		7.�۸�
		8.����
*/
struct Merchandise {
	int id;
	std::string name;
	int totalNum;
	int restNum;
	int saledNum;
	int price;
	int income;
	int type;
	Merchandise(){}
	Merchandise(int merchandiseId, std::string merchandiseName, int mtotalNum, int mtype):id(merchandiseId),name(merchandiseName),totalNum(mtotalNum),restNum(mtotalNum),saledNum(0),type(mtype){}
};

