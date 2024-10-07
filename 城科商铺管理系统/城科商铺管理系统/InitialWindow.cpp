#include "InitialWindow.h"

void InitialWindow::draw()
{
	std::cout << "欢迎来到城科商铺管理系统！\n";
	std::cout << "请选择您执行的功能：\n";

	std::cout << "1.登录\n";
	std::cout << "2.注册\n";
	std::cout << "3.退出\n";
}

int InitialWindow::getInputFunction()
{
againIW:
	int op = 0;
	std::cin >> op;
	if (op >= IW_OPTION_MAX || op <= IW_OPTION_MIN) {
		system("clear");
		draw();
		std::cout << "请输入正确的选项序号:";
		goto againIW;
	}

	return op;

}
