#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define getpch(type) (type*)malloc(sizeof(type))
#define NUM_OF_RESOURCE 3
struct Resource
{
    char name[10];//��cԴ��
    int num;      //��Դ������
    int usedTime; //��ҵ����Դ��ʱ
    struct Resource *link;
};
typedef struct Resource resource;
struct jcb      //��ҵ���ƿ�
{
    char name[10];  // ��ҵ��
    int reachtime;  //��ҵ����ʱ��
    int rnum;       //��ҵ������Դ��������
    int starttime;  //��ҵ��ʼʱ��
    int needtime;
    int finishtime; //��ҵ���ʱ��
    float cycletime;//��ҵ��תʱ��
    float cltime;   //��Ȩ��תʱ��
    char state;     //��ҵ״̬
    int IsUsed;    //��־�Ƿ�ʹ�ø���Դ
    resource *res;  //������Դָ��
    struct jcb *next;      //�ṹ��ָ��
}*ready[4], *p, *q; //q����ָ��ǰ�ڵ�
//�����ĸ����У����ζ�Ӧ������Դ�ľ�������

int times  = 0;
typedef struct jcb JCB;

//��Դ������ҵ
void InsertR ( JCB *p, resource *ptr )
{
    if ( p -> res == NULL )
    {
        p->res = ptr;
    }
    else
    {
        resource* pt = p -> res;
        while ( pt->link != NULL )
            pt = pt->link;
        pt -> link = ptr;
    }
}

//��ҵ����������У������ݵ���ʱ���������
void InsertJobs ( JCB* p, int t )
{
    if ( ready[t] == NULL )
        ready[t] = p;
    else
    {
        JCB *pt = ready[t];
        q = pt->next;
        //�ȶ���Ԫ�������磬�ʹ��ڶ���
        if ( pt->reachtime > p->reachtime )
        {
            ready[t] = p;
            p->next = pt;
        }
        else
        {
            while ( q != NULL && q->reachtime <= p->reachtime )
            {
                pt = pt->next;
                q = pt->next;
            }
            if ( q == NULL )
            {
                pt->next = p;
            }
            else
            {
                pt->next = p;
                p->next = q;
            }
        }

    }
}
//����m����ҵ
void init ( int m )
{
    resource *ptr;
    int i, j;
    printf ( "��������ҵ��" );
    printf ( "%d \n", m );
    for ( i = 0; i < m; i++ )
    {
        p = getpch ( JCB );
        //
        printf ( "������ҵ���� " );
        scanf ( "%s", p->name );
        printf ( "\n������ҵ����ʱ��" );
        scanf ( "%d", &p->reachtime );
        printf ( "\n������ҵ������Դ��������:" );
        scanf ( "%d", &p->rnum );
        p->res = NULL;
        for ( j = 0; j < p->rnum; j++ )
        {
            ptr = ( resource* ) malloc ( sizeof ( resource ) );
            printf ( "\n\t������Դ��: " );
            scanf ( "%s", ptr->name );
            printf ( "\n\t����������Դ������: " );
            scanf ( "%d", &ptr->num );
            printf ( "\n\t�������ҵ���ĸ���Դ��ʱ��: " );
            scanf ( "%d", &ptr->usedTime );
            p->IsUsed = 1; //Ĭ�϶�ʹ��
            ptr->link = NULL;
            InsertR ( p, ptr );
        }
        p->state = 'W';//W��ʾ����״̬
        p->next = NULL;
        InsertJobs   ( p, 0 ); //��p����󱸶���
    }
}
void Running(JCB *p, int j, resource *cre)
{
    printf("%s�ĵ��Ƚ����\n", cre[j].name);
    printf("��ҵ��Ϊ��%s\n", p->name);
    printf("�������Դ��ʱ�䣺%d\n", p->reachtime);
    p->reachtime = p->starttime+p->needtime;
    printf("�ͷŸ���Դ��ʱ��%d\n",p->reachtime);
    InsertJobs(p, j+1);
}
//�����㷨
void FCFS ( resource *cre )
{
    int j = 0;
    for ( j = 0; j < 3; j++ )
    {
        printf ( "\n" );
        p = ready[j];
        if ( p != NULL )
        {
            ready[j] = p->next;
            p->next = NULL;//����ԭ����
        }
        while ( p != NULL )
        {
            //Ѱ��p����������Դ��
            resource * ptr = p->res;
            while ( ptr != NULL && strcmp ( ptr->name, cre[j].name ) )
            {
                ptr = ptr->link;
            }
            //��ҵ��Ҫ����Դ����ĿС�ڵ����ִ���Դ������Ҫ����Դ����ִ��p
            if ( ptr != NULL && ptr->num <= cre[j].num )
            {
                //�����ǰʱ��С�ڵ���ʱ��,��ǰʱ��Ӧ��������ʱ�̲�������
                if ( times <= p->reachtime )
                {
                    times = p->reachtime;
                }
                if ( ptr == NULL )
                {
                    p->starttime = times;
                    p->needtime = 0;
                    p->IsUsed = 0; //��־Ϊ����Ҫ����Դ
                    Running ( p, j, cre );
                }
                //��Ҫ����Դ��Ӧ��ϵͳ��Դ�м�ȥ�������Ŀ
                else
                {
                    p->starttime = times;
                    p->needtime = ptr->usedTime;
                    cre[j].num -= ptr->num;
                    Running ( p, j, cre );
                }
                //ִ����һ����ҵ
                p = ready[j];
                if ( p != NULL )
                {
                    ready[j] = p->next;
                    p->next = NULL;
                }

            }
            else
            {
                JCB*q1;
                q1 = ready[j + 1];
                //�ҵ���һ��ʹ�ø���Դ����δ�ͷŵĽ���q1
                while ( q1 != NULL && q1->IsUsed == 0 )
                    q1 = q1->next;
                if ( q1 == NULL )
                    return;
                times = q1->reachtime;
                resource* ptr1 = q1->res;
                while ( ptr1 != NULL && strcmp ( ptr1->name, cre[j].name ) )
                    ptr1 = ptr1->link;
                if ( ptr1 == NULL )
                    return;
                cre[j].num += ptr1->num;
                q1->IsUsed = 0;
            }

        }
        times=0;//����ʱ��
        JCB* pt = ready[j+1];
        while (pt != NULL)
        {
            pt ->IsUsed = 1;
            pt = pt ->next;
        }

    }
}
int main()
{
    int m;
    resource cre[3];//�������Դ
    //��ʼ���������Դ0Ϊ�����豸��1Ϊcpu��2Ϊ����豸
    //�����豸
    strcpy(cre[0].name, "INS");
    cre[0].num = 2;
    //CPU
    strcpy(cre[1].name, "CPU");
    cre[1].num = 4;
    //����豸
    strcpy(cre[2].name, "OUTS");
    cre[2].num = 2;
    //��ʼ����������
    int id=0;
    for(id=0; id<4; id++)
        ready[id]=NULL;
    //����m����ҵ
    printf("����Ҫ�������ҵ����: ");
    scanf("%d", &m);
    getchar();
    init(m);
    FCFS(cre);
    q = ready[3];
    while(q != NULL)
    {
        ready[3] = q -> next;
        free(q);
        q=q->next;
    }
    return 0;
}

