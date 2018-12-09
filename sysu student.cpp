//sysuѧ����Ϣ����ϵͳ 
//github.com/Misakiwei/studentinfocontrol
#include<iostream>
#define MAX_Student 100//���ѧ��������
//typedef int rank;
using namespace std;
string a[3]={"c++","math analysis","English"};
class admin;
void admincontrol(admin administrator);
void studentcontrol(admin administrator);
class student//ѧ���� 
{
	protected:
		int Rank;//���� 
		double* score;//���浥�Ʒ��� 
		double allscore;//�ܷ� 
		string name,studentid,password,email,phonenum;//�ֱ𴢴�����,ѧ��,���룬���䣬�绰���� 
		int rank(){return Rank;}//�������� 
		void copy(student const A);//����ѧ������ 
	public:
		student(){double v=0;score=new double[3];for(int i=0;i!=3;score[i++]=v);allscore=0;int Rank=0;string password="0";}//���캯���������ʼ����0��ѧ����3�Ƴɼ�0 
		student(student const &A){copy(A);}//���캯������A 
        ~student(){delete [] score;}//����������ɾ���ɼ��� 
        alterpassword(string k){password=k;}//�޸����� 
        //student&operator[](rank r)const;
        //void Register(student const&e);
        student &operator = (student const& A){copy(A);}//���������=Ϊ�����Ҳ���� 
        friend class admin;//adminΪ��Ԫ 
        friend void studentcontrol(admin administrator);
        friend void admincontrol(admin administrator);
};
class admin
{
	protected:
		int size,capacity;//������������� 
		student *elem;//���������洢ѧ�� 
		void expand();//���������� 
		void shrink();//��С������ 
		void Sort(int lo,int hi);//������ 
		int Max(int lo,int hi);//Ѱ�����rank���˲�����rank
	public:
		admin(int c=MAX_Student,int s=0){elem=new student[capacity=c];size=0;}//���캯����ʼ�������� 
		~admin(){delete [] elem;}//�������� 
		int size1() {return size;}//���ش�С 
		bool empty() const{return !size;}//�жϿպ��� 
		//int disordered()const;//�ж��Ƿ������� 
		int find(string const& elem,int lo,int hi) const;//ѧ������Ѱ�Һ��� 
		int search(string const& e,int lo,int hi) const;//ѧ������Ѱ�Һ��� 
		void remove(int r);//ɾ��ѧ������ 
		int remove(int lo,int hi);//ɾ������ĺ��� 
		int insert(int r,student const&e);//����ѧ���ĺ��� 
		void newstudent();//�½�ѧ���ĺ��� 
		void dosort(student *T,int lo,int hi,int flag);//�����֧ 
		void namesort(student *T,int lo,int hi,int flag);//���������� 
		void stunumsort(student *T,int lo,int hi,int flag);//��ѧ�Ž������� 
		void scoresort(student *T,int lo,int hi,int flag);//���ܷ����������� 
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
	cout << "������ѧ������" << endl;
	cin >> elem[size].name;
	cout << "����������ѧ��" << endl;
	cin >> elem[size].studentid;
	cout << "�������������Ƴɼ�" << endl;
	for(int i=0;i!=3;i++)
	   {
	   	cout << a[i] << " �ĳɼ���" <<endl;
	   	cin >> elem[size].score[i];
	   }
	size++;
	cout << "�����ɹ�" << endl;
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
	cout << "�����밴ʲô��������" << endl;
	cout << "[1].����"<< endl;
	cout << "[2].ѧ��" << endl;
	cout << "[3].�ܳɼ�" << endl;
	cout << "[4].����" << endl;
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
	cout << "[0].����" << endl;
	cout << "[1].����" << endl;
	int it;
	cin >> it;
	if(it!=0&&it!=1)
	   {
	   	cout << "��Ч����" << endl;
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
//����С���Ͳ��ܲ��������ֳ�������
//�ֳ��������̫������qwq
//������ 
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
//����ֳ��������Ҽ�������ǵ�ѧc++����
//�Ҿ��ô�ѧ���ò���ͣ����40��ǰ
//���ڶ�8102����,������c99�ı�׼�ҾͲ�˵ʲô�� 
//��ģ�������
//�������ֳ�������� 
//�Ҵ�������д����֤д����������
//�������ֳ��������qwq 
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
	cout << "��ӭ������ɽ��ѧ��Ϣ����ϵͳ" << endl;
	cout << "�����汾����������bug" << endl;
	cout << "��ο�Դ������ݽṹ���㷨" << endl;
	cout << "���˲���֤exe�ļ�����������" << endl;
	cout << "Դ��400+�У���ҵ�����޸�bug�������ѣ�ʱ�䲻�㣬����ԭ��" << endl;
	cout << "��֪�����Ľ��汾���Ʋ� github.com/Misakiwei/studentinfocontrol" << endl; 
	cout << "by ��� 2018/12/9" << endl;
    cout << "�밴�������ʼ��һ������" << endl;
	//system("pause");
	getchar();
	int it;
	admin administrator;
	while(1)
	{
		cout << "��������" << endl;
		cout << "[1].ѧ��" << endl;
		cout << "[2].����Ա" << endl;
		cout << "[3].�˳�" <<endl;
		cin >> it;
		if(it==1)
		   	studentcontrol(administrator);
		else if(it==2)
			admincontrol(administrator);
		else if(it==3)
		    break;
		else
		    cout << "��������" << endl;
	}
	return 0;
}
void studentcontrol(admin administrator)
{
	cout << "[1].��¼" << endl;
	cout << "[2].ע��" << endl;//������bug 
	cout << "[3].����" <<endl;
	int it2;
	cin >> it2;
	if (it2==1)
	   {
	   	string stunum,password;
	   	int i=0;
	   	cout << "������ѧ��" << endl;
	   	cin >> stunum;
	   	cout << "����������" << endl;
	   	cin >> password;
	   	for (;i!=administrator.size;i++)
	   	   {
			 if((administrator.elem[i]).studentid==stunum&&(administrator.elem[i]).password==password)
	   	       break;
	   	    if((administrator.elem[i]).studentid==stunum&&(administrator.elem[i]).password!=password)
	   	       	{
					  cout << "�������" <<endl;
					  return;
				}
			if((administrator.elem[i]).studentid!=stunum)
			   {
			   cout << "���������ѧ�ŵ�ѧ��" << endl;
			   return;
		       }
		   }
		cout << "��ӭ��" << (administrator.elem[i]).name << " ͬѧ" << endl;
		while (1)
		{
			cout << "[1].��ѯ����" << endl;
			cout << "[2].��ѯ�ɼ�" << endl;
			//cout << "[3].��ѯ������Ϣ" << endl;
			cout << "[3].�˳�" << endl;
			int it1;
			cin >> it1;
			if(it1==3)
			   break;
			switch(it1)
			{
				case 1:
					cout << "����������" << (administrator.elem[i]).Rank << endl;
					break;
				case 2:
					for(int j=0;j!=3;j++)
					    	cout << a[j] << " �ĳɼ���" << (administrator.elem[i]).score[j] << endl;
					cout << "�ܳɼ��� " <<(administrator.elem[i]).allscore << endl;
					break;
				default:
					break;
			}
	}
	   }
	if (it2==2)
	{
		cout << "���������ѧ�ź�����" <<endl;
		string stuid,name,password,email,phonenum;
		cin >> stuid >> name ;
		for(int p=0;p!=administrator.size;p++)
		   if((administrator.elem[p]).studentid==stuid)
		       {
		       	cout << "�����Ϣ�ѱ�¼��ϵͳ����ǰȥ��¼" << endl;
		       	return;
			   }
		student e;
		e.name=name;
		e.studentid=stuid;
		while(1)
		{
		cout << "���޸���������(����6λ)" << endl;
		cin >> password;
		if(password.size()<6)
		    cout << "��Ч����" << endl;
		else
		    break;
 	    }
		e.alterpassword(password);
		for(int j=0;j!=3;j++)
		   {
		   	cout << "������" << a[j] << " �ĳɼ�" <<endl;
		   	cin >> e.score[j];
		   	e.allscore+=e.score[j];
		   }
		administrator.Register(e);
		cout << "��ɴ���" <<endl;
		cout << "�����ϵͳ" <<endl;
		return;
	}
}
void admincontrol(admin adminstrator)
{
	cout << "Ĭ�Ϲ���Ա����admin,��ʹ�������з�װ" <<endl;
	cout << "���������Ա����" << endl;
	string g;
	cin >> g;
	if(g!="admin")
	{
	   cout << "�������" <<endl;
	   return;
    }
    while(1)
    {
    cout << "[1].�г�����ѧ��" << endl;
    cout << "[2].��ѯĳ��ѧ��" << endl;
    cout << "[3].����ѧ��" << endl;
    cout << "[4].����ѧ��" << endl;
    //cout << "[5].Ѱ��ѧ��" << endl;
    cout << "[5].ɾ��ѧ��" << endl;
    cout << "[6].�˳�" << endl;
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
    		   cout << "û��ѧ��" << endl;
    		else
    		for(int i=0;i!=adminstrator.size;i++)
    		   {
    		   	cout << "ѧ��" << endl;
    		   	cout << (adminstrator.elem[i]).studentid << endl;
    		   	cout << "����" << endl;
    		   	cout << (adminstrator.elem[i]).name << endl;
			   }
			   break;
		case 2:
			cout << "������ѧ��" << endl;
			cin >> stuid;
			k=adminstrator.find(stuid,0,adminstrator.size);
			if (k==-1)
			{
			   cout << "�����ڸ�ѧ��" << endl;
			   break;
			}
			cout << "��ѧ�������� " << (adminstrator.elem[k]).name << endl;
			cout << "��ѧ���ɼ�����" << endl;
			for (int t=0;t!=3;t++)
			   cout << a[t] <<" �ĳɼ��� " << (adminstrator.elem[k]).score[t] << endl;
			cout << "����������" << (adminstrator.elem[k]).Rank << endl;
			break;
		case 3:
			adminstrator.Sort(0,adminstrator.size-1);
			break;
		case 4:
			adminstrator.newstudent();
			break;
		case 5:
			cout << "�������ѧ����ѧ��" << endl;
			cin >> id;
			b=adminstrator.find(id,0,adminstrator.size);
			cout << "��ȷ��Ҫɾ�� " << (adminstrator.elem[b]).name << "ͬѧ��?(y/n)" << endl;
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
	//����һ���Ҫ˵һ��
	//������С��㣬�Ҳ����ֳ����� qwq
}
}

