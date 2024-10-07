#pragma once
#include "User.h"
#include<vector>
#include<string>
#include"Conversion.h"
class Buyer :
    public User
{
public:
    void showMerchandiseOfOneMerchant();//չʾһ���̻�����Ʒ
    void showAllMerchantInfo();//չʾ�����̻�
    void purchaseDesiredMerchandise(std::string name);//������Ҫ����Ʒ
    Buyer(std::string account,std::string pwd);
    
    //ѡ�����
    void optionWindow();
    //��ѭ��
    void play();
private:
    std::vector<std::vector<std::string>>m_merchandiseInfo;
    std::vector<int>m_maxColLen;
    Conversion m_conversion;
    std::vector<std::string>m_merchantsName;
    bool m_isQuit=false;
    
};

