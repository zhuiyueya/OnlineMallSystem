#pragma once
#include "User.h"
//#include<string>
#include<vector>
#include<filesystem>
class Manager :
    public User
{
public:
    Manager(const std::string &account,const std::string &pwd);
    //��ʾ�̻�ע������
    void showAllAppliedMerchant();

    //�жϸ��»�����û�ע��������Ϣ
    void updateTemporaryMerchantApplicationInfo();

    //��׼�̻�����
    void acceptMerchantApplication();

    //��׼�����̻�ע������
    void acceptAllMerchantApplication();

    //Ѱ���ж��Ƿ���ָ�����ֵ��̻�ע�����룬�����򷵻�-1���з������ڻ����е��±�
    int findSpecifiedMerchantApplication(const std::string& name);

    //ѡ�����
    void optionWindow();

    //��ѭ��
    void play();

    //�������������ļ�
    void copyAllDataFile();

    //���ݻָ�-ָ�����ݵ����ݻָ�����ǰϵͳ��Ҳ�������Ϊ����Ǩ�ƵĹ���
    void recoverData();

    //ϵͳ��ʼ��
    void initSystem();

    //�鿴ϵͳ��ǰ�����̻�
    void showAllMerchant();

    //ע��ָ���̻����˺�
    void deleteSpecifiedMerchantAccount();

    //ע��ָ����ҵ��˺�
    void deleteSpecifiedBuyerAccount();

    //ע��ָ���˺�
    bool deleteSpecifiedAccount(const char*filePath,std::string account);

    //��ʾĳ���û���Ϣ
    void showUserInfo(const char*filePath);

    //��ʾ��������˺���Ϣ
    void showAllBuyer();
   
private:
    std::vector<std::vector<std::string>>m_merchantApplicationInfo;//�̻�ע��������Ϣ
    std::vector<std::string>m_m_merchantApplicationInfoColHeadName;//��ͷ��
    std::vector<int>m_merchantApplicationInfoColMaxLen;//ÿ���ı�����ַ���
    std::filesystem::file_time_type m_merchantApplicationInfoFileLastModifyTime;//�洢��һ�δ򿪽�����Ϣ���ļ���ʱ��
    bool m_isQuit;
};
/*
 // Edit your code here
    //dp[i][j][k]��ʾǰi������������j��Һ�k�����ٶ��µ��������ֵ
    //�ܲ���ѡ��i
    //S[i]-k>0||C[i]-j>0
    //dp[i][j][k]=dp[i-1][j][k];
    //
    //ѡ��ѡ��ǰ��i����Ʒ
    //��ѡ-dp[i][j][k]=dp[i-1][j][k];
    //ѡ-dp[i][j][k]=dp[i-1][j-C[i]][k-S[i]]+D[i];
    //��ʼ��
    //dp[0][0][0]=0;dp[0][j][k]=0,dp[i][0][k]=0,dp[i][j][0]=0;
    //ѭ��˳��
    //i->j->k
    vector<vector<vector<int>>>dp(n+1,vector<vector<int>>(g+1,vector<int>(s,0)));

    for(int i=1;i<=n;i++){
        for(int j=1;j<=g;j++){
            for(int k=1;k<s;k++){
                dp[]
            }
        }
    }

*/
