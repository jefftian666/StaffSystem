#include"workerManager.h"

//WorkerManager构造函数
WorkerManager::WorkerManager()
{
	this->m_empNum = 0;
	this->m_enmArray = NULL;
}
//WorkerManager析构函数
WorkerManager::~WorkerManager()
{
	if (this->m_enmArray != NULL)
	{
		delete[] this->m_enmArray;
		this->m_enmArray = NULL;
	}
}
//展示菜单函数
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用。" << endl;
	system("pause");
	exit(0);//不论在何地，结束程序
}
//增加员工
void WorkerManager::addEmp()
{
	cout << "请输入增加的数量" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//增加员工后的员工数量
		int newEmpNum = this->m_empNum + addNum;
		//为增加员工后的所有员工开辟空间
		Worker** newSpace = new Worker * [newEmpNum];
		//如果原来的人数不为0,把原员工放入新空间
		if (this->m_empNum != 0)
		{
			for (int i = 0; i < this->m_empNum;i++)
			{
				newSpace[i] = this->m_enmArray[i];
			}
		}
		//把新增加的员工放入新空间
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "请输入第" <<i+1<<"个员工的编号："<< endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个员工的姓名：" << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "个员工的岗位：" << endl;
			cout << "1、员工   2、经理   3、老板  " << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name,1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_empNum + i] = worker;
		}
		//释放原数组空间
		delete[] this->m_enmArray;
		//更改指针指向
		this->m_enmArray = newSpace;
		//更新新的个数
		this->m_empNum = newEmpNum;
		//提示信息
		cout << "成功添加"<<addNum<<"个员工" << endl;
	}	
	else
	{
		cout << "输入有误，请输入大于0的数。" << endl;
	}
	system("pause");
	system("cls");
}