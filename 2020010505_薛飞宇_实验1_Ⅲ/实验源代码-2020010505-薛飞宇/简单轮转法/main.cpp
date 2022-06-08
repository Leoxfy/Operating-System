#include "stdio.h"
#include <stdlib.h>
#include <conio.h>
#define getpch(type) (type*)malloc(sizeof(type))
#define NULL 0

struct pcb { 			/* 定义进程控制块PCB */
	char name[10]; 		/*进程名字*/
	char state; 		/*进程状态*/
	int super; 			/*进程优先级*/
	int ntime; 			/*进程预计运行时间*/
	int rtime; 			/*进程运行时间*/
	struct pcb* link; 	/*指向下一个进程的指针*/
}*ready=NULL,*p;
						/*ready为就绪进程队列，p为当前正在执行的进程*/

typedef struct pcb PCB;



/* 建立对进程进行优先级排列函数*/
/*简单轮转法中，只要将所有进程优先数*/
sort()
{
	PCB *first, *second;
	int insert=0;
	if((ready==NULL)||((p->super)>(ready->super)))
	/*1如果就绪队列为空或者当前进程优先级大于队头进程优先级的话，将当前进程PCB插入队头 */
	{
		p->link=ready;
		ready=p;
	}
	else /* 进程比较优先级,插入适当的位置中*/
	{
		first=ready;
		second=first->link;
		while(second!=NULL)
		{
			if((p->super)>(second->super)) /*若插入进程比当前进程优先数大,*/
			{                              /*插入到当前进程前面*/
				p->link=second;
				first->link=p;
				second=NULL;
				insert=1;
			}
			else /* 插入进程优先数最低,则插入到队尾*/
			{
				/*2*/
				first = second;
				second=second->link;
			}
		}
		if(insert==0) first->link=p;
	}
}



/* 建立进程控制块函数*/
input()
{
	int i,num;
	system("cls"); /*清屏*/
	printf("\n 请输入进程数量?");
	scanf("%d",&num);
	for(i=0;i<num;i++)
	{
		printf("\n 进程号No.%d:\n",i);
		p=getpch(PCB);
		printf("\n 输入进程名:");
		scanf("%s",p->name);
//		printf("\n 输入进程优先数:");
//		scanf("%d",&p->super);
/*简单轮转法中，只要将所有进程优先数置0即可*/

        p->super = 0;
		printf("\n 输入进程运行时间:");
		scanf("%d",&p->ntime);
		printf("\n");
		p->rtime=0;p->state='w';
		p->link=NULL;
		sort(); /* 调用sort函数，将就绪队列排序*/
	}
}

/*获取就绪队列的长度*/
int space()
{
	int l=0; PCB* pr=ready;
	while(pr!=NULL)
	{
		l++;
		pr=pr->link;
	}
	return(l);
}

/*建立进程显示函数,用于显示当前进程*/
disp(PCB * pr)
{
	printf("\n qname \t state \t ndtime \t runtime\n");
	printf("|%s\t",pr->name);
	printf("|%c\t",pr->state);
//	printf("|%d\t",pr->super);
	printf("|%d\t",pr->ntime);
	printf("|%d\t",pr->rtime);
	printf("\n");
}

/* 建立进程查看函数 */
check()
{
	PCB* pr;
	printf("\n **** 当前正在运行的进程是:%s",p->name); /*显示当前运行进程*/
	disp(p);
	pr=ready;
	printf("\n ****当前就绪队列状态为:\n"); /*显示就绪队列状态*/
	while(pr!=NULL)
	{
		disp(pr);
		pr=pr->link;
	}
}

/*建立进程撤消函数(进程运行结束,撤消进程)*/
destroy()
{
	printf("\n 进程 [%s] 已完成.\n",p->name);
	free(p);
}

/* 建立进程就绪函数(进程运行时间到,置就绪状态)*/
running()
{
	(p->rtime)++;
	if(p->rtime==p->ntime)
		destroy(); /* 调用destroy函数*/
	else
	{
//		(p->super)--;
		p->state='w'; /*进程状态改为就绪态*/
		sort(); /*调用sort函数*/
	}
}

/*主函数*/
main()
{
	int len,h=0; /*声明*/
	char ch; /*声明*/
	input(); /*输入进程相关信息*/
	len=space(); /*len获取就绪队列长度*/
	while((len!=0)&&(ready!=NULL)) /*当就绪队列长度不为0并且就绪队列不为空时*/
	{
		ch=getchar(); /*按任意键继续*/
		h++; 		  /*系统执行时间+1*/
		printf("\n The execute number:%d \n",h); /*打印当前系统已执行时间*/
		/*执行就绪队列队头的进程*/
		p=ready; /*指针p指向就绪队列队头*/
		ready=p->link; /*就绪队列队头指向下一个PCB*/
		p->link=NULL; /*原先队头的指针域置空*/
		p->state='R'; /*原先队头的进程状态改为运行态*/
		check(); /*调用进程查看函数*/
		running(); /*更新进程的优先级，就绪队列重新排序*/
		printf("\n 按任一键继续......");
		ch=getchar();
	}
	printf("\n\n 进程已经完成.\n");
	ch=getchar();
}
