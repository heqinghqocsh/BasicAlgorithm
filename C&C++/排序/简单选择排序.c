//功能：完成从键盘录入数据，然后从小到大排序输出。
//思路:利用函数display(int data[],int length)完成显示，利用
// 函数 simpleselectsort(int data[],int length)完成排序功能。
//程序行数：60左右

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 11  //数组大小预定义,空置0单元


void simpleselectsort(int data[],int length);//简单选择排序函数
void display(int data[],int length);//遍历所有数据

/*……………………………………………………………………//
函 数 名:main（）
描    述:主函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
int main()
{
	int i,data[MAXSIZE]={0,12,9,25,19,3,58,62,34,85,70};//默认数据，空置0单元
	printf("简单选择排序函数：heqinghqocsh\n\n");
	printf("已从内部数组创建好10个数据.\n排序前：\n");
	display(data,MAXSIZE);
	simpleselectsort(data,MAXSIZE);
	printf("排序后为： \n");
	display(data,MAXSIZE);
	system("pause");
	return 0;	
	
}

/*……………………………………………………………………//
函 数 名:display
描    述:遍历所有数据
入口参数:数组名，线性表长度
出口参数:无
//……………………………………………………………………*/
void display(int data[],int length)//遍历所有数据
{
	int i;
	for(i=1;i<length;i++)
	{
		printf("%d  ",data[i]);
	}
	printf("\n");
}

/*……………………………………………………………………//
函 数 名:simpleselectsort
描    述:完成元素的排序
入口参数:数组名，线性表长度
出口参数:无
//……………………………………………………………………*/
void simpleselectsort(int data[],int length)  //直接插入排序函数
{
	int term;//指向未排数据的首位置
	int i,j,item;
	for(term=1;term<length;term++)
	{
		item=data[term];
		for(i=term;i<length;i++)
			if(data[i]<=item)
			{
				item=data[i];//保留未排数据最小数据
				j=i;          //保留未排数据最小数据的位置
			}
			data[j]=data[term];
			data[term]=item;
	}
}