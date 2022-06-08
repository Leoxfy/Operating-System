#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

int Available[10];           //��ʹ����Դ����
int Max[10][10];             //����������
int Allocation[10][10] = { 0 };      //�������
int Need[10][10] = { 0 };            //�������
int Work[10];                   //��������
int Finish[10];                  //�Ƿ����㹻����Դ���䣬״̬��־
int Request[10][10];         //����������Դ����
int Pause[10];
int arr[] = { 0 };        //������Դ����
int List[10];
int i, j;
int n;                       //ϵͳ��Դ����
int m;                       //�ܵĽ�����
int a;                       //��ǰ����Ľ��̺�
int l, e;                     //������
int b = 0, c = 0, f = 0, g;           //������
int z = 0;

int  securitycheck()     //��ȫ�Լ��
{
    printf("\n\n");
    printf("\t\t\t�� ��ȫ�Լ�� ��\n\n");
    if (n == 3)
    {
        printf("          ��������       ��������       �ѷ���      ��������+�ѷ���\n���� ");
        for (c = 1; c <= 4; c++)
        {
            for (j = 1; j <= n; j++)
            {
                printf("  %d��", j);
            }
        }
    }
    if (n == 2)
    {
        printf("       ��������   ��������  �ѷ���  ��������+�ѷ���\n���� ");
        for (c = 1; c <= 4; c++)
        {
            for (j = 1; j <= n; j++)
            {
                printf("  %d��", j);
            }
        }
    }
    for (i = 1; i <= m; i++)
    {
        Pause[i] = Available[i];    //Pause[i]ֻ��һ����ʱ�Ĵ���м������Ϊ��ֹ�����氲ȫ�Լ��ʱ�޸ĵ�Available[i]�������һά����
        Finish[i] = false;
    }
    for (g = 1; g <= m; g++)
    {
        for (i = 1; i <= m; i++)
        {
            b = 0;                 //��������ʼ��
            Finish[i] == false;
            for (j = 1; j <= n; j++)
            {
                if (Need[i][j] <= Pause[j])
                {
                    b = b + 1;
                }
                if (Finish[i] == false && b == n)
                {
                    Finish[i] = true;
                    printf("\nP[%d] ", i);        //����������̰�ȫ����
                    for (l = 1; l <= n; l++)
                    {
                        printf("  %2d ", Pause[l]);
                    }
                    for (j = 1; j <= n; j++)
                    {
                        printf("  %2d ", Need[i][j]);
                    }
                    for (j = 1; j <= n; j++)
                    {
                        //Allocation[i][j]=Pause[j]-Need[i][j];
                        printf("  %2d ", Allocation[i][j]);
                    }
                    for (j = 1; j <= n; j++)
                    {
                        printf("  %2d ", Pause[j] + Allocation[i][j]);
                    }
                    for (l = 1; l <= n; l++)
                    {
                        Pause[l] = Pause[l] + Allocation[i][l];
                    }
                }
            }
        }
    }

    printf("\n\n");
    for (i = 1; i <= m; i++)
    {
        if (Finish[i] == true) f = f + 1;             //ͳ��Finish[i]����true�ĸ���
    }
    if (f == m)
    {
        printf("safe state");
        printf("\n\nϵͳʣ����Դ����   ");
        for (i = 1; i <= n; i++)
        {
        printf("   %d ", Available[i]);
        }
        f = 0;       //��������f���³�ʼ����Ϊ��һ������µĽ���������׼��
        return 1;
    }
    else
    {
        printf("unsafe state ");
        for (i = 1; i <= n; i++)
        {
            Available[i] = Available[i] + Request[a][i];
            Allocation[a][i] = Allocation[a][i] - Request[a][i];
            Need[a][i] = Need[a][i] + Request[a][i];
        }
        return 0;
    }

}

void initialize()    //��ʼ��
{
    printf("������ϵͳ����Դ��������");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        printf("��%d����Դ������", i);
        scanf("%d", &arr[i]);
    }
    printf("���������������");
    scanf("%d", &m);
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf("����P[%d]�Ե�%d����Դ�������������", i, j);
            scanf("%d", &Max[i][j]);
        }
    }
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf("����P[%d]�Ե�%d����Դ�ѷ�������", i, j);
            scanf("%d", &Allocation[i][j]);
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            arr[i] -= Allocation[j][i];
        }
    }
    for (i = 1; i <= n; i++)
        Available[i] = arr[i];
    securitycheck();
}

void mainrequest()  //����������Դ
{
    printf("������������Դ�Ľ��̣�");
    scanf("%d", &a);
    for (i = 1; i <= n; i++)
    {
        printf("���������P[%d]��%d����Դ����������", a, i);
        scanf("%d", &Request[a][i]);
        if (Request[a][i] > Need[a][i])
        {
            printf("\n���������������Դ���������Լ��걨�����������\n");
            return;
        }
        if (Request[a][i] > Available[i])
        {
            printf("\nP[%d]�������Դ�����ڿ�����Դ��������ȴ�\n", a);
            return;
        }

    }
    for (i = 1; i <= n; i++)
    {
        //��������̽�Է���
        Available[i] = Available[i] - Request[a][i];
        Allocation[a][i] = Allocation[a][i] + Request[a][i];
        Need[a][i] = Need[a][i] - Request[a][i];
    }
    int ret=securitycheck();
    if (ret == 1)
    {
        int key = 0;
        for (j = 1; j <= n; j++)
        {
            if (Need[a][j] == 0)
            {
                key++;
            }
        }
        if (key == n)
        {
            for (j = 1; j <= n; j++)
            {
                Available[j] += Allocation[a][j];
                Allocation[a][j] = 0;
            }
        }
    }
}

void mainshow()
{
    printf("\n\n");
    if (n == 3)
    {
        printf("          �ѷ���       ���������       ����Ҫ�� \n����");
    }
    if (n == 2)
    {
        printf("       �ѷ���   �������  ����Ҫ�� \n����");
    }
    for (i = 1; i <= 3; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf("  %d��", j);
        }
    }
    for (i = 1; i <= m; i++)
    {
        printf("\nP[%d]", i);
        for (j = 1; j <= n; j++)
        {
            printf("  %2d ", Allocation[i][j]);
        }
        for (j = 1; j <= n; j++)
        {
            printf("  %2d ", Max[i][j]);
        }
        for (j = 1; j <= n; j++)
        {
            printf("  %2d ", Need[i][j]);
        }
    }
    printf("\n\nϵͳʣ����Դ����   ");
    for (i = 1; i <= n; i++)
    {
        printf("   %d ", Available[i]);
    }
    printf("\n");
}

void menu()
{
    printf("\n\n\t\t�e�d����    ���м��㷨    ����e�d\n");
    printf("\n\n\t\t\t1:��ʼ��");
    printf("\n  \t\t\t2:���̽�����Դ����");
    printf("\n  \t\t\t3:��Դ����״̬");
    printf("\n  \t\t\t4:�˳�����");
    printf("\n\n\t\t\t\t\t ���������ѡ��: ");
}
int main()
{
    int key = 0;
    printf("\n\n");
    while (1)
    {
        menu();
        scanf("%d", &key);
        printf("\n\n");
        switch (key)
        {
        case 1:
            initialize();
            break;
        case 2:
            mainrequest();
            break;
        case 3:
            mainshow();
            break;
        case 4:
            printf("\n\n\t\t\tллʹ�� \n");
            printf("\n\t\t\tSee you next time !\n\n\n");
            system("pause");
            return 0;
        }

    }
    system("pause");
    return 0;
}
