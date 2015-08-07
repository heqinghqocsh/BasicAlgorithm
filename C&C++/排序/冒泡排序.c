//功能：通过计算机随机产生数据，然后从小到大排序输出。
//思路:利用函数display(int data[],int length)完成显示，利用
// 函数 bubblesort(int data[],int length)完成排序功能。
//程序行数：80左右

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 11  //数组大小预定义,空置0单元


void bubblesort(int data[],int length);//冒泡排序函数
void generaterandomdata(int data[],int length);//产生随机数据
void display(int data[],int length);//遍历所有数据

/*……………………………………………………………………//
函 数 名:main（）
描    述:主函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
int main()
{
	int i,data[MAXSIZE];
	char choose;
	while(1)
	{
		system("cls");
		printf("简单选择排序函数：作者 heqinghqocsh\n\n");
		printf("系统将自动产生10个11到99之间的数据\n");
		generaterandomdata(data,MAXSIZE);
		printf("系统产生的数据在排序前：\n");
		display(data,MAXSIZE);
		bubblesort(data,MAXSIZE);
		printf("排序后为： \n");
		display(data,MAXSIZE);
		printf("是否继续（Y/N）？");
		scanf("%c",&choose);
		fflush(stdin);//“吃掉”回车键
		if(choose!='Y'&&choose!='y')
			break;
	}
	return 0;
}

/*……………………………………………………………………//
函 数 名:display
描    述:遍历所有数据
入口参数:数组名，线性表长度
出口参数:无
//……………………………………………………………………*/
void generaterandomdata(int data[],int length)//产生随机数据
{
	int i;
	for(i=1;i<length;i++)
		data[i]=rand()%88+11;//由系统随机产生10个11到99之间的数据
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
void bubblesort(int data[],int length)  //冒泡排序函数
{
	int i,item,term;
	for(term=1;term<length-1;term++)//空置0单元,下标从1开始
	{
		for(i=1;i<length-term;i++)//在每一趟比较中进行10-term次两两比较
			if(data[i]>data[i+1])//相邻两个数比较
			{
				item=data[i];//交换数据
				data[i]=data[i+1];
				data[i+1]=item;
			}
	}
}