//定义类里面的所有函数 
#include<iostream>
#include<fstream>
#include<cstring>
#include "work4class.h"
using namespace std;

//往结点输入学生信息
void Student::input()
{
	cout<<"请输入学生名字：";
	cin>>student_name;
	cout<<"请输入学生学号：";
	cin>>student_ID;
	cout<<"请输入学生语文成绩：";
	cin>>chinese_score;
	cout<<"请输入学生数学成绩：";
	cin>>math_score;
	cout<<"请输入学生英语成绩：";
	cin>>english_score;
	average_score=(chinese_score+math_score+english_score)/3;
}

//从文档中读取值到结点
void Student::readfile(ifstream &in)
{
	in>>student_name>>student_ID>>chinese_score>>math_score>>english_score>>average_score;
}

//这个构造函数可以在打开程序时，就自动加载原有的学生信息
Student_information::Student_information()
{
	//初始化，头尾结点 
	head = new Student;
	head->next = new Student;
	end = head->next; 
	ifstream in("C++work4.txt");
	/*首先要先向文件读一下，才能判断文件是否为空，因为eof()不能用来判断
	文件是否为空，eof()是根据文件的状态标识来判断文件是否为空的，当读取
	文件时，遇到结尾时，系统会改变文件的状态标识，这时候才会返回EOF，才
	能用eof()判断。不先读一下的话，in.eof()是不会返回正值的，即使文件为空*/
	char ch = in.get();
	if(in.eof())
	{
		cout<<"文件为空！"<<endl;
	}
	//若文件非空
	while(!in.eof())
	{
		end->readfile(in);
		if(end->student_name[0]=='\0')
		break;//不加这一句的话程序会把文件最后结束的标记也都出来		
		end->next = new Student;
		end = end->next;
	} 
}

//析构函数
Student_information::~Student_information()
{
	save();//当正常退出程序的时候，保存数据到C++work4.txt中 
	Student *pos = head->next;
	Student *temp;
	while(pos!=end)
	{
		temp = pos;
		pos = pos->next;
		delete temp;
	}
	delete head,end;
}

//增加结点
void Student_information::add()
{
	char quit;
	while(1)
	{
		end->input();
		end->next = new Student;
		end = end->next;
		cout<<"是否继续?(Y/N)"<<endl;
		cin>>quit;
		switch(quit)
		{
			case'Y':
			case'y':break;
			case'n':
			case'N':return;break;
			default:cout<<"错误输入,是否继续输入?(Y/N)";
				cin>>quit;
		}
	}
	cout<<"增加信息成功!"<<endl;
	system("pause");
}

//修改结点
void Student_information::modify()
{
	char name[20];
	cout<<"请输入您想要修改的学生名字：";
	cin>>name;
	Student *pos = head->next;
	for(pos;pos!=end;pos=pos->next)
	{
		if(strcmp(name,pos->student_name)==0)
		{
			pos->input();
			break;
		}	
	}
	cout<<"修改成功!"<<endl;
}

//删除结点
void Student_information::del()
{
	int del_flag = 0;//标记是否删除成功 
	char name[20];
	if(head->next == end)	
	{
	    cout<<"空的..."<<endl;
		   return ;
	}
	cout<<"请输入您想要删除的学生名字：";
	cin>>name;
	Student *p1 = head->next;
	Student *p2 = head;
	for(p1;p1!=end;p1->next)
	{
		if(strcmp(p1->student_name,name)==0)
		{
			del_flag = 1;
			p2->next = p1->next;
			delete p1;
			break;		
		}
		else
		{
		    p2=p2->next;
			p1=p1->next;
		}
	}	
	if(del_flag == 0)
	{
	    cout<<"未能找到该学生...."<<endl;
	}
	cout<<"删除信息成功!"<<endl;
}

//查找学生信息
void Student_information::find()
{
	while(1)
	{
	   char name[20];
	   char ID[10];
	   cout<<"    1、按学号查询\n";
	   cout<<"    2、按姓名查询\n";
	   cout<<"\n请输入指令：";
	   int choice;
       cin>>choice;
 	   while(choice !=1 && choice != 2)
	   {
		   cout<<"错误指令！\n";
		   system("pause");
		   cout<<"请重新输入指令：";
		   cin>>choice;
           continue;//重新执行条件判断
	    }
        system("cls");
	    Student *pos = head->next;
	    int flag(0);//判断是否找到信息 
	    if(choice==1)
     	{
		   cout<<"请输入要查询的学号：";
		   cin>>ID;
	       for(pos;pos!=end;pos=pos->next)
	       {
		       if(strcmp(pos->student_ID,ID)==0)
		       {
			      flag = 1; 
			      cout<<"学生名字:"<<pos->student_name<<endl;
			      cout<<"学生学号:"<<pos->student_ID<<endl;
			      cout<<"语文成绩:"<<pos->chinese_score<<endl;
			      cout<<"数学成绩:"<<pos->math_score<<endl;
			      cout<<"英语成绩:"<<pos->english_score<<endl;
			      cout<<"平均成绩:"<<pos->average_score<<endl;
		       }
	       }
        }
	    if(choice==2)
	    {
		   cout<<"请输入要查询的姓名：";
		   cin>>name;
	       for(pos;pos!=end;pos=pos->next)
	       {
		       if(strcmp(pos->student_name,name)==0)
		       {
			        flag = 1;
			        cout<<"学生名字:"<<pos->student_name<<endl;
			        cout<<"学生学号:"<<pos->student_ID<<endl;
			        cout<<"语文成绩:"<<pos->chinese_score<<endl;
			        cout<<"数学成绩:"<<pos->math_score<<endl;
			        cout<<"英语成绩:"<<pos->english_score<<endl;
			        cout<<"平均成绩:"<<pos->average_score<<endl;
		       }
	       }
        }
        if(!flag)
        {
    	   cout<<"未能找到该学生信息...\n";
	    }
	    char c;
	    cout<<"\n是否继续查询(Y/N)：";
        cin>>c;
        system("cls");
        if(c == 'N' || c == 'n')
           break;
    }
}

//保存学生信息
void Student_information::save()
{
	out.open("C++work4.txt");
	Student *pos = head->next;
	if(head->next== end)
	{
		cout<<"空的..."<<endl;
	}
	else
	{
		for(pos;pos!=end;pos=pos->next)
		{
			out<<'\t'<<pos->student_name<<'\t'<<pos->student_ID<<'\t'<<pos->chinese_score<<'\t'<<pos->math_score<<'\t'<<pos->english_score<<'\t'<<pos->average_score;
			//格式最好这样写,因为一开始会把文件读一下，以判断文件是否为空，所以前面最后用‘\t’
			//来增加几个空格，给他读一个空格，以不读到正常数据，后面就不要有空格
			//因为当程序从C++work4.txt读信息时，可能会把空格也当是一个数据结点读进程序	
		}
	}
	out.close();
	cout<<"保存信息成功!"<<endl;
}

//显示结点
void Student_information::display()
{
	if(head->next==end)
	{
	   cout<<"空的..."<<endl;
	}
	Student *pos;
	pos = head->next;
	for(pos;pos!=end;pos=pos->next)
	{
		cout<<"学生姓名："<<pos->student_name<<endl;
		cout<<"学生学号："<<pos->student_ID<<endl;
		cout<<"语文成绩："<<pos->chinese_score<<endl;
		cout<<"数学成绩："<<pos->math_score<<endl;
		cout<<"英语成绩："<<pos->english_score<<endl;
		cout<<"平均成绩："<<pos->average_score<<endl;
		cout<<endl;
	}
}

//统计函数 
void Student_information::count()
{
	while(1)
	{
		cout<<"1、查看统计的语文分数"<<endl;
	    cout<<"2、查看统计的数学分数"<<endl;
	    cout<<"3、查看统计的英语分数"<<endl;
	    cout<<"\n请输入指令(1-3)：";
	    int choice;
	    cin>>choice;
	    while(choice<1 || choice>3)
	   {
		   cout<<"错误指令！\n";
		   system("pause");
		   cout<<"重新输入指令：";
		   cin>>choice;
           continue;//重新执行条件判断
	    }
	    Student *p = head->next;
	    if(choice==1)
	   {
		  int a(0);
		  int b(0);
		  int c(0);
		  int d(0);
	      int e(0);
	      int total_student(0);
	      int total_chinese_score(0);
		  for(p;p != end;p = p->next)
          { 
             if (90 <= p->chinese_score && p->chinese_score <= 100)
             {
                a++;
             }
             else if (80 <= p->chinese_score && p->chinese_score <= 89)
             {
                b++;
             }
             else if (70 <= p->chinese_score && p->chinese_score <= 79)
             {
                c++;
             }
             else if (60 <= p->chinese_score && p->chinese_score <= 69)
             {
                d++;
             }
             else
             {
                e++;
             }
             total_student++;
	         total_chinese_score = total_chinese_score + p->chinese_score;
	       }
	       cout<<"\n语文平均分："<<total_chinese_score/total_student<<endl;;
	       cout<<"语文分数90-100人数："<<a<<endl;
	       cout<<"语文分数 80-89人数："<<b<<endl;
	       cout<<"语文分数 70-79人数："<<c<<endl;
	       cout<<"语文分数 60-69人数："<<d<<endl;
	       cout<<"语文分数  <60 人数："<<e<<endl;
        }
        if(choice==2)
	   {
		  int a(0);
		  int b(0);
		  int c(0);
		  int d(0);
	      int e(0);
	      int total_student(0);
	      int total_math_score(0);
		  for(p;p != end;p = p->next)
          { 
             if (90 <= p->math_score && p->math_score <= 100)
             {
                a++;
             }
             else if (80 <= p->math_score && p->math_score <= 89)
             {
                b++;
             }
             else if (70 <= p->math_score && p->math_score <= 79)
             {
                c++;
             }
             else if (60 <= p->math_score && p->math_score <= 69)
             {
                d++;
             }
             else
             {
                e++;
             }
             total_student++;
	         total_math_score = total_math_score + p->math_score;
	       }
	       cout<<"\n数学平均分："<<total_math_score/total_student<<endl;;
	       cout<<"数学分数90-100人数为："<<a<<endl;
	       cout<<"数学分数 80-89人数为："<<b<<endl;
	       cout<<"数学分数 70-79人数为："<<c<<endl;
	       cout<<"数学分数 60-69人数为："<<d<<endl;
	       cout<<"数学分数  <60 人数为："<<e<<endl;
       }
       if(choice==3)
	   {
		  int a(0);
		  int b(0);
		  int c(0);
		  int d(0);
	      int e(0);
	      int total_student(0);
	      int total_english_score(0);
		  for(p;p != end;p = p->next)
          { 
             if (90 <= p->english_score && p->english_score <= 100)
             {
                a++;
             }
             else if (80 <= p->english_score && p->english_score <= 89)
             {
                b++;
             }
             else if (70 <= p->english_score && p->english_score <= 79)
             {
                c++;
             }
             else if (60 <= p->english_score && p->english_score <= 69)
             {
                d++;
             }
             else
             {
                e++;
             }
             total_student++;
	         total_english_score = total_english_score + p->english_score;
	       }
	       cout<<"\n英语平均分："<<total_english_score/total_student<<endl;;
	       cout<<"英语分数90-100人数为："<<a<<endl;
	       cout<<"英语分数 80-89人数为："<<b<<endl;
	       cout<<"英语分数 70-79人数为："<<c<<endl;
	       cout<<"英语分数 60-69人数为："<<d<<endl;
	       cout<<"英语分数  <60 人数为："<<e<<endl;
       }
        char c;
	    cout<<"\n是否继续查询(Y/N)：";
        cin>>c;
        system("cls");
        if(c == 'N' || c == 'n')
        break;
	}
}

//把结点p2信息拷贝到p1
void Student_information::copy(Student *p1,Student *p2)
{
	if (p2 == NULL)
    {
        cout <<"拷贝目标为空！"<<endl;
    }
    else
    {
        strcpy(p1->student_name,p2->student_name);
        strcpy(p1->student_ID,p2->student_ID);
        p1->chinese_score = p2->chinese_score;
        p1->math_score = p2->math_score;
        p1->english_score = p2->english_score;
        p1->average_score = p2->average_score;
        //只是信息拷贝,next不能拷贝否则信息丢失
    }
}

//按三科成绩排序
void Student_information::sort()
{
	cout<<"\t\t***********************排序*******************\n";
	cout<<"\t\t*                                            *\n";
    cout<<"\t\t*              1.按语文成绩降序排            *\n";
    cout<<"\t\t*                                            *\n";
    cout<<"\t\t*              2.按语文成绩升序排            *\n";
    cout<<"\t\t*                                            *\n";
    cout<<"\t\t*              3.按数学成绩降序排            *\n";
    cout<<"\t\t*                                            *\n";
    cout<<"\t\t*              4.按数学成绩升序排            *\n";
    cout<<"\t\t*                                            *\n";
    cout<<"\t\t*              5.按英语成绩降序排            *\n";
    cout<<"\t\t*                                            *\n";
    cout<<"\t\t*              6.按英语成绩升序排            *\n";
    cout<<"\t\t*                                            *\n";
    cout<<"\t\t**********************************************\n";
    cout<<"\t\t请输入指令(1-6): ";
	int choice(0);
	cin>>choice;
	while(choice < 1 || choice > 6)
    {
        printf("错误指令！\n\n");
        system("pause");//这将要求“按任意键....”关闭窗口
        continue;       //重新执行条件判断
    }
    Student *p1,*p2;
    p1=head->next;
    if(choice==1)       //按语文成绩降序排
    {
	    for(p1;p1!=end;p1=p1->next)//冒泡排序
	    {
		    for(p2=p1->next;p2!=end;p2=p2->next)
		    {
			   if(p2->chinese_score > p1->chinese_score)
			   {
				   Student *ptemp = new Student;
                   copy(ptemp, p1);
                   copy(p1, p2);
                   copy(p2, ptemp);
		       }	
		    }
      	}
   }
   if(choice==2)//按语文成绩升序排
    {
    	Student *p1,*p2,*tmp;
	    p1=head->next;
	    for(p1;p1!=end;p1=p1->next)//冒泡排序
	    {
		    for(p2=p1->next;p2!=end;p2=p2->next)
		    {
			   if(p2->chinese_score < p1->chinese_score)
			   {
				   Student *ptemp = new Student;
                   copy(ptemp, p1);
                   copy(p1, p2);
                   copy(p2, ptemp);
		       }	
		    }
      	}
   }
   if(choice==3)//按数学成绩降序排
    {
    	Student *p1,*p2,*tmp;
	    p1=head->next;
	    for(p1;p1!=end;p1=p1->next)//冒泡排序
	    {
		    for(p2=p1->next;p2!=end;p2=p2->next)
		    {
			   if(p2->math_score > p1->math_score)
			   {
				   Student *ptemp = new Student;
                   copy(ptemp, p1);
                   copy(p1, p2);
                   copy(p2, ptemp);
		       }	
		    }
      	}
   }
   if(choice==4)//按数学成绩升序排
    {
    	Student *p1,*p2,*tmp;
	    p1=head->next;
	    for(p1;p1!=end;p1=p1->next)//冒泡排序
	    {
		    for(p2=p1->next;p2!=end;p2=p2->next)
		    {
			   if(p2->math_score < p1->math_score)
			   {
				   Student *ptemp = new Student;
                   copy(ptemp, p1);
                   copy(p1, p2);
                   copy(p2, ptemp);
		       }	
		    }
      	}
   }
   if(choice==5)//按英语成绩降序排
    {
    	Student *p1,*p2,*tmp;
	    p1=head->next;
	    for(p1;p1!=end;p1=p1->next)//冒泡排序
	    {
		    for(p2=p1->next;p2!=end;p2=p2->next)
		    {
			   if(p2->english_score > p1->english_score)
			   {
				   Student *ptemp = new Student;
                   copy(ptemp, p1);
                   copy(p1, p2);
                   copy(p2, ptemp);
		       }
		    }
      	}
   }
   if(choice==6)//按英语成绩升序排
    {
    	Student *p1,*p2,*tmp;
	    p1=head->next;
	    for(p1;p1!=end;p1=p1->next)//冒泡排序
	    {
		    for(p2=p1->next;p2!=end;p2=p2->next)
		    {
			   if(p2->english_score < p1->english_score)
			   {
				   Student *ptemp = new Student;
                   copy(ptemp, p1);
                   copy(p1, p2);
                   copy(p2, ptemp);
		       }
		    }
      	}
   }
    cout<<"排序成功!"<<endl;
}

//清空文档
void Student_information::clean()
{
	ofstream out("C++work4.txt",ios::trunc);
	out.close();
	exit(0);//用exit使程序退出程序的时候，不调用Student_information类的析构函数，
			//否则又会把内存的数据写到C++work4.txt文件中 
}

//显示菜单
void Student_information::show_menu()
{
    cout<<"\t\t************学生成绩管理系统菜单**********\n";
    cout<<"\t\t*                                        *\n";
    cout<<"\t\t*              1.录入学生成绩            *\n";
    cout<<"\t\t*                                        *\n";
    cout<<"\t\t*              2.删除学生成绩            *\n";
    cout<<"\t\t*                                        *\n";
    cout<<"\t\t*              3.修改学生成绩            *\n";
    cout<<"\t\t*                                        *\n";
    cout<<"\t\t*              4.显示学生成绩            *\n";
    cout<<"\t\t*                                        *\n";
    cout<<"\t\t*              5.查询学生成绩            *\n";
    cout<<"\t\t*                                        *\n";
    cout<<"\t\t*              6.统计学生成绩            *\n";
    cout<<"\t\t*                                        *\n";
    cout<<"\t\t*              7.排序学生成绩            *\n";
    cout<<"\t\t*                                        *\n";
    cout<<"\t\t*              8.清除学生成绩            *\n";
    cout<<"\t\t*                                        *\n";
    cout<<"\t\t*              0.退出                    *\n";
    cout<<"\t\t*                                        *\n";
    cout<<"\t\t******************************************\n";
    cout<<"\t\t请输入指令(0-8): ";
}
