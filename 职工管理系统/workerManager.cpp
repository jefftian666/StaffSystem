#include"workerManager.h"

//WorkerManager���캯��
WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1 �ļ������ڵ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		this->m_empNum = 0;
		this->m_empArray = NULL;
		this->m_fileIsEmpty = true;
		ifs.close();
		return;
	}
	//2 �ļ����ڣ�������Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->m_empNum = 0;
		this->m_empArray = NULL;
		this->m_fileIsEmpty = true;
		ifs.close();
		return;
	}
	//3 �ļ����ڣ������ݲ�Ϊ��
	//��ʾ�ļ��е�Ա������
	int num = this->getEmpNum();
	cout << "��ǰ�ļ��е�Ա������Ϊ" << num << endl;
	this->m_empNum = num;
	this->m_empArray = new Worker * [this->m_empNum];//����Ա����������Ա������
	this->initEmpArray();
	//���Ա�������е�����
	for (int i = 0; i < this->m_empNum; i++)
	{
		cout << this->m_empArray[i]->m_id << " " << this->m_empArray[i]->m_name << " " << this->m_empArray[i]->m_deptId << endl;
	}
}
//WorkerManager��������
WorkerManager::~WorkerManager()
{
	if (this->m_empArray != NULL)
	{
		delete[] this->m_empArray;
		this->m_empArray = NULL;
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
				newSpace[i] = this->m_empArray[i];
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
		delete[] this->m_empArray;
		//����ָ��ָ��
		this->m_empArray = newSpace;
		//�����µĸ���
		this->m_empNum = newEmpNum;
		//��ְ����Ϣ���浽�ļ�
		this->save();
		//����ְ��Ϊ�ձ�־
		this->m_fileIsEmpty = false;
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
//�����ļ�
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
//����ļ��е�Ա������
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
//���ļ��е�Ա�����ݶ���Ա������
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
//��ʾ����Ա����Ϣ
void WorkerManager::showEmp()
{
	if (this->m_fileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
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