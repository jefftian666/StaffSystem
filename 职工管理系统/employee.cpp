//��ͨԱ���� Դ�ļ�
#include "employee.h"

//���캯��
Employee::Employee(int id, string name, int deptId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptId = deptId;
}
//��ʾ������Ϣ
void Employee::showInfo()
{
	cout << "ְ����ţ�" << this->m_id 
		<< "\tְ��������" << this->m_name 
		<< "\t��λ��" << this->getDeptName() 
		<<"\t��λְ����ɾ�����������"
		<< endl;
}
//��ȡְ����λ����
string Employee::getDeptName()
{
	return string("Ա��");//����string����ǿת�����ص���const*�����������Զ�ǿת��
}