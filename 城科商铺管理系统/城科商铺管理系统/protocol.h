#pragma once
#include<string>
//属性-》常规-》C++语言标准-》C++17
#define MERCHANT_FILE_PATH "./merchant.txt"//存储商户账号密码文件路径
#define BUYER_FILE_PATH "./buyer.txt"//存储买家账号密码文件路径
#define MANAGER_FILE_PATH "./manager.txt"//存储系统管理员账号密码文件路径
#define MANAGER_FILE_NAME "manager.txt"

#define MERCHANT_APPLICAIONS_FILE_PATH "./merchantApplications.txt"//存储申请注册商户的申请的文件路径

#define MERCHANDISE_INFO_NUM 8//商品信息数量
#define allGoodsFilePath "./allgoods.txt"//存储系统中所有商户的所有商品的文件路径

#define TRADEINFO_NUM 6//交易信息数量
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
//初始界面的选项功能
enum INITIA_WINDOW_OPTION {
	IW_OPTION_MIN,
	IW_OPTION_LOGIN,
	IW_OPTION_REGISTER,
	IW_OPTION_EXIT,
	IW_OPTION_MAX,
};
/*
	商品信息设计
		1.商品编号
		2.商品名
		3.商品剩余数量
		4.商品总数量
		5.商品已销售数量
		6.商品类别
		7.价格
		8.收入
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

