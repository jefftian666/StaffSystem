#pragma once //��ֹͷ�ļ��ظ�����
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
	//չʾ�˵�
	void Show_Menu();
	//�˳�ϵͳ
	void ExitSystem();
	//����Ա��
	void addEmp();
	//�����ļ�
	void save();
	//����ļ��е�Ա������
	int getEmpNum();
	//��ʼ��Ա������
	void initEmpArray();
	//��ʾ����Ա����Ϣ
	void showEmp();
	//ɾ��ְ��
	void delEmp();
	//����ְ������ж�ְ���Ƿ����,�����ڷ���ְ����������λ�ã������ڷ���-1
	int isExist(int id);
	//�޸�ְ����Ϣ
	void modEmp();


	//��ǰ��Ա������
	int m_empNum;
	//Ա�����飬ÿ��Ա����һ��ָ�룬�ö���ָ���ʾ
	Worker** m_empArray;
	//�ж��ļ��Ƿ�Ϊ��
	bool m_fileIsEmpty;


};
