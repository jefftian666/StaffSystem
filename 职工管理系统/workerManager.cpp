//ְ������ϵͳ�� Դ�ļ�
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
//ɾ��ְ��
void WorkerManager::delEmp()
{
	if (this->m_fileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����ְ���ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->isExist(id);
		if (ret == -1)
		{
			cout << "ɾ��ʧ�ܣ�ְ��������" << endl;
		}
		else
		{
			//ְ�����ڣ�������ǰ��
			for (int i = ret; i < m_empNum - 1; i++)
			{
				this->m_empArray[i] = this->m_empArray[i + 1];
			}
			this->m_empNum--;
			this->save();//���浽�ļ���
			cout << "ɾ���ɹ�" << endl;
		}
	}
	system("pause");
	system("cls");
}
//����ְ������ж�ְ���Ƿ����,�����ڷ���ְ����������λ�ã������ڷ���-1
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
//�޸�ְ����Ϣ
void WorkerManager::modEmp()
{
	if (this->m_fileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->isExist(id);
		if (ret == -1)
		{
			cout << "���޴���" << endl;
		}
		else
		{
			delete this->m_empArray[ret];
			int newId = 0;
			string newName = "";
			int newDeptSelect = 0;
			cout <<"�鵽"<<id<<"��Ա��,"<< "�������µ�id��" << endl;
			cin >> newId;
			cout << "�������µ����֣�" << endl;
			cin >> newName;
			cout << "��ѡ���µĸ�λ��1 ��ͨԱ�� 2 ���� 3 �ϰ�" << endl;
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
			cout << "�޸ĳɹ�" << endl;

		}
	}
	system("pause");
	system("cls");
}
//����ְ��
void  WorkerManager::findEmp()
{
	if (this->m_fileIsEmpty)
	{
		cout << "�ļ�Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ��1 ��id 2 ������" << endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			cout << "������Ҫ����Ա����id��" << endl;
			int id = 0;
			cin >> id;
			int ret = this->isExist(id);
			if (ret == -1)//��id����
			{
				//������
				cout << "���޴���" << endl;
			}
			else
			{
				cout << ret << "��ְ����Ϣ���£�" << endl;
				this->m_empArray[ret]->showInfo();
			}
		}
		else if (choice == 2)//����������
		{
			string name = "";
			cout << "������Ҫ����Ա����������" << endl;
			cin >> name;
			bool falg = false;
			for (int i = 0; i < this->m_empNum; i++)
			{
				if (this->m_empArray[i]->m_name == name)
				{
					cout << "����Ϊ" << name << "��ְ����ϢΪ�£�" << endl;
					this->m_empArray[i]->showInfo();
					falg = true;
					break;
				}
			}
			if (!falg)
			{
				cout << "���޴���" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}
//ѡ������
void WorkerManager::sortEmpArray()
{
	if (this->m_fileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "����������ʽ��1 ���� 2 ����" << endl;
		int select = 1;
		cin >> select;
		for (int i = 0; i < this->m_empNum; i++)
		{
			int MinOrMax = i;
			for (int j = i + 1; j < this->m_empNum; j++)
			{
				if (select == 1)//����
				{
					if (this->m_empArray[MinOrMax]->m_id > this->m_empArray[j]->m_id)
					{
						MinOrMax = j;//����Сֵ���±�
					}
				}
				else//����
				{
					if (this->m_empArray[MinOrMax]->m_id < this->m_empArray[j]->m_id)
					{
						MinOrMax = j;//�����ֵ���±�
					}
				}

			}
			if (i != MinOrMax)//�����±�󣬺�ǰ�߽���λ��
			{
				Worker* temp = this->m_empArray[i];
				this->m_empArray[i] = this->m_empArray[MinOrMax];
				this->m_empArray[MinOrMax] = temp;
			}

		}
		this->showEmp();
		this->save();
		cout << "����ɹ�" << endl;
	}
}
//����ļ�
void WorkerManager::cleanFile()
{
	cout << "����ļ���" << endl;
	cout << "1 �� 2 ��" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);//��ģʽ ios::trunc �������ɾ���ļ������´���
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
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}