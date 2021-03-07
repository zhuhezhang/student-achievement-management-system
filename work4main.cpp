/*成绩管理系统
信息描述：
现有学生成绩信息，内容如下
姓名    学号   语文  数学   英语    
张明明   01     67    78     82
李成友   02     78    91     88
张辉灿   03     68    82     56
王露     04     56    45     77
陈东明   05     67    38     47
...      ..     ..    ..     .. 
请编写一实现学生信息管理系统，用C++及类和对象来进行抽象、封装与实现，
注意学生的成绩需要用链表来实现，并且链表也需要实现封装，包含以下功能：
1)信息维护：
  a)学生信息数据要以文件的形式保存，能实现学生信息数据的维护
  b)此模块包括子模块有：增加学生信息、删除学生信息、修改学生信息
  c)在程序中能够以链表的形式从文件中读入数据
2)信息查询：
  查询时可实现按姓名查询、按学号查询
3)成绩统计：
  a)输入任意的一个课程名（如数学）给出该门课程的成绩的分段统计（以10分为一个
    成绩段，如90-100，80-89，70-79，60-69，小于60），给出在此分数段的学生数目
  b)根据指定的课程名求该门课所有学生的平均成绩
  c)给出每个学生的平均成绩
4)排序：
  能对指定的任意课程名，按成绩升序或降序排列学生数据并显示排序结果
5)采用文本菜单界面*/
 
#include<iostream>
#include<fstream> 
#include<cstring>
#include "work4class.h"
using namespace std;

//主函数部分
int main()
{
	Student_information si;//创建类对象，并调用其构造函数					     
	//把C++work4.txt中的学生信息数据读到内存中
	int choice1;
	while(1)
	{
		si.show_menu();//显示菜单 
		cin>>choice1;
		system("cls");//这将清除运行的任何文本的屏幕
		switch(choice1)
		{
			case 1:si.add();    break;//添加 
			case 2:si.del();    break;//删除 
			case 3:si.modify(); break;//修改 
			case 4:si.display();break;//显示 
			case 5:si.find();   break;//查询 
			case 6:si.count();  break;//统计 
			case 7:si.sort();   break;//排序
			case 8:si.clean();  break;//清除 
			case 0:return 0;    break;
			default :cout<<"\n无效指令!\n\n\n";
		}
		system("pause");//这将要求“按任意键....”关闭窗口
		system("cls");  //这将清除运行的任何文本的屏幕
	}
	return 0;
}
