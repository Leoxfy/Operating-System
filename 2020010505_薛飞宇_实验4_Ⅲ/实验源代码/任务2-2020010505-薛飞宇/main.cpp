#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<iomanip>

#if _MSC_VER>1000
#pragma once
#endif	//_MSC_VER>1000

using namespace std;
extern int disk_block[10000];
extern int disk_empty;
typedef struct UFD		//存储文件信息
{
	char name[10];		//文件名
	int attribute;		//属性
	int length;			//长度
	int a[10];		//为文件本身分配10个空间
	int *p1;			//一级索引，100个空间
	int (*p2)[100];		//二级索引，100*100个空间
	struct UFD *next;
}UFD;
typedef struct DIR		//存储目录信息
{
	DIR* above;			//上一结点
	char name[10];
	int length;
	DIR *next;			//下一结点
	UFD *File_head;		//此目录下的文件指针
	DIR *Dir_head;		//此目录下目录链表指针
}DIR;

class Cuse				//定义管理用户目录的类
{
	DIR *now;			//当前目录
	UFD *Fhead;			//文件的头结点
	DIR *Dhead;			//根目录的目录链头结点
	char code[10];		//密码
	char name[10];		//用户名
	int length;			//用户空间大小
	int status;			//是否获得空间
public:
	void set_status(int);
	int dele_user();
	int dis_file();		//显示文件所占外存块号
	int dis_dir(DIR *d);//当前路径
	int get_length();
	char const *get_name();
	char const *get_code();
	int get_status();
	int set_user(char *,char *);//设置用户名与密码
	DIR *get_now();
	int dele_file(UFD *f);		//删除文件
	int dele_dir(DIR*);			//删除目录
	Cuse();						//构造
	~Cuse();					//析构
	int goback();				//返回上级
	int dis_now();				//显示当前目录
	int new_file();
	int new_dir();
	int open_dir();
	int open_file();
	int first_dele_file();		//删除文件的前部分工作
	int first_dele_dir();		//删除目录的前部分工作
	int set_code();
};

class Cdisk{					//用户类
public:
	Cuse user[5];		//用户个数最多为5
	char code[10];
	int dis_disk();
	int first_dele_user();
	int dele_user(int);
	int new_user();				//查看当前用户与外存空间使用情况，后创建新用户
	int set_code();				//设置新密码
	int login(char);				//登陆
	Cdisk();
	virtual~Cdisk();			//虚函数，析构
};

int disk_block[10000];
int disk_empty;
Cdisk::Cdisk()		//管理磁盘的类，构造函数
{
	int i=0;
	char code[10]="123456";
	for(i=0;i<10000;i++)		//初始化所有磁盘块为空闲
		disk_block[i]=0;
	//this->user[0].set_user("student","123");//默认一个用户
	disk_empty=10000;
	cout.setf(ios::left);	//设置输出方式
}
Cdisk::~Cdisk()		//析构
{
}

int Cdisk::dele_user(int i)		//Cdisk类dele_user的构造
{
	Cuse C;
	C=user[i];
	user[i].dele_user();		//调用Cuse类的成员函数 int dele_user()
	return 1;
}

int Cdisk::dis_disk()		//检查磁盘信息
{
	int i=0;
	cout<<setw(14)<<"用户名"<<setw(14)<<"占用空间大小"<<endl;
	for(i=0;i<5;i++)
		if(user[i].get_status()==1)		//存在的用户的信息
			cout<<setw(14)<<user[i].get_name()<<setw(14)<<user[i].get_length()<<endl;
		cout<<"已用空间："<<10000-disk_empty<<endl<<"剩余空间："<<disk_empty<<endl;
		return 1;
}
int Cdisk::login(char b)		//登陆
{
	char n[10],c[10];
	int i;
	if(b=='1')
	{
		cout<<"用户：管理员"<<endl;
		cout<<"密码：默认\n"<<endl;
		system("pause");
		return 1;
	}
	else
	{
		if(!user[0].get_status())	//当前不存在用户
		{
			i=0;
			cout<<"当前用户为空，欢迎注册！"<<endl;
			user[i].set_status(1);		//为新用户分配权利
			cout<<"请输入用户名："<<endl;
			cin>>n;
			cout<<"请输入密码："<<endl;
			cin>>c;
			user[i].set_user(n,c);		//调用Cuse的成员函数，传递用户名与密码

			cout<<"恭喜，创建用户成功！"<<endl;
			return i;
		}
		else
		{
			cout<<"用户名:";
			cin>>n;
			cout<<"密码：";
			cin>>c;
			cout<<endl;
			for(i=0;i<5;i++)	//查找是否存在此用户
			{
				if(user[i].get_status())		//存在方比较
					if(!strcmp(n,user[i].get_name()))	//相等时为0，此判断为匹配
						if(!strcmp(c,user[i].get_code()))		//密码匹配
						{
							cout<<"登陆成功！"<<endl;
							cout<<"欢迎"<<user[i].get_name()<<"登陆"<<endl;
							return i;
						}
						else
						{
							cout<<"密码错误"<<endl;
							return -1;
						}
			}
			cout<<"此用户不存在！"<<endl;
			return -1;
		}
	}
}

int Cdisk::set_code()		//设置新密码
{
	char temp1[10],temp2[10];
	cout<<"请输入原密码"<<endl;
	cin>>temp1;
	if(strcmp(temp1,code))		//无疑是针对当前用户进行操作，故直接code
	{
		cout<<"原密码错误！"<<endl;
		return 0;
	}
	while(1)
	{
		cout<<"请输入新密码："<<endl;
		cin>>temp1;
		cout<<"请再次输入新密码："<<endl;
		cin>>temp2;
		if(strcmp(temp1,temp2))
		{
			cout<<"两次密码不相同，请重输!"<<endl;
			break;
		}
		cout<<"密码设置成功！"<<endl;
		strcpy(code,temp1);		//保存新密码
		break;
	}
	return 1;
}

int Cdisk::new_user()		//准备创建新用户
{
	char n[10],c[10];
	int i=0,j;
	for(i=0;i<5;i++)
		if(user[i].get_status()==0)		//是否有此用户，此尚未存在
			break;
		if(i==5)
		{
			cout<<"已经达到最大用户5个，不能再创建！"<<endl;
			return 0;
		}
		user[i].set_status(1);		//为新用户分配权利
		cout<<"请输入用户名："<<endl;
		cin>>n;
		if(i>0)			//已有其它用户存在
		{
			for(j=0;j<i-1;j++)
				if(!strcmp(user[j].get_name(),n))
				{
					cout<<"此用户名已存在！"<<endl;
					return 0;
				}
		}
		cout<<"请输入密码："<<endl;
		cin>>c;
		user[i].set_user(n,c);		//调用Cuse的成员函数，传递用户名与密码
		cout<<"恭喜，创建用户成功！"<<endl;
		return 1;
}

int Cdisk::first_dele_user()		//删除用户
{
	char n[10],c;
	int i;
	cout<<"请输入你要删除的用户名"<<endl;
	cin>>n;
	for(i=0;i<5;i++)		//在查找用户的同时，得到用户序号i
		if(!strcmp(user[i].get_name(),n)&&user[i].get_status())
			break;		//找到，跳出
		if(i==5)
		{
			cout<<"出错啦，此用户不存在！"<<endl;
			return 0;
		}
		cout<<"确认删除此用户？确认Y，取消任意键"<<endl;
		cin>>c;
		if(c!='Y'&&c!='y')
		{
			cout<<"已经取消删除！"<<endl;
			return 0;
		}
		this->dele_user(i);
		cout<<"用户删除成功"<<endl;
		return 1;
}

Cuse::Cuse()		//构造函数，初始化成员
{
	status=0;		//用户权利，即是否被创建标记
	length=0;		//空间
	now=0;			//当前目录
	Fhead=0;		//文件
	Dhead=0;		//目录
}

Cuse::~Cuse()		//析构，清除程序占用的内存
{
	disk_empty+=length;
	length=0;
	UFD *f=Fhead;
	DIR *d=Dhead;
	while(f!=0)		//文件
	{
		if(f->next==0)
		{
			this->dele_file(f);
			f=0;
			break;
		}
		while(f->next->next!=0)
			f=f->next;
		this->dele_file(f->next);
		f->next=0;
		f=Fhead;
	}
	while(d!=0)		//目录
	{
		if(d->next==0)
		{
			this->dele_dir(d);
			d=0;
			break;
		}
		while(d->next->next!=0)
			d=d->next;
		this->dele_dir(d->next);
		d->next=0;
		d=Dhead;
	}
}


int Cuse::new_file()		//建立新文件
{
	int i=0,j=0;
	UFD *f,*p=0;
	DIR *D;

	p=new UFD;				//开辟一个新的文件结构体
	if(p==0)
	{
		cout<<"无可用内存空间，创建文件失败！"<<endl;
		return 1;
	}
	cout<<"请输入建立的文件名：";
	cin>>p->name;
	if(now==0)			//根目录下的文件链
		f=Fhead;
	else				//当前目录下的文件链
		f=now->File_head;
	while(f!=0)			//检查是否文件重名
	{
		if(!strcmp(p->name,f->name))
		{
			cout<<"此文件已存在！"<<endl;
			return 0;	//退出
		}
		f=f->next;
	}
	cout<<"\n"<<"长度：";
	cin>>p->length;
	cout<<"\n"<<"属性(0：只读，1：读写)：";
	cin>>p->attribute;
	cout<<endl;
	if(p->length>disk_empty)		//空间不足
	{
		cout<<"文件太大，空间不足，当前空间为："<<disk_empty<<endl;
		delete p;
		return 0;
	}
	disk_empty=disk_empty-p->length;	//剩余空闲盘块
	//
	for(i=0;i<p->length&&i<10;i++)		//文件较小时，直接地址，文件数据盘块号
		for(j;j<10000;j++)				//位示图法
			if(disk_block[j]==0)		//空闲
			{
				p->a[i]=j;				//得到此空间
				disk_block[j]=1;		//标记为已分配出去
				j++;
				break;					//跳出寻找，为文件分配下一空间
			}
			p->p1=0;					//一级索引
			p->p2=0;					//二级索引
			if(p->length>10)			//超过10，用一级索引
			{
				p->p1=new int[100];		//为一级索引分配100个空间
				for(i=10;i<p->length&&i<110;i++)
					for(j;j<10000;j++)		//j，继续前面的值
						if(disk_block[j]==0)
						{
							(p->p1)[i-10]=j;
							disk_block[j]=1;
							j++;
							break;
						}
						if(p->length>110)			//超过110，得用二级索引
						{
							p->p2=new int[100][100];	//在一级索引的基础上，2维
							for(i=110;i<p->length;i++)
								for(j;j<10000;j++)		//j，继续前面的值
									if(disk_block[j]==0)
									{
										int m=(i-110)/100;		//行
										int k=(i-110)%100;		//列
										p->p2[m][k]=j;
										disk_block[j]=1;
										j++;
										break;
									}
						}
			}
			if(now==0)	//根目录下的文件
			{
				p->next=Fhead;	//后继结点指向头，即新指点在前
				Fhead=p;	//新结点在头
			}
			else
			{
				p->next=now->File_head;
				now->File_head=p;
			}
			length+=p->length;	//用户总空间大小增加
			if(now!=0)			//子目录下空间大小增加
			{
				now->length+=p->length;
				D=now->above;	//上一级目录
				while(D!=0)		//上级目录（根目录已实现）空间增加
				{
					D->length+=p->length;
					D=D->above;		//逐级向上
				}
			}

			return 0;
}

int Cuse::new_dir()		//建立新目录
{
	DIR *p,*h;
	cout<<"请输入新目录的名字："<<endl;
	p=new DIR;
	cin>>p->name;		//目录名
	p->Dir_head=0;		//目录下的目录链为空
	p->length=0;		//
	p->File_head=0;		//目录下的文件为空
	if(now==0)			//当前为主目录
		h=Dhead;	//第一次时，h=0；指向目录链
	else
		h=now->Dir_head;//当前的目录链
	while(h!=0)	//此目录下存在其它子目录
	{
		if(!strcmp(h->name,p->name))
		{
			cout<<"此目录已存在！"<<endl;
			return 0;
		}
		h=h->next;
	}
	if(now==0)		//当前为主目录
	{
		p->above=0;		//主目录里目录的上一结点为0
		p->next=Dhead;		//把原目录接入新目录后面（Dhead初始为0）
		Dhead=p;		//Dhead始终指向最新目录结点
	}
	else
	{
		p->above=now;		//当前目录为新目录的上一结点
		p->next=now->Dir_head;	//反序插入新目录
		now->Dir_head=p;	//更新目录链
	}
	cout<<"目录创建成功"<<endl;
	return 1;
}

int Cuse::goback()		//向上返回
{
	if(now==0)
	{
		cout<<"已是主目录，不能向上！"<<endl;
		return 0;
	}
	now=now->above;		//上一结点
	return 1;
}

int Cuse::open_dir()	//打开目录
{
	char name[10];
	DIR *p;
	if(now==0)	//当前主目录
		p=Dhead;
	else
		p=now->Dir_head;	//p指向目录链
	cout<<"请输入你要打开的目录名："<<endl;
	cin>>name;
	//int flag=0;
	while(p!=0)
	{
		if(strcmp(p->name,name)==0)
		{
			now=p;	//找到目录，now标记
			return 1;
		}
		p=p->next;
	}
	cout<<"当前没此目录"<<endl;
	return 0;
}

int Cuse::first_dele_file()	//删除文件的前面工作
{
	char temp[10],a[5];
	cout<<"你要删除的文件名："<<endl;
	cin>>temp;
	UFD *f=Fhead;	//数据文件头指针
	UFD *above=0;
	if(now!=0)
		f=now->File_head;	//当前目录下的数据文件
	while(f!=0)
	{
		if(!strcmp(f->name,temp))
			break;	//找到，跳出
		above=f;	//标记第一个文件
		f=f->next;
	}
	if(f==0)
	{
		cout<<"此文件不存在"<<endl;
		return 0;
	}
	cout<<"确定删除"<<f->name<<"文件吗？按0确定，其他键取消"<<endl;
	cin>>a;
	if(a[0]!='0')
	{
		cout<<"已取消删除文件。"<<endl;
		return 0;
	}
	disk_empty+=f->length;	//回收此数据文件的空间大小
	if(now==0)	//根目录
	{
		if(f==Fhead)
			Fhead=Fhead->next;
		else
			above->next=f->next;
	}
	else
	{
		DIR *d=now;
		while(d!=0)
		{
			d->length=f->length;
			d=d->above;
		}
		if(f==now->File_head)
			now->File_head=now->File_head->next;
		else
			above->next=f->next;
	}
	length-=f->length;
	this->dele_file(f);
	cout<<"删除成功"<<endl;
	return 1;
}

int Cuse::dele_file(UFD *f)	//具体实现删除文件
{
	int i=0,m;
	for(i=0;i<10&&i<f->length;i++)	//回收文件具体空间，重置空闲
	{
		m=f->a[i];
		disk_block[m]=0;
	}
	if(f->p1!=0)	//回收一级索引
	{
		for(i=10;i<110&&i<f->length;i++)
		{
			m=f->p1[i-10];
			disk_block[m]=0;
		}
		delete[](f->p1);
	}
	if(f->p2!=0)	//回收二级索引
	{
		for(i=110;i<f->length;i++)
		{
			m=(f->p2)[(i-110)/100][(i-110)%100];
			disk_block[m]=0;
		}
		delete[](f->p2);
		delete f;
	}
	f=0;	//要删除的文件为空了
	return 1;
}

int Cuse::first_dele_dir()	//删除目录的前奏
{
	char n[10];
	char c;
	DIR *p,*above=0;
	p=Dhead;	//指向根目录下的目录链
	if(now!=0)
		p=now->Dir_head;	//指向当前目录下的目录链
	cout<<"要删除的目录名："<<endl;
	cin>>n;
	while(p!=0)
	{
		if(!strcmp(p->name,n))
			break;	//找到要删除的目录，跳出
		above=p;	//保存前一结点
		p=p->next;
	}
	if(p==0)
	{
		cout<<"没有这个目录！"<<endl;
		return 0;
	}
	cout<<"确定删除当前目录及此目标上的所有信息吗？按0确定，其他键取消"<<endl;
	cin>>c;
	if(c!='0')
		return 0;
	disk_empty+=p->length;	//回收磁盘空间
	if(now==0)
	{
		if(p==Dhead)	//如果是根目录下头结点，直接移动Dhead
			Dhead=Dhead->next;
		else
			above->next=p->next;//中间抽掉目标
	}
	else
	{
		if(p==now->Dir_head)
			now->Dir_head=now->Dir_head->next;
		else
			above->next=p->next;
		above=now;	//当前目录
		while(above!=0)
		{
			above->length-=p->length;//用above标记当前目录，进行大小更新
			above=above->above;	//向上一级
		}
	}
	length-=p->length;	//根目录大小更新
	this->dele_dir(p);
	p=0;
	cout<<"删除成功！"<<endl;
	return 1;
}

int Cuse::dele_dir(DIR *p)	//具体实现删除目录的工作
{
	int flag=0;
	DIR *d=p->Dir_head;	//当前目录下的目录链表
	UFD *f=p->File_head;	//当前目录下的文件链
	if(f!=0)
	{
		while(p->File_head->next!=0)//删除目录里的文件
		{
			f=p->File_head;
			while(f->next->next!=0)
				f=f->next;
			this->dele_file(f->next);
			f->next=0;
		}
		if(p->File_head->next==0)
		{
			this->dele_file(p->File_head);//删除头文件
			p->File_head=0;
		}
	}
	if(d!=0)	//删除目录下的目录
	{
		while(p->Dir_head->next!=0)
		{
			d=p->Dir_head;
			while(d->next->next!=0)
				d=d->next;
			this->dele_dir(d->next);
			d->next=0;
		}
		if(p->Dir_head->next==0)
		{
			this->dele_dir(p->Dir_head);//删除目录链头结点
			p->Dir_head=0;
		}
	}
	delete p;	//释放p占用的内存
	p=0;		//置0
	return 1;
}

int Cuse::dis_now()	//显示当前目录
{
	DIR *d=Dhead;
	UFD *f=Fhead;
	if(now!=0)
	{
		d=now->Dir_head;	//当前目录下的目录链
		f=now->File_head;
	}
	if(d==0&&f==0)
	{
		cout<<"当前目录为空"<<endl;
		return 0;
	}
	cout<<"当前目录大小：";
	if(now==0)
		cout<<length;
	else
		cout<<now->length;
	cout<<endl;
	if(d==0)
		cout<<"当前目录下没有目录"<<endl;
	else
	{
		cout<<"当前目录下包含如下目录："<<endl;
		cout<<setw(14)<<"目录名称"<<setw(14)<<"目录大小"<<endl;
		while(d!=0)
		{
			cout<<setw(14)<<d->name<<setw(14)<<d->length<<endl;
			d=d->next;
		}
	}
	if(f==0)
		cout<<"当前目录下没有文件"<<endl;
	else
	{
		cout<<"当前目录下包含如下文件:"<<endl;
		cout<<setw(14)<<"文件名称"<<setw(14)<<"文件大小"<<setw(14)<<"文件属性"<<endl;
		while(f!=0)
		{
			cout<<setw(14)<<f->name<<setw(14)<<f->length<<setw(14)<<f->attribute<<endl;
			f=f->next;
		}
	}
	return 1;
}

int Cuse::open_file()	//打开文件
{
	char n[10];
	cout<<"请输入要打开的文件名"<<endl;
	cin>>n;
	UFD *f=Fhead;	//文件头指针
	if(now!=0)
		f=now->File_head;	//指向文件
	while(f!=0)
	{
		if(!strcmp(f->name,n))
		{
			cout<<"文件打开成功"<<endl;
			return 1;
		}
		f=f->next;
	}
	cout<<"当前目录无此文件"<<endl;
	return 0;
}

int Cuse::set_code()	//设置密码
{
	char a1[10],a2[10];
	cout<<"请输入原密码"<<endl;
	cin>>a1;
	if(strcmp(a1,code))
	{
		cout<<"密码错误"<<endl;
		return 0;
	}
	while(1)
	{
		cout<<"请输入新密码："<<endl;
		cin>>a1;
		cout<<"再次输入新密码:"<<endl;
		cin>>a2;
		if(strcmp(a1,a2))
			cout<<"两次输入密码不同，请重输！"<<endl;
		else
		{
			strcpy(code,a1);
			cout<<"密码修改成功！"<<endl;
			break;
		}
	}
	return 1;
}

DIR *Cuse::get_now()	//得到当前目录路径
{
	return now;
}

int Cuse::set_user(char *n,char *c)//建立用户与密码
{
	strcpy(name,n);
	strcpy(code,c);
	status=1;
	return 1;
}

void Cuse::set_status(int b)//标记分配
{
	status=b;
}

int Cuse::get_status()//探取是否分配
{
	return status;
}

const char* Cuse::get_code()//得到密码
{
	return code;
}

const char* Cuse::get_name()//得到名字
{
	return name;
}

int Cuse::get_length()//得到长度
{
	return length;
}

int Cuse::dis_dir(DIR *d)//显示目录
{
	if(d==0)
		return 0;
	if(d->above!=0)
		this->dis_dir(d->above);//递归调用此功能
	cout<<"	"<<d->name<<'\n';
	return 0;
}

int Cuse::dis_file()//查看文件
{
	int i;
	char n[10];
	UFD *f=Fhead;
	if(now!=0)
		f=now->File_head;
	cout<<"请输入要查看的文件名："<<endl;
	cin>>n;
	while(f!=0)
	{
		if(!strcmp(n,f->name))	//找到此文件，跳出
			break;
		f=f->next;
	}
	if(f==0)
	{
		cout<<"当前目录下没此文件"<<endl;
		return 0;
	}
	if(f->attribute==0)
		cout<<"此为只读文件，";
	else
		cout<<"此为读写文件，";
	cout<<"占用硬盘块号如下："<<endl;
	for(i=0;i<f->length&&i<10;i++)		//直接存放的
	{
		cout<<setw(6)<<f->a[i];
		if((i+1)%10==0)
			cout<<endl;
	}
	for(i=10;i<f->length&&i<110;i++)	//一级索引存放的
	{
		cout<<setw(6)<<f->p1[i-10];
		if((i+1)%10==0)
			cout<<endl;
	}
	for(i=110;i<f->length;i++)	//二级索引存放的
	{
		cout<<setw(6)<<f->p2[(i-110)/100][(i-110)%100];
		if((i+1)%10==0)
			cout<<endl;
	}
	cout<<endl;
	return 1;
}

int Cuse::dele_user()//删除用户
{
	length=0;	//用户空间置0
	Fhead=0;
	Dhead=0;
	now=0;
	status=0;
	return 1;
}


int main()
{
	char c;
	Cdisk D;		//管理员类的对象
	int i=1,n,flag=1,t=0;

	while(flag)
	{
		cout<<"*******************欢迎使用文件系统**************************"<<endl;
		cout<<endl;
		cout<<"***                 1.管理员登陆"<<endl;
		cout<<"***                 2.用户登陆"<<endl;
		cout<<"***                 3.退出系统"<<endl;
		cout<<endl;
		cout<<"*************************************************************"<<endl;

		cout<<"\n请输入选择：";
		cin>>c;
		switch(c)
		{
		case '1':
			n=D.login(c);
			flag=1;
			system("cls");
			cout<<"管理员登陆成功！"<<endl;
			while(flag)
			{
				cout<<"*************************************************************"<<endl;
				cout<<"***1.创建用户"<<endl;
				cout<<"***2.删除用户"<<endl;
				cout<<"***3.查看当前用户"<<endl;
				cout<<"***4.修改密码"<<endl;
				cout<<"***5.返回登陆窗口"<<endl;
				cout<<"*************************************************************"<<endl;
				cout<<"请选择：";
				cin>>c;
				cout<<endl;
				switch(c){
				case '1':
					D.new_user();
					break;
				case '2':
					D.first_dele_user();
					break;
				case '3':
					D.dis_disk();
					break;
				case '4':
					{
						if(t==0)	//t作标记，防止重复设置密码出错
							strcpy(D.code,"123");
						D.set_code();
						t++;
						break;
					}
				case '5':
					{
						flag=0;
						system("cls");
					}
					break;
				default:
					cout<<"请输入1-5！"<<endl;
				}
			}
			flag=1;
			break;
		case '2':
			n=D.login(c);
			if(n==-1)
				break;
			while(flag)
			{
				cout<<"*************************************************************"<<endl;
				cout<<"***1.创建文件"<<endl;
				cout<<"***2.删除文件"<<endl;
				cout<<"***3.创建目录"<<endl;
				cout<<"***4.删除目录"<<endl;
				cout<<"***5.打开目录"<<endl;
				cout<<"***6.返回上一层目录"<<endl;
				cout<<"***7.查看当前目录"<<endl;
				cout<<"***8.修改密码"<<endl;
				cout<<"***9.查看文件"<<endl;
				cout<<"***0.安全退出"<<endl;
				cout<<"*************************************************************"<<endl;
				cout<<"用户："<<D.user[n].get_name()<<'\n'<<"目录为:\n	root\n";
				D.user[n].dis_dir(D.user[n].get_now());
				cout<<endl;
				cout<<"请输入选择：";
				cin>>c;
				cout<<endl;
				switch(c)
				{
				case '1':
					D.user[n].new_file();
					break;
				case '2':
					D.user[n].first_dele_file();
					break;
				case '3':
					D.user[n].new_dir();
					break;
				case '4':
					D.user[n].first_dele_dir();
					break;
				case '5':
					D.user[n].open_dir();
					break;
				case '6':
					D.user[n].goback();
					break;
				case '7':
					D.user[n].dis_now();
					break;
				case '8':
					D.user[n].set_code();
					break;
				case '9':
					D.user[n].dis_file();
					break;
				case '0':
					{
						flag=0;
						system("cls");
					}
					break;
				default:
					cout<<"请输入0-9"<<endl;
				}
			}
			flag=1;
			break;
		case '3':
			flag=0;
			break;
		default:
			cout<<"请输入1-3！"<<endl;
			}
		}
}
