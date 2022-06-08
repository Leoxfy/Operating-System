#include<stdio.h>
#include<stdlib.h>
#define N 5

struct jcb
{
    char name[10];//用户名称
    int reachtime;//作业抵达时间
    int starttime;//作业开始时间
    int needtime;//作业运行所需时间
    int finishtime;//作业完成时间
    float cycletime;//作业周转时间
    float cltime;//带权周转时间
    char state;//作业状态
    struct jcb *next;//结构体指针
    int Rp;//响应比——响应时间/要求服务时间
    int waittime;//等待时间
}*ready = NULL, *p, *q;

int main()

{
         int a[2][5]={0};  //a[0][i]存放到达的时间，a[1][i]存放需要的服务时间

         int d[5]={0};

         int h[5]={0,1,2,3,4};

         double b[4][6]={0};  //FCFS

         double n[4][6]={0};  //SJF

         double m[4][6]={0};  //最高相应比优先

         double c[5];    //存放响应比

         double ha[5];   //存放服务时间用于响应比排序

         int i=0,j=0,t;

         int temp;

         int r,z;

         printf("五个进程:\tA\tB\tC\tD\tE\n");

   printf("到达时间:\t");

         for(i=0;i<N;i++)

         {

                   a[0][i]=i;     //到达时间

                   printf("%d\t",a[0][i]);

         }

         printf("\n");

         printf("请输入服务时间:\t");

   for(i=0;i<N;i++)

         {
             scanf("%d",&a[1][i]);  //服务时间

         }

         printf("服务时间:\t");

         for(i=0;i<N;i++)

         {

                    d[i]=a[1][i];    //把服务时间顺便存放到d数组中

                  printf("%d\t",a[1][i]);

         }

         printf("\n");

   /*先来先服务*/

   printf("FCFS\n");

   printf("开始时间:\t");

         b[0][0]=a[0][0];

                   printf("%d\t",b[0][0]);

   for(i=1;i<N;i++)

    {
           b[0][i]=b[0][i-1]+(double)(a[1][i-1]);

     printf("%d\t",(int)b[0][i]);//b[0][i]存放的是各进程开始时间

         }

         printf("\n");

         b[1][0]=(double)a[1][0];

   printf("完成时间:\t%d\t",(int)b[1][0]); //b[1][i]存放的是完成时间

   for(i=1;i<N;i++)

    {
           b[1][i]=b[0][i]+(double)a[1][i];

     printf("%d\t",(int)b[1][i]);

         }

         printf("\n");

   printf("周转时间:\t");

   for(i=0;i<N;i++)

    {
     b[2][i]=b[1][i]-(double)a[0][i];

           b[2][5]+=b[2][i];   //b[2][5]周转时间累加和

     printf("%d\t",(int)b[2][i]); //b[2][i]存放的是周转时间

         }

         printf("arve=%.2f\n",b[2][5]/5);

         printf("带权周转时间:\t");

   for(i=0;i<N;i++)

    {
           b[3][i]=b[2][i]/(double)(a[1][i]);

           b[3][5]+=b[3][i];  //b[3][5]带权周转时间累加和

     printf("%.1f\t",(double)b[3][i]);//b[3][i]存放的是带权周转时间

         }

         printf("avre=%.2f\n",b[3][5]/5);

   /*短作业优先*/

   printf("SJF\n");

   for(i=1;i<N;i++)

                   for(j=i+1;j<N;j++)

                            if(d[i]>d[j])

                            {
                              t=d[j];

                              d[j]=d[i];

                              d[i]=t;



                              temp=h[j];

                              h[j]=h[i];

                              h[i]=temp;

                            }                //h[i]即为进程服务的顺序   for(i=0;i<5;i++)printf("%d\t",h[i]);

         printf("开始时间:\t");

   for(i=1;i<N;i++)

         {
                   n[0][h[i]]=a[1][h[i-1]]+n[0][h[i-1]];

         }

         for(i=0;i<N;i++)

           printf("%d\t",(int)n[0][i]);

     printf("\n");

         printf("完成时间:\t");

         n[1][0]=a[1][0];

         for(i=1;i<N;i++)

            n[1][h[i]]=n[0][h[i]]+a[1][h[i]];

  for(i=0;i<N;i++)

           printf("%d\t",(int)n[1][i]);

     printf("\n");

       printf("周转时间:\t");

         //n[2][0]=n[1][0]-a[0][0];//刚开始总是先执行第一个来的

         for(i=0;i<N;i++)

            n[2][i]=n[1][i]-a[0][i];

   for(i=0;i<N;i++)

         {
           n[2][5]+=n[2][i];  //总周转时间

           printf("%d\t",(int)n[2][i]);

    }

     printf("avre=%.2f\n",n[2][5]/5);

   printf("带权周转时间\t");

         for(i=0;i<N;i++)

            n[3][i]=n[2][i]/a[1][i];

  for(i=0;i<N;i++)

  {

            n[3][5]+=n[3][i];  //总带权周转时间

            printf("%.1f\t",n[3][i]);

   }

     printf("avre=%.2f\n",n[3][5]/5);

   /*最高相应比优先*/

   printf("HRN:\n");

          for(i=1;i<N;i++)

       {
          ha[i]=a[1][i];//a[1][i]服务时间，ha[i]用于排序找响应比

        }

      m[0][0]=0;  //开始时间

      m[1][0]=a[1][0];

      r=0;

     for(int X=1;X<N;X++)

      {
        for(i=1;i<N;i++)

         {
              if(ha[i]!=0)

                 c[i]=1+(double)(m[1][r]-a[0][i])/a[1][i];//c[i]用于存放响应比

           else

              c[i]=0;

         }

                  z=1;

               for(j=1;j<N;j++) //选出每次最高的响应比

                     {
                 if(c[z]<=c[j]&&ha[j]!=0)

                  z=j;

                     }

                 ha[z]=0;

                 m[0][z]=m[1][r];

                 m[1][z]=m[0][z]+a[1][z];

                 r=z;

           }

              printf("开始时间:\t");

        for(i=0;i<N;i++)

             printf("%d\t",(int)m[0][i]);

                    printf("\n");

        printf("完成时间:\t");

        for(i=0;i<N;i++)

             printf("%d\t",(int)m[1][i]);

        printf("\n");

                    printf("周转时间\t");

        for(i=0;i<N;i++)

                    {
                             m[2][i]=m[1][i]-a[0][i];

                             m[2][5]+=m[2][i];  //m[2][5]周转时间累加和

                             printf("%d\t",(int)m[2][i]);

                    }

                    printf("aver=%.2f\n",m[2][5]/5);

                    printf("带权周转时间\t");

        for(i=0;i<N;i++)

                    {
                             m[3][i]=m[2][i]/a[1][i];

                             m[3][5]+=m[3][i];

                             printf("%.1f\t",m[3][i]);

                    }

                    printf("aver:%.2f\n",m[3][5]/5);

}
