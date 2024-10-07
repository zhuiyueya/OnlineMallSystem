#pragma once
#include "User.h"
#include<vector>
#include<string>
#include"Conversion.h"
class Buyer :
    public User
{
public:
    void showMerchandiseOfOneMerchant();//展示一个商户的商品
    void showAllMerchantInfo();//展示所有商户
    void purchaseDesiredMerchandise(std::string name);//购买想要的商品
    Buyer(std::string account,std::string pwd);
    
    //选择界面
    void optionWindow();
    //主循环
    void play();
private:
    std::vector<std::vector<std::string>>m_merchandiseInfo;
    std::vector<int>m_maxColLen;
    Conversion m_conversion;
    std::vector<std::string>m_merchantsName;
    bool m_isQuit=false;
    
};

