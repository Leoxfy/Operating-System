#include <stdio.h>
#include <stdlib.h>

struct Info
{
    int value;
    int count;
    int begin;
    int end;
};

void init(struct Info info[])
{
    int i;
    for(i=0; i<11; i++)
    {
        if(i == 0)  info[i].value = 1;
        else info[i].value = info[i-1].value*2;
        info[i].count = 0;
        info[i].begin = 0;
        info[i].end = 0;
    }
    info[10].count = 1;
    info[10].end = 1023;
}

void print(struct Info info[])
{
    int i,j;
    printf("|");
    for (i=0; i<11; i++){
    	if (info[10].count > 0){
    		printf("%d|",info[10].value);
    		break;
		}
    	if (info[i].count > 0){
    		printf("%d|",info[i].value);
		}else if(info[i+1].count > 0 && i!=9){
			printf("*|");
		}else if(i==9 && info[i].count == 0){
			printf("*|");
		}
	}
}

void buddy(struct Info info[], int num)
{
    int i, j, k;
    for(i=0; i<11; i++)
    {
        if(info[i].value >= num)
        {
            if(info[i].count == 1)
            {
                info[i].count = 0;
                printf("Allocate pages succefully!\n");
                return ;
            }
            else{
                for(j=i; j<11; j++)
                {
                    if(info[j].count == 1)
                    {
                        info[j].count = 0;             //把该页拆分开
                        for(k=i; k<j; k++)
                        {
                            info[k].count = 1;
                            info[k].begin = info[k].value;
                            info[k].end = info[k].begin*2 - 1;
                        }
                        printf("Allocate pages succefully!\n");
                        return ;
                    }
                    if(j == 10)
                    {
                        printf("Allocate pages failed!\n");
                        return ;
                    }
                }
            }
        }
    }
}

int main()
{
    int i, num;
    struct Info info[11];
    printf("Init:\n");
    init(info);

    print(info);
    while(1)
    {
        printf("\nPlease input a  num:");
        scanf("%d", &num);
        fflush(stdin);
        if(num > 1023)  printf("The num is too big , try littler\n");
        else
        {
            buddy(info, num);
            print(info);
        }
    }
    system("pause");
    return 0;
}
