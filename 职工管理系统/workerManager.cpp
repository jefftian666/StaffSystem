#include"workerManager.h"

//WorkerManager���캯��
WorkerManager::WorkerManager()
{
	this->m_empNum = 0;
	this->m_enmArray = NULL;
}
//WorkerManager��������
WorkerManager::~WorkerManager()
{
	if (this->m_enmArray != NULL)
	{
		delete[] this->m_enmArray;
		this->m_enmArray = NULL;
	}
}
//չʾ�˵�����
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
//�˳�ϵͳ
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ�á�" << endl;
	system("pause");
	exit(0);//�����ںεأ���������
}
//����Ա��
void WorkerManager::addEmp()
{
	cout << "���������ӵ�����" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//����Ա�����Ա������
		int newEmpNum = this->m_empNum + addNum;
		//Ϊ����Ա���������Ա�����ٿռ�
		Worker** newSpace = new Worker * [newEmpNum];
		//���ԭ����������Ϊ0,��ԭԱ�������¿ռ�
		if (this->m_empNum != 0)
		{
			for (int i = 0; i < this->m_empNum;i++)
			{
				newSpace[i] = this->m_enmArray[i];
			}
		}
		//�������ӵ�Ա�������¿ռ�
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "�������" <<i+1<<"��Ա���ı�ţ�"<< endl;
			cin >> id;
			cout << "�������" << i + 1 << "��Ա����������" << endl;
			cin >> name;
			cout << "�������" << i + 1 << "��Ա���ĸ�λ��" << endl;
			cout << "1��Ա��   2������   3���ϰ�  " << endl;
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
		//�ͷ�ԭ����ռ�
		delete[] this->m_enmArray;
		//����ָ��ָ��
		this->m_enmArray = newSpace;
		//�����µĸ���
		this->m_empNum = newEmpNum;
		//��ʾ��Ϣ
		cout << "�ɹ����"<<addNum<<"��Ա��" << endl;
	}	
	else
	{
		cout << "�����������������0������" << endl;
	}
	system("pause");
	system("cls");
}