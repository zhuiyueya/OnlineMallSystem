#include "InitialWindow.h"

void InitialWindow::draw()
{
	std::cout << "��ӭ�����ǿ����̹���ϵͳ��\n";
	std::cout << "��ѡ����ִ�еĹ��ܣ�\n";

	std::cout << "1.��¼\n";
	std::cout << "2.ע��\n";
	std::cout << "3.�˳�\n";
}

int InitialWindow::getInputFunction()
{
againIW:
	int op = 0;
	std::cin >> op;
	if (op >= IW_OPTION_MAX || op <= IW_OPTION_MIN) {
		system("clear");
		draw();
		std::cout << "��������ȷ��ѡ�����:";
		goto againIW;
	}

	return op;

}
