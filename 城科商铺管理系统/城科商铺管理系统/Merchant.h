#pragma once
#include "User.h"
#include<fstream>
#include<vector>
#include<filesystem>
#include<chrono>
class Merchant :
    public User
{

public:

    Merchant(std::string account, std::string pwd);
    //�����Ʒ
    void addMerchandise();

    //�鿴������Ʒ���������
    void showSalesPerformance();

    //��ʾ���ֲ�Ʒ�Ŀ�����
    void showInventory();

    //��ʾ����ͳ����Ϣ
    void showIncome();
    //���Ա��
    void addEmployee();

    //��ѯĳ����Ʒ����Ϣ
    void findSpecifiedMerchandiseInfo();
    //ͨ�����ֲ�ѯĳ����Ʒ����Ϣ
    int searchSpecifiedMerchandiseInfoByName(const std::string& name);
    //ͨ��ID��ѯĳ����Ʒ����Ϣ
    int searchSpecifiedMerchandiseInfoByID(int id);

    //�жϸ����ڴ��л����������Ʒ����
    void updateTemporaryMerchandiseInfo();

    //�޸���Ʒ��Ϣ
    void changeMerchandiseInfo(int num, std::string buyer,int id);

    //��ȡ��Ʒ��Ϣ�����ݸ���ң�ͨ��conversion����
    void getMerchandiseInfoForBuyer(std::vector<std::vector<std::string>>& merchandise,std::vector<int>&maxColLen);

    //��ҹ���ָ����Ʒ
    bool purchaseSpecifiedMerchandise_Buyer(int merchandiseID, int merchandiseNum,const std::string &buyerName);

    //��ӽ�����Ϣ
    void addTradeInfo(const std::string& buyerName, int merchandiseId, std::string merchandiseName, int purchaseQuantity, int price);

    //�жϸ����ڴ��л�������н�����Ϣ
    void updateTemporaryTradeInfo();

    //��ʾ���н�����Ϣ
    void showAllTradeInfo();

    //ѡ���ܽ���
    void optionWindow();
    //����ϵͳѭ��
    void play();
private:
    std::string m_merchandiseFilePath;//�洢��Ʒ��Ϣ���ļ�·��
    std::string m_employeeFilePath;//�洢Ա����Ϣ���ļ�·��
    std::string m_tradeInfoFilePath;//�洢������Ϣ���ļ�·��
    
    std::vector<std::vector<std::string>>m_merchandiseInfo;//�����洢��Ʒ��Ϣ���������ļ�δ�޸�Ƶ����ȡ�ļ����ҿ��Ż���Ϣ��ʾ�����ж�����ַ���
    std::vector<int>m_maxInfoLen;//ÿ����Ʒ��Ϣ�е���󳤶�
    std::filesystem::file_time_type m_lastModifyTime;//�洢��һ���޸�ʱ�䣬��������ʾ������Ʒ��Ϣʱ�ж��ļ��Ƿ��޸Ĺ������޸Ĺ��������¶�ȡ��merchandiseInfo
    std::vector<std::string>m_colHeadName;//ÿ����Ʒ��Ϣ�ı�ͷ

    bool m_isQuit;//�Ƿ��˳���ǰϵͳ

    std::vector<std::vector<std::string>>m_tradeInfo;//������ʱ�洢������Ϣ������Ƶ����ȡ�ļ�
    std::filesystem::file_time_type m_tradeInfoFileLastModifyTime;//�洢��һ�δ򿪽�����Ϣ���ļ���ʱ��
    std::vector<std::string>m_tradeInfoColHeadName;//ÿ�н�����Ϣ�ı�ͷ
    std::vector<int>m_tradeInfoColMaxLen;//ÿ�н�����Ϣ����ͷ����󳤶�
};

