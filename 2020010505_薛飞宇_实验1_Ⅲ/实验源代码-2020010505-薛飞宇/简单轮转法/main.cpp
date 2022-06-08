#include "stdio.h"
#include <stdlib.h>
#include <conio.h>
#define getpch(type) (type*)malloc(sizeof(type))
#define NULL 0

struct pcb { 			/* ������̿��ƿ�PCB */
	char name[10]; 		/*��������*/
	char state; 		/*����״̬*/
	int super; 			/*�������ȼ�*/
	int ntime; 			/*����Ԥ������ʱ��*/
	int rtime; 			/*��������ʱ��*/
	struct pcb* link; 	/*ָ����һ�����̵�ָ��*/
}*ready=NULL,*p;
						/*readyΪ�������̶��У�pΪ��ǰ����ִ�еĽ���*/

typedef struct pcb PCB;



/* �����Խ��̽������ȼ����к���*/
/*����ת���У�ֻҪ�����н���������*/
sort()
{
	PCB *first, *second;
	int insert=0;
	if((ready==NULL)||((p->super)>(ready->super)))
	/*1�����������Ϊ�ջ��ߵ�ǰ�������ȼ����ڶ�ͷ�������ȼ��Ļ�������ǰ����PCB�����ͷ */
	{
		p->link=ready;
		ready=p;
	}
	else /* ���̱Ƚ����ȼ�,�����ʵ���λ����*/
	{
		first=ready;
		second=first->link;
		while(second!=NULL)
		{
			if((p->super)>(second->super)) /*��������̱ȵ�ǰ������������,*/
			{                              /*���뵽��ǰ����ǰ��*/
				p->link=second;
				first->link=p;
				second=NULL;
				insert=1;
			}
			else /* ����������������,����뵽��β*/
			{
				/*2*/
				first = second;
				second=second->link;
			}
		}
		if(insert==0) first->link=p;
	}
}



/* �������̿��ƿ麯��*/
input()
{
	int i,num;
	system("cls"); /*����*/
	printf("\n �������������?");
	scanf("%d",&num);
	for(i=0;i<num;i++)
	{
		printf("\n ���̺�No.%d:\n",i);
		p=getpch(PCB);
		printf("\n ���������:");
		scanf("%s",p->name);
//		printf("\n �������������:");
//		scanf("%d",&p->super);
/*����ת���У�ֻҪ�����н�����������0����*/

        p->super = 0;
		printf("\n �����������ʱ��:");
		scanf("%d",&p->ntime);
		printf("\n");
		p->rtime=0;p->state='w';
		p->link=NULL;
		sort(); /* ����sort��������������������*/
	}
}

/*��ȡ�������еĳ���*/
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

/*����������ʾ����,������ʾ��ǰ����*/
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

/* �������̲鿴���� */
check()
{
	PCB* pr;
	printf("\n **** ��ǰ�������еĽ�����:%s",p->name); /*��ʾ��ǰ���н���*/
	disp(p);
	pr=ready;
	printf("\n ****��ǰ��������״̬Ϊ:\n"); /*��ʾ��������״̬*/
	while(pr!=NULL)
	{
		disp(pr);
		pr=pr->link;
	}
}

/*�������̳�������(�������н���,��������)*/
destroy()
{
	printf("\n ���� [%s] �����.\n",p->name);
	free(p);
}

/* �������̾�������(��������ʱ�䵽,�þ���״̬)*/
running()
{
	(p->rtime)++;
	if(p->rtime==p->ntime)
		destroy(); /* ����destroy����*/
	else
	{
//		(p->super)--;
		p->state='w'; /*����״̬��Ϊ����̬*/
		sort(); /*����sort����*/
	}
}

/*������*/
main()
{
	int len,h=0; /*����*/
	char ch; /*����*/
	input(); /*������������Ϣ*/
	len=space(); /*len��ȡ�������г���*/
	while((len!=0)&&(ready!=NULL)) /*���������г��Ȳ�Ϊ0���Ҿ������в�Ϊ��ʱ*/
	{
		ch=getchar(); /*�����������*/
		h++; 		  /*ϵͳִ��ʱ��+1*/
		printf("\n The execute number:%d \n",h); /*��ӡ��ǰϵͳ��ִ��ʱ��*/
		/*ִ�о������ж�ͷ�Ľ���*/
		p=ready; /*ָ��pָ��������ж�ͷ*/
		ready=p->link; /*�������ж�ͷָ����һ��PCB*/
		p->link=NULL; /*ԭ�ȶ�ͷ��ָ�����ÿ�*/
		p->state='R'; /*ԭ�ȶ�ͷ�Ľ���״̬��Ϊ����̬*/
		check(); /*���ý��̲鿴����*/
		running(); /*���½��̵����ȼ�������������������*/
		printf("\n ����һ������......");
		ch=getchar();
	}
	printf("\n\n �����Ѿ����.\n");
	ch=getchar();
}
