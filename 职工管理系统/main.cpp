#include<iostream>
#include"workerManager.h"
using namespace std;


int main()
{
	//test();
	//system("pause");
	//exit(0);
	WorkerManager wm;
	int select = 0;
	while (true)
	{
		wm.Show_Menu();//展示菜单
		cout << "请输入选择" << endl;
		cin >> select;
		if (cin.fail()) //若流操作失败，则返回true
		{
			cout << "请输入整数" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			system("pause");
			system("cls");
		}
		else
		{
			switch (select)
			{
			case 0: //退出系统
				wm.ExitSystem();
				break;
			case 1: //添加职工
				wm.addEmp();
				break;
			case 2: //显示职工
				wm.showEmp();
				break;
			case 3: //删除职工
				wm.delEmp();
				break;
			case 4: //修改职工
				wm.modEmp();
				break;
			case 5: //查找职工
				break;
			case 6: //排序职工
				break;
			case 7: //清空文件
				break;
			default:
				cout << "请输入0-7" << endl;
				system("pause");
				system("cls");
				break;
			}
		}
		
		
	}




	system("pause");
	return 0;
}