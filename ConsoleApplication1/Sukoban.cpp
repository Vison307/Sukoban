
// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// version: 0.0.1beta
// author: Vison
// date: 2019.11.29

#include <iostream>
#include "gamemap.h"
#include "game.h"
class UI {
public:
	UI() {};
	~UI() {};
	void Show(void);
	void Control(void);
};
void UI::Show(void) {
	std::cout << "欢迎来到推推乐游戏v0.0.1" << std::endl;
	std::cout << "1. 闯关模式（传统推箱子地图）" << std::endl;
	std::cout << "2. 休闲模式（一箱子随机地图模式）" << std::endl;
	std::cout << "请选择游戏模式（输入0退出）:";
}
void UI::Control(void) {
	int c;
	std::cin >> c;
	switch (c) {
		case 1: {
			int i = 1;
			for (i = 1; i <= 5; i++) {
				int cont = 1;
				Normal_Game game(i);
				game.Play();
				std::cout << "继续玩吗？输入0退出" << std::endl;
				std::cin >> cont;
				if (cont == 0)	break;
			}
			if(i > 5)	std::cout << "您通关了！" << std::endl;
			std::cout << "感谢您的使用！" << std::endl;
			break;
		}
		case 2: {
			int cont = 1;
			while (cont) {
				Random_Game game;
				game.Play();
				std::cout << "继续玩吗？输入0退出" << std::endl;
				std::cin >> cont;
			}
			std::cout << "感谢您的使用！" << std::endl;
			break;
		}
		case 0: {
			std::cout << "感谢您的使用！" << std::endl;
			break;
		}
	}
	return;
}
int main()
{
	UI ui;
	ui.Show();
	ui.Control();
	system("pause");
}
