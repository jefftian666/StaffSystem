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
		wm.Show_Menu();//չʾ�˵�
		cout << "������ѡ��" << endl;
		cin >> select;
		if (cin.fail()) //��������ʧ�ܣ��򷵻�true
		{
			cout << "����������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			system("pause");
			system("cls");
		}
		else
		{
			switch (select)
			{
			case 0: //�˳�ϵͳ
				wm.ExitSystem();
				break;
			case 1: //���ְ��
				wm.addEmp();
				break;
			case 2: //��ʾְ��
				wm.showEmp();
				break;
			case 3: //ɾ��ְ��
				wm.delEmp();
				break;
			case 4: //�޸�ְ��
				wm.modEmp();
				break;
			case 5: //����ְ��
				break;
			case 6: //����ְ��
				break;
			case 7: //����ļ�
				break;
			default:
				cout << "������0-7" << endl;
				system("pause");
				system("cls");
				break;
			}
		}
		
		
	}




	system("pause");
	return 0;
}