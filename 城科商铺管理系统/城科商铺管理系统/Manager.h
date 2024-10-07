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
    //显示商户注册申请
    void showAllAppliedMerchant();

    //判断更新缓存的用户注册申请信息
    void updateTemporaryMerchantApplicationInfo();

    //批准商户请求
    void acceptMerchantApplication();

    //批准所有商户注册请求
    void acceptAllMerchantApplication();

    //寻找判断是否有指定名字的商户注册申请，若无则返回-1，有返回其在缓存中的下标
    int findSpecifiedMerchantApplication(const std::string& name);

    //选择界面
    void optionWindow();

    //主循环
    void play();

    //备份所有数据文件
    void copyAllDataFile();

    //数据恢复-指将备份的数据恢复到当前系统，也可组合做为数据迁移的工具
    void recoverData();

    //系统初始化
    void initSystem();

    //查看系统当前所有商户
    void showAllMerchant();

    //注销指定商户的账号
    void deleteSpecifiedMerchantAccount();

    //注销指定买家的账号
    void deleteSpecifiedBuyerAccount();

    //注销指定账号
    bool deleteSpecifiedAccount(const char*filePath,std::string account);

    //显示某种用户信息
    void showUserInfo(const char*filePath);

    //显示所有买家账号信息
    void showAllBuyer();
   
private:
    std::vector<std::vector<std::string>>m_merchantApplicationInfo;//商户注册申请信息
    std::vector<std::string>m_m_merchantApplicationInfoColHeadName;//标头名
    std::vector<int>m_merchantApplicationInfoColMaxLen;//每列文本最大字符数
    std::filesystem::file_time_type m_merchantApplicationInfoFileLastModifyTime;//存储上一次打开交易信息的文件的时间
    bool m_isQuit;
};
/*
 // Edit your code here
    //dp[i][j][k]表示前i个能力不超过j金币和k攻击速度下的最大能力值
    //能不能选第i
    //S[i]-k>0||C[i]-j>0
    //dp[i][j][k]=dp[i-1][j][k];
    //
    //选不选当前第i个商品
    //不选-dp[i][j][k]=dp[i-1][j][k];
    //选-dp[i][j][k]=dp[i-1][j-C[i]][k-S[i]]+D[i];
    //初始化
    //dp[0][0][0]=0;dp[0][j][k]=0,dp[i][0][k]=0,dp[i][j][0]=0;
    //循环顺序
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
