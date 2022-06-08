#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define getpch(type) (type*)malloc(sizeof(type))
#define NUM_OF_RESOURCE 3
struct Resource
{
    char name[10];//资c源名
    int num;      //资源的数量
    int usedTime; //作业该资源耗时
    struct Resource *link;
};
typedef struct Resource resource;
struct jcb      //作业控制块
{
    char name[10];  // 作业名
    int reachtime;  //作业到达时间
    int rnum;       //作业所需资源的种类数
    int starttime;  //作业开始时间
    int needtime;
    int finishtime; //作业完成时间
    float cycletime;//作业周转时间
    float cltime;   //带权周转时间
    char state;     //作业状态
    int IsUsed;    //标志是否使用该资源
    resource *res;  //所需资源指针
    struct jcb *next;      //结构体指针
}*ready[4], *p, *q; //q用来指向当前节点
//创建四个队列，依次对应三种资源的就绪队列

int times  = 0;
typedef struct jcb JCB;

//资源插入作业
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

//作业进入就绪队列，并根据到达时间进行排序
void InsertJobs ( JCB* p, int t )
{
    if ( ready[t] == NULL )
        ready[t] = p;
    else
    {
        JCB *pt = ready[t];
        q = pt->next;
        //比队首元素来得早，就待在队首
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
//输入m个作业
void init ( int m )
{
    resource *ptr;
    int i, j;
    printf ( "请输入作业数" );
    printf ( "%d \n", m );
    for ( i = 0; i < m; i++ )
    {
        p = getpch ( JCB );
        //
        printf ( "输入作业名： " );
        scanf ( "%s", p->name );
        printf ( "\n输入作业到达时间" );
        scanf ( "%d", &p->reachtime );
        printf ( "\n输入作业所需资源的种类数:" );
        scanf ( "%d", &p->rnum );
        p->res = NULL;
        for ( j = 0; j < p->rnum; j++ )
        {
            ptr = ( resource* ) malloc ( sizeof ( resource ) );
            printf ( "\n\t输入资源名: " );
            scanf ( "%s", ptr->name );
            printf ( "\n\t输入所需资源的数量: " );
            scanf ( "%d", &ptr->num );
            printf ( "\n\t输入该作业消耗该资源的时间: " );
            scanf ( "%d", &ptr->usedTime );
            p->IsUsed = 1; //默认都使用
            ptr->link = NULL;
            InsertR ( p, ptr );
        }
        p->state = 'W';//W表示就绪状态
        p->next = NULL;
        InsertJobs   ( p, 0 ); //把p插入后备队列
    }
}
void Running(JCB *p, int j, resource *cre)
{
    printf("%s的调度结果：\n", cre[j].name);
    printf("作业名为：%s\n", p->name);
    printf("到达该资源的时间：%d\n", p->reachtime);
    p->reachtime = p->starttime+p->needtime;
    printf("释放该资源的时间%d\n",p->reachtime);
    InsertJobs(p, j+1);
}
//调度算法
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
            p->next = NULL;//脱离原队列
        }
        while ( p != NULL )
        {
            //寻找p中所含的资源数
            resource * ptr = p->res;
            while ( ptr != NULL && strcmp ( ptr->name, cre[j].name ) )
            {
                ptr = ptr->link;
            }
            //作业需要该资源数量目小于等于现存资源数或不需要该资源，则执行p
            if ( ptr != NULL && ptr->num <= cre[j].num )
            {
                //如果当前时刻小于到达时刻,则当前时刻应当到到达时刻才能运行
                if ( times <= p->reachtime )
                {
                    times = p->reachtime;
                }
                if ( ptr == NULL )
                {
                    p->starttime = times;
                    p->needtime = 0;
                    p->IsUsed = 0; //标志为不需要该资源
                    Running ( p, j, cre );
                }
                //需要该资源则应从系统资源中减去所需的数目
                else
                {
                    p->starttime = times;
                    p->needtime = ptr->usedTime;
                    cre[j].num -= ptr->num;
                    Running ( p, j, cre );
                }
                //执行下一个作业
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
                //找到第一个使用该资源的且未释放的进程q1
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
        times=0;//重设时间
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
    resource cre[3];//计算机资源
    //初始化计算机资源0为输入设备，1为cpu，2为输出设备
    //输入设备
    strcpy(cre[0].name, "INS");
    cre[0].num = 2;
    //CPU
    strcpy(cre[1].name, "CPU");
    cre[1].num = 4;
    //输出设备
    strcpy(cre[2].name, "OUTS");
    cre[2].num = 2;
    //初始化三个队列
    int id=0;
    for(id=0; id<4; id++)
        ready[id]=NULL;
    //输入m个作业
    printf("输入要输入的作业总数: ");
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

