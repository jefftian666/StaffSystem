#pragma once //防止头文件重复包含
#include<iostream>
using namespace std;

class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();
	//展示菜单
	void Show_Menu();
	void ExitSystem();
};
