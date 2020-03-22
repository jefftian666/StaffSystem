#include"workerManager.h"

//WorkerManager构造函数
WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1 文件不存在的情况
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		this->m_empNum = 0;
		this->m_empArray = NULL;
		this->m_fileIsEmpty = true;
		ifs.close();
		return;
	}
	//2 文件存在，但内容为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->m_empNum = 0;
		this->m_empArray = NULL;
		this->m_fileIsEmpty = true;
		ifs.close();
		return;
	}
	//3 文件存在，且内容不为空
	//显示文件中的员工个数
	int num = this->getEmpNum();
	cout << "当前文件中的员工个数为" << num << endl;
	this->m_empNum = num;
	this->m_empArray = new Worker * [this->m_empNum];//根据员工数量创建员工数组
	this->initEmpArray();
	//输出员工数组中的内容
	for (int i = 0; i < this->m_empNum; i++)
	{
		cout << this->m_empArray[i]->m_id << " " << this->m_empArray[i]->m_name << " " << this->m_empArray[i]->m_deptId << endl;
	}
}
//WorkerManager析构函数
WorkerManager::~WorkerManager()
{
	if (this->m_empArray != NULL)
	{
		delete[] this->m_empArray;
		this->m_empArray = NULL;
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
				newSpace[i] = this->m_empArray[i];
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
		delete[] this->m_empArray;
		//更改指针指向
		this->m_empArray = newSpace;
		//更新新的个数
		this->m_empNum = newEmpNum;
		//将职工信息保存到文件
		this->save();
		//更新职工为空标志
		this->m_fileIsEmpty = false;
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
//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_empNum; i++)
	{
		ofs << this->m_empArray[i]->m_id << " "
			<< this->m_empArray[i]->m_name << " "
			<< this->m_empArray[i]->m_deptId << endl;
	}
	ofs.close();
}
//获得文件中的员工个数
int WorkerManager::getEmpNum()
{
	int id;
	string name;
	int dId;
	int num=0;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	while (ifs >> id&&ifs >> name&& ifs >> dId)
	{
		num++;
	}
	ifs.close();
	return num;
	
}
//将文件中的员工数据读入员工数组
void WorkerManager::initEmpArray()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	Worker* worker = NULL;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if(dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else
		{
			worker = new Boss(id, name, dId);
		}
		this->m_empArray[index] = worker;
		index++;
	}
	ifs.close();
}
//显示所有员工信息
void WorkerManager::showEmp()
{
	if (this->m_fileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_empNum; i++)
		{
			this->m_empArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}