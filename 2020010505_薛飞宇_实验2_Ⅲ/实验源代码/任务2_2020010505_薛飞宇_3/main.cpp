#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct JCB
{
    string ID;                                       //作业号
    int priority;                                            //优先级
    double begin_time;                               //提交时间
    double rtime;                                    //已经运行时间
    double turnaround_time;                          //周转时间
    double cpu_service_time;                         //占用CPU的时间
    double io_time;                                  //用于I/O的时间
    double finish_time;                              //完成时间
    double Wturnaround_time;                         //带权周转时间
    JCB& operator = (const JCB& p2)                 //重载 = 运算符，方便排序
    {
        this->priority = p2.priority;
        this->begin_time = p2.begin_time;
        this->rtime = p2.rtime;
        this->finish_time = p2.finish_time;
        this->cpu_service_time = p2.cpu_service_time;
        this->io_time = p2.io_time;
        this->ID = p2.ID;
        this->turnaround_time = p2.turnaround_time;
        this->Wturnaround_time = p2.Wturnaround_time;
        return *this;
    }
};

typedef struct
{
    JCB data[100];

}JCBk;

const double CPU = 10.0;
const double index = 0.5;
JCBk jcb,jcb_1;
int n,number;

void init()                                                        //初始化作业块
{
    cout<<"输入作业数量:";
    cin>>n;
    number = n;
    for(int i = 0; i<n; i++)
    {
        cout<<"作业名称:";
        cin>>jcb.data[i].ID;
        cout<<jcb.data[i].ID<<"开始时间:";
        cin>>jcb.data[i].begin_time;
        cout<<jcb.data[i].ID<<"服务时间:";
        cin>>jcb.data[i].cpu_service_time;
        cout<<jcb.data[i].ID<<"I/O时间:";
        cin>>jcb.data[i].io_time;
        cout<<jcb.data[i].ID<<"优先级:";
        cin>>jcb.data[i].priority;
        jcb.data[i].rtime = 0;
    }
    for(int i = 0; i<n-1; i++)                                    //按照优先级从大到小排序
    {
        for(int j = i+1; j<n; j++)
        {
            if(jcb.data[i].priority < jcb.data[j].priority)
                swap(jcb.data[i],jcb.data[j]);
        }
    }
    for(int i = 0; i<n-1; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            if(jcb.data[i].begin_time == jcb.data[j].begin_time && jcb.data[i].ID > jcb.data[j].ID)
                swap(jcb.data[i],jcb.data[j]);
        }
    }
}

void youxianji()                                                //优先级
{
    int j = 0;
    double running = CPU;
    double bt = jcb.data[0].begin_time;
    double gtt = 0;
    double gwtt = 0;
    double real_begin;
    double record = jcb.data[0].begin_time;
    int num = n-1;
    cout<<"作业名称     "<<"到达时间  "<<"开始时间  "<<"周转时间  "<<"结束时间  "<<"平均带权周转时间"<<endl;
    while(1)
    {
        if(jcb.data[j].cpu_service_time > CPU)
        {
            cout<<"超时!!!"<<endl;
            exit(0);
        }
        jcb.data[j].rtime += index;
        record += index;
        if(running >= 0)
        {
            if (jcb.data[j].rtime >= jcb.data[j].cpu_service_time)
            {
                real_begin = bt;
                jcb.data[j].finish_time = record + jcb.data[j].io_time;
                jcb.data[j].turnaround_time = jcb.data[j].finish_time - jcb.data[j].begin_time;
                jcb.data[j].Wturnaround_time = jcb.data[j].turnaround_time / jcb.data[j].rtime;
                cout<<jcb.data[j].ID<<"         "<<real_begin<<"                "
                <<jcb.data[j].begin_time<<"                  "<<jcb.data[j].turnaround_time
                <<"              "<<jcb.data[j].finish_time<<"                 "
                <<jcb.data[j].Wturnaround_time<<endl;
                n--;
                running -= jcb.data[j].cpu_service_time;
                bt = record;
                gtt += jcb.data[j].turnaround_time;
                gwtt += jcb.data[j].Wturnaround_time;
            }
            else
            {
                num++;
                swap(jcb.data[num],jcb.data[j]);
            }
        }
        else
        {
            running += jcb.data[j].cpu_service_time;
            num++;
            swap(jcb.data[num],jcb.data[j]);
        }
        if(n == 0)
            break;
        j++;
    }
    cout<<" 平均周转时间:"<<gtt/number<<endl<<"平均带权周转时间:"<<gwtt/number<<endl;
}


int main()
{
    init();
    youxianji();
    return 0;
}
