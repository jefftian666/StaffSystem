//普通员工类 源文件
#include "employee.h"

//构造函数
Employee::Employee(int id, string name, int deptId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptId = deptId;
}
//显示个人信息
void Employee::showInfo()
{
	cout << "职工编号：" << this->m_id 
		<< "\t职工姓名：" << this->m_name 
		<< "\t岗位：" << this->getDeptName() 
		<<"\t岗位职责：完成经理交给的任务。"
		<< endl;
}
//获取职工岗位名称
string Employee::getDeptName()
{
	return string("员工");//不加string（）强转，返回的是const*，编译器会自动强转。
}