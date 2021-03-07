//定义两个类，第一个是存放学生信息的，同时也是要传入文件的； 
//第二个是声明所需要的操作函数 
#ifndef WORK4CLASS_H_
#define WORK4CLASS_H_
using namespace std;

//学生信息结点
class Student{
	public:
		char student_name[20];
		char student_ID[10];
		int chinese_score;
		int math_score;
		int english_score;
		int average_score;
		Student *next;
		
		void input();
		void readfile(ifstream &in);
};

//学生信息结点链表
class Student_information
{
    public:
	    Student_information();
	    ~Student_information();
	    void show_menu();//显示菜单 
  	    void add();      //增加 
	    void del();      //删除 
	    void display();  //显示 
	    void find();     //查询 
	    void modify();   //修改 
	    void save();     //保存 
    	void copy(Student *p1,Student *p2);//交换节点 
	    void sort();     //排序 
	    void count();    //统计
	    void clean();    //清除 
	private: 
	//Student_information类可以看作是以Student类为结点的链表 
	    Student *head;//链表头 
	    Student *end; //链表尾 
	    ifstream in;
		ofstream out; 
};
#endif
