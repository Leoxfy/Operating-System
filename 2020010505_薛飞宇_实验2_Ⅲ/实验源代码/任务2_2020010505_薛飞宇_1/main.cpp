#include<stdio.h>
#include<stdlib.h>
#define N 5

struct jcb
{
    char name[10];//�û�����
    int reachtime;//��ҵ�ִ�ʱ��
    int starttime;//��ҵ��ʼʱ��
    int needtime;//��ҵ��������ʱ��
    int finishtime;//��ҵ���ʱ��
    float cycletime;//��ҵ��תʱ��
    float cltime;//��Ȩ��תʱ��
    char state;//��ҵ״̬
    struct jcb *next;//�ṹ��ָ��
    int Rp;//��Ӧ�ȡ�����Ӧʱ��/Ҫ�����ʱ��
    int waittime;//�ȴ�ʱ��
}*ready = NULL, *p, *q;

int main()

{
         int a[2][5]={0};  //a[0][i]��ŵ����ʱ�䣬a[1][i]�����Ҫ�ķ���ʱ��

         int d[5]={0};

         int h[5]={0,1,2,3,4};

         double b[4][6]={0};  //FCFS

         double n[4][6]={0};  //SJF

         double m[4][6]={0};  //�����Ӧ������

         double c[5];    //�����Ӧ��

         double ha[5];   //��ŷ���ʱ��������Ӧ������

         int i=0,j=0,t;

         int temp;

         int r,z;

         printf("�������:\tA\tB\tC\tD\tE\n");

   printf("����ʱ��:\t");

         for(i=0;i<N;i++)

         {

                   a[0][i]=i;     //����ʱ��

                   printf("%d\t",a[0][i]);

         }

         printf("\n");

         printf("���������ʱ��:\t");

   for(i=0;i<N;i++)

         {
             scanf("%d",&a[1][i]);  //����ʱ��

         }

         printf("����ʱ��:\t");

         for(i=0;i<N;i++)

         {

                    d[i]=a[1][i];    //�ѷ���ʱ��˳���ŵ�d������

                  printf("%d\t",a[1][i]);

         }

         printf("\n");

   /*�����ȷ���*/

   printf("FCFS\n");

   printf("��ʼʱ��:\t");

         b[0][0]=a[0][0];

                   printf("%d\t",b[0][0]);

   for(i=1;i<N;i++)

    {
           b[0][i]=b[0][i-1]+(double)(a[1][i-1]);

     printf("%d\t",(int)b[0][i]);//b[0][i]��ŵ��Ǹ����̿�ʼʱ��

         }

         printf("\n");

         b[1][0]=(double)a[1][0];

   printf("���ʱ��:\t%d\t",(int)b[1][0]); //b[1][i]��ŵ������ʱ��

   for(i=1;i<N;i++)

    {
           b[1][i]=b[0][i]+(double)a[1][i];

     printf("%d\t",(int)b[1][i]);

         }

         printf("\n");

   printf("��תʱ��:\t");

   for(i=0;i<N;i++)

    {
     b[2][i]=b[1][i]-(double)a[0][i];

           b[2][5]+=b[2][i];   //b[2][5]��תʱ���ۼӺ�

     printf("%d\t",(int)b[2][i]); //b[2][i]��ŵ�����תʱ��

         }

         printf("arve=%.2f\n",b[2][5]/5);

         printf("��Ȩ��תʱ��:\t");

   for(i=0;i<N;i++)

    {
           b[3][i]=b[2][i]/(double)(a[1][i]);

           b[3][5]+=b[3][i];  //b[3][5]��Ȩ��תʱ���ۼӺ�

     printf("%.1f\t",(double)b[3][i]);//b[3][i]��ŵ��Ǵ�Ȩ��תʱ��

         }

         printf("avre=%.2f\n",b[3][5]/5);

   /*����ҵ����*/

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

                            }                //h[i]��Ϊ���̷����˳��   for(i=0;i<5;i++)printf("%d\t",h[i]);

         printf("��ʼʱ��:\t");

   for(i=1;i<N;i++)

         {
                   n[0][h[i]]=a[1][h[i-1]]+n[0][h[i-1]];

         }

         for(i=0;i<N;i++)

           printf("%d\t",(int)n[0][i]);

     printf("\n");

         printf("���ʱ��:\t");

         n[1][0]=a[1][0];

         for(i=1;i<N;i++)

            n[1][h[i]]=n[0][h[i]]+a[1][h[i]];

  for(i=0;i<N;i++)

           printf("%d\t",(int)n[1][i]);

     printf("\n");

       printf("��תʱ��:\t");

         //n[2][0]=n[1][0]-a[0][0];//�տ�ʼ������ִ�е�һ������

         for(i=0;i<N;i++)

            n[2][i]=n[1][i]-a[0][i];

   for(i=0;i<N;i++)

         {
           n[2][5]+=n[2][i];  //����תʱ��

           printf("%d\t",(int)n[2][i]);

    }

     printf("avre=%.2f\n",n[2][5]/5);

   printf("��Ȩ��תʱ��\t");

         for(i=0;i<N;i++)

            n[3][i]=n[2][i]/a[1][i];

  for(i=0;i<N;i++)

  {

            n[3][5]+=n[3][i];  //�ܴ�Ȩ��תʱ��

            printf("%.1f\t",n[3][i]);

   }

     printf("avre=%.2f\n",n[3][5]/5);

   /*�����Ӧ������*/

   printf("HRN:\n");

          for(i=1;i<N;i++)

       {
          ha[i]=a[1][i];//a[1][i]����ʱ�䣬ha[i]������������Ӧ��

        }

      m[0][0]=0;  //��ʼʱ��

      m[1][0]=a[1][0];

      r=0;

     for(int X=1;X<N;X++)

      {
        for(i=1;i<N;i++)

         {
              if(ha[i]!=0)

                 c[i]=1+(double)(m[1][r]-a[0][i])/a[1][i];//c[i]���ڴ����Ӧ��

           else

              c[i]=0;

         }

                  z=1;

               for(j=1;j<N;j++) //ѡ��ÿ����ߵ���Ӧ��

                     {
                 if(c[z]<=c[j]&&ha[j]!=0)

                  z=j;

                     }

                 ha[z]=0;

                 m[0][z]=m[1][r];

                 m[1][z]=m[0][z]+a[1][z];

                 r=z;

           }

              printf("��ʼʱ��:\t");

        for(i=0;i<N;i++)

             printf("%d\t",(int)m[0][i]);

                    printf("\n");

        printf("���ʱ��:\t");

        for(i=0;i<N;i++)

             printf("%d\t",(int)m[1][i]);

        printf("\n");

                    printf("��תʱ��\t");

        for(i=0;i<N;i++)

                    {
                             m[2][i]=m[1][i]-a[0][i];

                             m[2][5]+=m[2][i];  //m[2][5]��תʱ���ۼӺ�

                             printf("%d\t",(int)m[2][i]);

                    }

                    printf("aver=%.2f\n",m[2][5]/5);

                    printf("��Ȩ��תʱ��\t");

        for(i=0;i<N;i++)

                    {
                             m[3][i]=m[2][i]/a[1][i];

                             m[3][5]+=m[3][i];

                             printf("%.1f\t",m[3][i]);

                    }

                    printf("aver:%.2f\n",m[3][5]/5);

}
