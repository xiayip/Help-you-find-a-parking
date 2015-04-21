//
//  main.c
//  park
//
//  Created by xiayip's mac on 15/4/18.
//  Copyright (c) 2015年 xiayip's mac. All rights reserved.
//

#include <stdio.h>
#include "string.h"

int a[7] = {1,0,1,1,0,1,0};
int b[4] = {1,1,0,1};
int c[3] = {1,1,0};
int d[2] = {0,1};
int e[4] = {1,1,1,1};

int weight[5] = {1,3,5,2,4};//权重

int isHaveZero[5];

void IsZero(void);
void alter(int i,int j);
void search(void);

int main(void)
{
    char cmd[10]={0},grp=0;
    int pos;
    printf("当前入口：入口一\n车位情况：\nC区剩余：1 E区剩余：0 B区剩余：1 D区剩余：1 A区剩余：3\n请输入操作：\n");
    while (1) {
        IsZero();
        scanf("%s", cmd);
        if (strcmp(cmd,"search")==0) {
            printf("最佳车位为：\n");
            search();
        }else if (strcmp(cmd,"alter")==0){
            getchar();
            printf("转换状态的车位：\n");
            scanf("%c %d", &grp,&pos);
            alter(((int)grp)-97, pos-1);
            printf("成功");
        }
    }
    return 0;
}
void IsZero(void)
{
    int i=0;
    
    for(i=0;i<5;i++)
        isHaveZero[i] = 0;
    for(i=0;i<7;i++)
    {
        if(a[i] == 0)
            isHaveZero[0] = 1;
    }
    for(i=0;i<4;i++)
    {
        if(b[i] == 0)
            isHaveZero[1] = 1;
    }
    for(i=0;i<3;i++)
    {
        if(c[i] == 0)
            isHaveZero[2] = 1;
    }
    for(i=0;i<2;i++)
    {
        if(d[i] == 0)
            isHaveZero[3] = 1;
    }
    for(i=0;i<4;i++)
    {
        if(e[i] == 0)
            isHaveZero[4] = 1;
    }
}
void search(void)
{
    int tmp = -1,i,j = -1;
    for(i=0;i<5;i++)
    {
        if(isHaveZero[i])
        {
            if(tmp < weight[i])
            {
                tmp = weight[i];
                j=i;
            }
        }
    }
    switch(j)
    {
        case 0:
            for(i=0;i<=6;i++)
            {
                if(a[i]==0)
                {
                    printf("a%d\n",i+1);
                    break;
                }
            }
            break;
        case 1:
            for(i=0;i<=3;i++)
            {
                if(b[i]==0)
                {
                    printf("b%d\n",i+1);
                    break;
                }
            }
            break;
        case 2:
            for(i=0;i<=2;i++)
            {
                if(c[i]==0)
                {
                    printf("c%d\n",i+1);
                    break;
                }
            }
            break;
        case 3:
            for(i=0;i<=1;i++)
            {
                if(d[i]==0)
                {
                    printf("d%d\n",i+1);
                    break;
                }
            }
            break;
        case 4:
            for(i=0;i<=3;i++)
            {
                if(e[i]==0)
                {
                    printf("e%d\n",i+1);
                    break;
                }
            }
            break;
        default:
            break;
    }
}
void alter(int i,int j)
{
    switch(i)
    {
        case 0:
            a[j] = !a[j];
            break;
        case 1:
            b[j] = !b[j];
            break;
        case 2:
            c[j] = !c[j];
            break;
        case 3:
            d[j] = !d[j];
            break;
        case 4:
            e[j] = !e[j];
            break;
        default:
            break;
    }
}
