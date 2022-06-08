#include <stdio.h>
#include <stdlib.h>

#define n 4 //�α�ĳ���
//�α�
struct Parag
{
    int state;//�ε�״̬
    int length;//�εĳ���,��ʾ�м���ҳ��������һ��ҳռ��һ���ڴ�
    int PTID;//ҳ��ʼַ
}parag[4];

//ҳ��
struct Page
{
    int state;//״̬
    int MMID;//������
}page[100];

void print(int did, int ptid)
{
    int i;
    printf("�α����Ϣ��\n");
    printf("�κ�\t|״̬\t|�α��С\t|ҳ��ʼַ|\n");
    for(i=0; i < n; i++)
       printf("%d\t|%d\t|%d\t\t|%d\t|\n", i, parag[i].state, parag[i].length, parag[i].PTID);
    printf("���ñ����Ϣ��\n");
    printf("ҳ��\t|״̬\t|������|\n");
    for(i = ptid; i<ptid+parag[did].length; i++)
        printf("%d\t|%d\t|%d\t|\n", i-ptid, page[i].state, page[i].MMID);
}

void Init()
{
    int i, d=0;
  //��ʼ���α�
  for(i=0; i < n; i++)
  {
      parag[i].length=i+4;//�εĳ�������Ϊ4 5 6 7
      parag[i].state=1;
      parag[i].PTID=d;
      d+=parag[i].length;
  }
  //��ʼ��ҳ��
  for(i = 0; i < d; i++)
  {
      page[i].state=1;
      page[i].MMID=(i+7)%d;//ȷ��������
  }
}

void Transform(int DID, int PID, int Address)
{
    if(DID >= n)
     {
         printf("��Խ�磡\n");
         return;
     }
    if(parag[DID].length <= PID)
    {
        printf("ҳԽ��\n");
        return;
    }
    int ptid = parag[DID].PTID;
    int ptid2 = ptid+PID;
    int mmid = page[ptid2].MMID;
    int newAddress = 1024*mmid+Address;
    printf("ת��ǰ�ĵ�ַ���κţ�%d, ҳ�ţ�%d, ҳ�ڵ�ַ��%d\n",DID, PID, Address);
    print(DID,ptid);//��ʾ�α������ҳ�����Ϣ
    printf("ת����ĵ�ַΪ��%d", newAddress);
}


int main()
{
    int DID, PID, Address;
    Init();//��ʼ��ҳ��Ͷα�
    printf("������Ҫת���ĵ�ַ��\n");
    printf("������κţ�\n");
    scanf("%d",&DID);
    printf("������ҳ�ţ�\n");
    scanf("%d",&PID);
    printf("������ҳ�ڵ�ַ��\n");
    scanf("%d", &Address);
    Transform(DID, PID, Address);
    return 0;
}

