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


	//��ǰ��Ա������
	int m_empNum;
	//Ա�����飬ÿ��Ա����һ��ָ�룬�ö���ָ���ʾ
	Worker** m_empArray;
	//�ж��ļ��Ƿ�Ϊ��
	bool m_fileIsEmpty;
	//����ļ��е�Ա������
	int getEmpNum();
	//��ʼ��Ա������
	void initEmpArray();

};
