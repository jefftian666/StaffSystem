#pragma once
#include<iostream>
#include<string>
#include"worker.h"
using namespace std;

class Manager :public Worker
{
public:
	//���캯��
	Manager(int id, string name, int deptId);
	//��ʾ������Ϣ
	virtual void showInfo() ;
	//��ȡ��λ����
	virtual string getDeptName() ;
};