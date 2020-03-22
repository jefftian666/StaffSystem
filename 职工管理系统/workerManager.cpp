//职工管理系统类 源文件
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
//删除职工
void WorkerManager::delEmp()
{
	if (this->m_fileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入想要删除的职工号：" << endl;
		int id;
		cin >> id;
		int ret = this->isExist(id);
		if (ret == -1)
		{
			cout << "删除失败，职工不存在" << endl;
		}
		else
		{
			//职工存在，做数据前移
			for (int i = ret; i < m_empNum - 1; i++)
			{
				this->m_empArray[i] = this->m_empArray[i + 1];
			}
			this->m_empNum--;
			this->save();//保存到文件中
			cout << "删除成功" << endl;
		}
	}
	system("pause");
	system("cls");
}
//按照职工编号判断职工是否存在,若存在返回职工在数组中位置，不存在返回-1
int WorkerManager::isExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_empNum; i++)
	{
		if (this->m_empArray[i]->m_id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}
//修改职工信息
void WorkerManager::modEmp()
{
	if (this->m_fileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;
		int ret = this->isExist(id);
		if (ret == -1)
		{
			cout << "查无此人" << endl;
		}
		else
		{
			delete this->m_empArray[ret];
			int newId = 0;
			string newName = "";
			int newDeptSelect = 0;
			cout <<"查到"<<id<<"号员工,"<< "请输入新的id：" << endl;
			cin >> newId;
			cout << "请输入新的名字：" << endl;
			cin >> newName;
			cout << "请选择新的岗位：1 普通员工 2 经理 3 老板" << endl;
			cin >> newDeptSelect;
			Worker* worker = NULL;
			switch (newDeptSelect)
			{
			case 1:
				worker = new Employee(newId, newName, newDeptSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, newDeptSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, newDeptSelect);
				break;
			default:
				break;
			}
			this->m_empArray[ret] = worker;
			this->save();
			cout << "修改成功" << endl;

		}
	}
	system("pause");
	system("cls");
}
//查找职工
void  WorkerManager::findEmp()
{
	if (this->m_fileIsEmpty)
	{
		cout << "文件为空" << endl;
	}
	else
	{
		cout << "请输入查找方式：1 按id 2 按姓名" << endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			cout << "请输入要查找员工的id：" << endl;
			int id = 0;
			cin >> id;
			int ret = this->isExist(id);
			if (ret == -1)//按id查找
			{
				//不存在
				cout << "查无此人" << endl;
			}
			else
			{
				cout << ret << "号职工信息如下：" << endl;
				this->m_empArray[ret]->showInfo();
			}
		}
		else if (choice == 2)//按姓名查找
		{
			string name = "";
			cout << "请输入要查找员工的姓名：" << endl;
			cin >> name;
			bool falg = false;
			for (int i = 0; i < this->m_empNum; i++)
			{
				if (this->m_empArray[i]->m_name == name)
				{
					cout << "姓名为" << name << "的职工信息为下：" << endl;
					this->m_empArray[i]->showInfo();
					falg = true;
					break;
				}
			}
			if (!falg)
			{
				cout << "查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}
//选择排序
void WorkerManager::sortEmpArray()
{
	if (this->m_fileIsEmpty)
	{
		cout << "文件为空或不存在" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请输入排序方式：1 升序 2 降序" << endl;
		int select = 1;
		cin >> select;
		for (int i = 0; i < this->m_empNum; i++)
		{
			int MinOrMax = i;
			for (int j = i + 1; j < this->m_empNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_empArray[MinOrMax]->m_id > this->m_empArray[j]->m_id)
					{
						MinOrMax = j;//找最小值的下标
					}
				}
				else//降序
				{
					if (this->m_empArray[MinOrMax]->m_id < this->m_empArray[j]->m_id)
					{
						MinOrMax = j;//找最大值的下标
					}
				}

			}
			if (i != MinOrMax)//找完下标后，和前边交换位置
			{
				Worker* temp = this->m_empArray[i];
				this->m_empArray[i] = this->m_empArray[MinOrMax];
				this->m_empArray[MinOrMax] = temp;
			}

		}
		this->showEmp();
		this->save();
		cout << "排序成功" << endl;
	}
}
//清空文件
void WorkerManager::cleanFile()
{
	cout << "清空文件？" << endl;
	cout << "1 是 2 否" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofs.close();
		if (this->m_empArray != NULL)
		{
			for (int i = 0; i < this->m_empNum; i++)
			{
				delete this->m_empArray[i];

			}
			delete[] this->m_empArray;
			this->m_empArray = NULL;
			this->m_empNum = 0;
			this->m_fileIsEmpty = true;
		}
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}