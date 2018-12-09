//sysu学生信息管理系统 
//github.com/Misakiwei/studentinfocontrol
#include<iostream>
#define MAX_Student 100//最大学生管理数
//typedef int rank;
using namespace std;
string a[3]={"c++","math analysis","English"};
class admin;
void admincontrol(admin administrator);
void studentcontrol(admin administrator);
class student//学生类 
{
	protected:
		int Rank;//排名 
		double* score;//储存单科分数 
		double allscore;//总分 
		string name,studentid,password,email,phonenum;//分别储存姓名,学号,密码，邮箱，电话号码 
		int rank(){return Rank;}//返回排名 
		void copy(student const A);//复制学生函数 
	public:
		student(){double v=0;score=new double[3];for(int i=0;i!=3;score[i++]=v);allscore=0;int Rank=0;string password="0";}//构造函数，构造初始密码0，学生的3科成绩0 
		student(student const &A){copy(A);}//构造函数复制A 
        ~student(){delete [] score;}//析构函数，删除成绩区 
        alterpassword(string k){password=k;}//修改密码 
        //student&operator[](rank r)const;
        //void Register(student const&e);
        student &operator = (student const& A){copy(A);}//重载运算符=为复制右侧对象 
        friend class admin;//admin为友元 
        friend void studentcontrol(admin administrator);
        friend void admincontrol(admin administrator);
};
class admin
{
	protected:
		int size,capacity;//容量和最大容量 
		student *elem;//数据区，存储学生 
		void expand();//扩大数据区 
		void shrink();//缩小数据区 
		void Sort(int lo,int hi);//排序函数 
		int Max(int lo,int hi);//寻找最大rank的人并返回rank
	public:
		admin(int c=MAX_Student,int s=0){elem=new student[capacity=c];size=0;}//构造函数初始化数据区 
		~admin(){delete [] elem;}//析构函数 
		int size1() {return size;}//返回大小 
		bool empty() const{return !size;}//判断空函数 
		//int disordered()const;//判断是否有序函数 
		int find(string const& elem,int lo,int hi) const;//学号无序寻找函数 
		int search(string const& e,int lo,int hi) const;//学号有序寻找函数 
		void remove(int r);//删除学生函数 
		int remove(int lo,int hi);//删除区间的函数 
		int insert(int r,student const&e);//插入学生的函数 
		void newstudent();//新建学生的函数 
		void dosort(student *T,int lo,int hi,int flag);//排序分支 
		void namesort(student *T,int lo,int hi,int flag);//以姓名排序 
		void stunumsort(student *T,int lo,int hi,int flag);//以学号进行排序 
		void scoresort(student *T,int lo,int hi,int flag);//以总分数进行排序 
		//bool flag;
		void Register(student const&e);
		friend void admincontrol(admin administrator);
		friend void studentcontrol(admin administrator);
};
void student::copy(student const A)
{
	Rank=A.Rank;
	score[0]=A.score[0];
	score[1]=A.score[1];
	score[2]=A.score[2];
	name=A.name;
	studentid=A.studentid;
	password=A.password;
	email=A.email;
	phonenum=A.phonenum;
}
void admin::newstudent()
{
	if(size>MAX_Student)
	  expand();
	cout << "请输入学生名字" << endl;
	cin >> elem[size].name;
	cout << "请输入他的学号" << endl;
	cin >> elem[size].studentid;
	cout << "请输入他的三科成绩" << endl;
	for(int i=0;i!=3;i++)
	   {
	   	cout << a[i] << " 的成绩是" <<endl;
	   	cin >> elem[size].score[i];
	   }
	size++;
	cout << "创建成功" << endl;
}
int admin::Max(int lo,int hi)
{
	int max;
	if(!empty())
	   return 0;
	max=elem[0].Rank;
	for (int i=1;i!=size;i++)
	   if(elem[i].Rank>max)
	      max=elem[i].Rank;
	return max;
}
void admin::expand()
{
	if(size<capacity)
	   return;
	student *oldelem = elem;
	elem = new student[2*capacity];
	for(int i=0;i!=size;i++)
	elem[i]=oldelem[i];
	delete [] oldelem;
}
void admin::shrink()
{
	if(size>capacity/2)
	   return;
	student *oldelem = elem;
	elem = new student[capacity/2+1];
	for(int i=0;i!=size;i++)
	elem[i]=oldelem[i];
	delete [] oldelem;
}
void admin::remove(int r)
{
	for(int i=r+1;i!=size;i++)
	   elem[i-1]=elem[i];
	size--;
	shrink();
}
int admin::remove(int lo,int hi)
{
	for(int i=lo;i<=hi;i++)
	  remove(i);
	return hi-lo+1;
}
void admin::Sort(int lo,int hi)
{
	cout << "请输入按什么进行排序" << endl;
	cout << "[1].姓名"<< endl;
	cout << "[2].学号" << endl;
	cout << "[3].总成绩" << endl;
	cout << "[4].返回" << endl;
	int it;
	cin >> it;
	switch(it)
	{
		case 1:
			dosort(elem,0,size-1,1);
			break;
		case 2:
			dosort(elem,0,size-1,2);
			break;
		case 3:
			dosort(elem,0,size-1,3);
			break;
		default:
			break;
	}
}
void admin::dosort(student *T,int lo,int hi,int flag)
{
	cout << "[0].升序" << endl;
	cout << "[1].降序" << endl;
	int it;
	cin >> it;
	if(it!=0&&it!=1)
	   {
	   	cout << "无效输入" << endl;
	   	return;
	   }
	switch(flag)
	{
		case 1:
			namesort(T,lo,hi,it);
			break;
		case 2:
			stunumsort(T,lo,hi,it);
			break;
		case 3:
			scoresort(T,lo,hi,it);
			break;
		default:
			break;
	}
}
void admin::scoresort(student *T,int lo,int hi,int flag)
{
	bool flag1=false;
	if (!flag)
	  {
	  	for (int j=hi;j>=0;j--)
	  	   {
			 for(int i=0;i<j;i++)
	  	      if(T[i].allscore<T[i+1].allscore)
	  	         {
	  	         	swap(T[i],T[i+1]);
	  	         	flag1=true;
				   }
			 if(!flag1)
			    break;
			 else
			    flag1=false;
	       }
}
}
//助教小姐姐就不能不让我们手抄代码吗？
//手抄代码真的太难受了qwq
//求你了 
void admin::namesort(student *T,int lo,int hi,int flag)
{
	bool flag1=false;
	if (!flag)
	  {
	  	for (int j=hi;j>=0;j--)
	  	   {
			 for(int i=0;i<j;i++)
	  	      if(T[i].name<T[i+1].name)
	  	         {
	  	         	swap(T[i],T[i+1]);
	  	         	flag1=true;
				   }
			 if(!flag1)
			    break;
			 else
			    flag1=false;
	       }
}
}
void admin::stunumsort(student *T,int lo,int hi,int flag)
{
	bool flag1=false;
	if (!flag)
	  {
	  	for (int j=hi;j>=0;j--)
	  	   {
			 for(int i=0;i<j;i++)
	  	      if(T[i].studentid<T[i+1].studentid)
	  	         {
	  	         	swap(T[i],T[i+1]);
	  	         	flag1=true;
				   }
			 if(!flag1)
			    break;
			 else
			    flag1=false;
	       }
}
}
//真的手抄代码是我见过最睿智的学c++操作
//我觉得大学课堂不能停留在40年前
//现在都8102年了,还用着c99的标准我就不说什么了 
//真的，求你了
//别让我手抄代码好吗 
//我代码认真写，保证写的让您满意
//别让我手抄代码好吗qwq 
int admin::find(string const& e,int lo,int hi) const
{
	for(int i=lo;i<=hi;i++)
	   if(elem[i].studentid==e)
	      return i;
	return -1;
}
int admin::search(string const& e,int lo,int hi) const
{
	int mi=(lo+hi)/2;
	if(lo>=hi)
	   return -1;
	if (elem[mi].studentid==e)
	   return mi;
	search(e,lo,mi);
	search(e,mi+1,hi);
}
int admin::insert(int r,student const&e)
{
	if(size==0)
	  {
	  	elem[0]=e;
	  	size++;
	  	return 1;
	  }
	if(size+1>capacity)
	   expand();
	for(int i=size;i>=r;i--)
	   elem[i+1]=elem[i];
	elem[r]=e;
	size++;
	return 1;
}
void admin::Register(student const&e)
{
	if (size+1>capacity)
	   expand();
	elem[size]=e;
	size++;
	return;
}
int main()
{
	cout << "欢迎来到中山大学信息管理系统" << endl;
	cout << "初代版本，功能尚有bug" << endl;
	cout << "请参考源码的数据结构和算法" << endl;
	cout << "本人不保证exe文件能正常运行" << endl;
	cout << "源码400+行，作业而言修改bug过于困难，时间不足，敬请原谅" << endl;
	cout << "欲知后续改进版本请移步 github.com/Misakiwei/studentinfocontrol" << endl; 
	cout << "by 邓炜 2018/12/9" << endl;
    cout << "请按任意键开始下一步操作" << endl;
	//system("pause");
	getchar();
	int it;
	admin administrator;
	while(1)
	{
		cout << "请问您是" << endl;
		cout << "[1].学生" << endl;
		cout << "[2].管理员" << endl;
		cout << "[3].退出" <<endl;
		cin >> it;
		if(it==1)
		   	studentcontrol(administrator);
		else if(it==2)
			admincontrol(administrator);
		else if(it==3)
		    break;
		else
		    cout << "输入有误" << endl;
	}
	return 0;
}
void studentcontrol(admin administrator)
{
	cout << "[1].登录" << endl;
	cout << "[2].注册" << endl;//该尚有bug 
	cout << "[3].返回" <<endl;
	int it2;
	cin >> it2;
	if (it2==1)
	   {
	   	string stunum,password;
	   	int i=0;
	   	cout << "请输入学号" << endl;
	   	cin >> stunum;
	   	cout << "请输入密码" << endl;
	   	cin >> password;
	   	for (;i!=administrator.size;i++)
	   	   {
			 if((administrator.elem[i]).studentid==stunum&&(administrator.elem[i]).password==password)
	   	       break;
	   	    if((administrator.elem[i]).studentid==stunum&&(administrator.elem[i]).password!=password)
	   	       	{
					  cout << "密码错误" <<endl;
					  return;
				}
			if((administrator.elem[i]).studentid!=stunum)
			   {
			   cout << "不存在这个学号的学生" << endl;
			   return;
		       }
		   }
		cout << "欢迎您" << (administrator.elem[i]).name << " 同学" << endl;
		while (1)
		{
			cout << "[1].查询排名" << endl;
			cout << "[2].查询成绩" << endl;
			//cout << "[3].查询个人信息" << endl;
			cout << "[3].退出" << endl;
			int it1;
			cin >> it1;
			if(it1==3)
			   break;
			switch(it1)
			{
				case 1:
					cout << "您的排名是" << (administrator.elem[i]).Rank << endl;
					break;
				case 2:
					for(int j=0;j!=3;j++)
					    	cout << a[j] << " 的成绩是" << (administrator.elem[i]).score[j] << endl;
					cout << "总成绩是 " <<(administrator.elem[i]).allscore << endl;
					break;
				default:
					break;
			}
	}
	   }
	if (it2==2)
	{
		cout << "请输入你的学号和姓名" <<endl;
		string stuid,name,password,email,phonenum;
		cin >> stuid >> name ;
		for(int p=0;p!=administrator.size;p++)
		   if((administrator.elem[p]).studentid==stuid)
		       {
		       	cout << "你的信息已被录入系统，请前去登录" << endl;
		       	return;
			   }
		student e;
		e.name=name;
		e.studentid=stuid;
		while(1)
		{
		cout << "请修改您的密码(至少6位)" << endl;
		cin >> password;
		if(password.size()<6)
		    cout << "无效密码" << endl;
		else
		    break;
 	    }
		e.alterpassword(password);
		for(int j=0;j!=3;j++)
		   {
		   	cout << "请输入" << a[j] << " 的成绩" <<endl;
		   	cin >> e.score[j];
		   	e.allscore+=e.score[j];
		   }
		administrator.Register(e);
		cout << "完成创建" <<endl;
		cout << "请登入系统" <<endl;
		return;
	}
}
void admincontrol(admin adminstrator)
{
	cout << "默认管理员密码admin,请使用者自行封装" <<endl;
	cout << "请输入管理员密码" << endl;
	string g;
	cin >> g;
	if(g!="admin")
	{
	   cout << "密码错误" <<endl;
	   return;
    }
    while(1)
    {
    cout << "[1].列出所有学生" << endl;
    cout << "[2].查询某个学生" << endl;
    cout << "[3].排序学生" << endl;
    cout << "[4].创建学生" << endl;
    //cout << "[5].寻找学生" << endl;
    cout << "[5].删除学生" << endl;
    cout << "[6].退出" << endl;
    int it1;
    cin >> it1;
    string stuid,id;
	int k,b;
    if(it1==6)
       return;
    switch(it1)
    {
    	case 1:
    		if(adminstrator.size==0)
    		   cout << "没有学生" << endl;
    		else
    		for(int i=0;i!=adminstrator.size;i++)
    		   {
    		   	cout << "学号" << endl;
    		   	cout << (adminstrator.elem[i]).studentid << endl;
    		   	cout << "姓名" << endl;
    		   	cout << (adminstrator.elem[i]).name << endl;
			   }
			   break;
		case 2:
			cout << "请输入学号" << endl;
			cin >> stuid;
			k=adminstrator.find(stuid,0,adminstrator.size);
			if (k==-1)
			{
			   cout << "不存在该学生" << endl;
			   break;
			}
			cout << "该学生姓名是 " << (adminstrator.elem[k]).name << endl;
			cout << "该学生成绩如下" << endl;
			for (int t=0;t!=3;t++)
			   cout << a[t] <<" 的成绩是 " << (adminstrator.elem[k]).score[t] << endl;
			cout << "他的排名是" << (adminstrator.elem[k]).Rank << endl;
			break;
		case 3:
			adminstrator.Sort(0,adminstrator.size-1);
			break;
		case 4:
			adminstrator.newstudent();
			break;
		case 5:
			cout << "请输入该学生的学号" << endl;
			cin >> id;
			b=adminstrator.find(id,0,adminstrator.size);
			cout << "您确认要删除 " << (adminstrator.elem[b]).name << "同学吗?(y/n)" << endl;
			if(getchar()=='y')
			   adminstrator.remove(b);
			else
			  break;
		case 7:
			cout << (adminstrator.elem[adminstrator.size]).name <<endl;
			break;
		default:
			break;
	}
	//最后我还是要说一下
	//求你了小姐姐，我不想手抄代码 qwq
}
}

