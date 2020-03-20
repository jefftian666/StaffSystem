#pragma once //防止头文件重复包含
#include<iostream>
using namespace std;
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();
	//展示菜单
	void Show_Menu();
	//退出系统
	void ExitSystem();
	//增加员工
	void addEmp();


	//当前的员工数量
	int m_empNum;
	//员工数组，每个员工是一个指针，用二级指针表示
	Worker** m_enmArray;

};
