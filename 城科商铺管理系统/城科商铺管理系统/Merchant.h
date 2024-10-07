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
    //添加商品
    void addMerchandise();

    //查看各种商品的销售情况
    void showSalesPerformance();

    //显示各种产品的库存情况
    void showInventory();

    //显示收入统计信息
    void showIncome();
    //添加员工
    void addEmployee();

    //查询某个商品的信息
    void findSpecifiedMerchandiseInfo();
    //通过名字查询某个商品的信息
    int searchSpecifiedMerchandiseInfoByName(const std::string& name);
    //通过ID查询某个商品的信息
    int searchSpecifiedMerchandiseInfoByID(int id);

    //判断更新内存中缓存的所有商品数据
    void updateTemporaryMerchandiseInfo();

    //修改商品信息
    void changeMerchandiseInfo(int num, std::string buyer,int id);

    //获取商品信息并传递给买家，通过conversion传递
    void getMerchandiseInfoForBuyer(std::vector<std::vector<std::string>>& merchandise,std::vector<int>&maxColLen);

    //买家购买指定商品
    bool purchaseSpecifiedMerchandise_Buyer(int merchandiseID, int merchandiseNum,const std::string &buyerName);

    //添加交易信息
    void addTradeInfo(const std::string& buyerName, int merchandiseId, std::string merchandiseName, int purchaseQuantity, int price);

    //判断更新内存中缓存的所有交易信息
    void updateTemporaryTradeInfo();

    //显示所有交易信息
    void showAllTradeInfo();

    //选择功能界面
    void optionWindow();
    //商人系统循环
    void play();
private:
    std::string m_merchandiseFilePath;//存储商品信息的文件路径
    std::string m_employeeFilePath;//存储员工信息的文件路径
    std::string m_tradeInfoFilePath;//存储交易信息的文件路径
    
    std::vector<std::vector<std::string>>m_merchandiseInfo;//用来存储商品信息，避免在文件未修改频繁读取文件，且可优化信息显示，即判断最长的字符串
    std::vector<int>m_maxInfoLen;//每列商品信息中的最大长度
    std::filesystem::file_time_type m_lastModifyTime;//存储上一次修改时间，用来在显示所有商品信息时判断文件是否修改过，若修改过则需重新读取进merchandiseInfo
    std::vector<std::string>m_colHeadName;//每列商品信息的标头

    bool m_isQuit;//是否退出当前系统

    std::vector<std::vector<std::string>>m_tradeInfo;//用来暂时存储交易信息，避免频繁读取文件
    std::filesystem::file_time_type m_tradeInfoFileLastModifyTime;//存储上一次打开交易信息的文件的时间
    std::vector<std::string>m_tradeInfoColHeadName;//每列交易信息的标头
    std::vector<int>m_tradeInfoColMaxLen;//每列交易信息含标头的最大长度
};

