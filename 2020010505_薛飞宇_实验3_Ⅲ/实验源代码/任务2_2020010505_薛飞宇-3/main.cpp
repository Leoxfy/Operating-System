#include <stdio.h>
#include <stdlib.h>

#define n 4 //段表的长度
//段表
struct Parag
{
    int state;//段的状态
    int length;//段的长度,表示有几个页，并假设一个页占用一个内存
    int PTID;//页表始址
}parag[4];

//页表
struct Page
{
    int state;//状态
    int MMID;//物理块号
}page[100];

void print(int did, int ptid)
{
    int i;
    printf("段表的信息：\n");
    printf("段号\t|状态\t|段表大小\t|页表始址|\n");
    for(i=0; i < n; i++)
       printf("%d\t|%d\t|%d\t\t|%d\t|\n", i, parag[i].state, parag[i].length, parag[i].PTID);
    printf("所用表的信息：\n");
    printf("页号\t|状态\t|物理块号|\n");
    for(i = ptid; i<ptid+parag[did].length; i++)
        printf("%d\t|%d\t|%d\t|\n", i-ptid, page[i].state, page[i].MMID);
}

void Init()
{
    int i, d=0;
  //初始化段表
  for(i=0; i < n; i++)
  {
      parag[i].length=i+4;//段的长度依次为4 5 6 7
      parag[i].state=1;
      parag[i].PTID=d;
      d+=parag[i].length;
  }
  //初始化页表
  for(i = 0; i < d; i++)
  {
      page[i].state=1;
      page[i].MMID=(i+7)%d;//确定物理块号
  }
}

void Transform(int DID, int PID, int Address)
{
    if(DID >= n)
     {
         printf("段越界！\n");
         return;
     }
    if(parag[DID].length <= PID)
    {
        printf("页越界\n");
        return;
    }
    int ptid = parag[DID].PTID;
    int ptid2 = ptid+PID;
    int mmid = page[ptid2].MMID;
    int newAddress = 1024*mmid+Address;
    printf("转换前的地址：段号：%d, 页号：%d, 页内地址：%d\n",DID, PID, Address);
    print(DID,ptid);//显示段表和所用页表的信息
    printf("转换后的地址为：%d", newAddress);
}


int main()
{
    int DID, PID, Address;
    Init();//初始化页表和段表
    printf("请输入要转换的地址：\n");
    printf("请输入段号：\n");
    scanf("%d",&DID);
    printf("请输入页号：\n");
    scanf("%d",&PID);
    printf("请输入页内地址：\n");
    scanf("%d", &Address);
    Transform(DID, PID, Address);
    return 0;
}

