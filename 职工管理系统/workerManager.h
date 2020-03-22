#pragma once //防止头文件重复包含
#include<iostream>
using namespace std;
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#define	FILENAME "empFile.txt"

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
	//保存文件
	void save();
	//获得文件中的员工个数
	int getEmpNum();
	//初始化员工数组
	void initEmpArray();
	//显示所有员工信息
	void showEmp();
	//删除职工
	void delEmp();
	//按照职工编号判断职工是否存在,若存在返回职工在数组中位置，不存在返回-1
	int isExist(int id);
	//修改职工信息
	void modEmp();


	//当前的员工数量
	int m_empNum;
	//员工数组，每个员工是一个指针，用二级指针表示
	Worker** m_empArray;
	//判断文件是否为空
	bool m_fileIsEmpty;


};
