
//功能：完成从键盘录入数据，然后从小到大排序输出。
//思路:利用函数readkeyboarddata(int data[],int length)完成输入，利用
// 函数 directinsertsorting(int data[],int length)完成排序功能。
//程序行数：100左右

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 21  //数组大小预定义

void showMenu();                            //显示菜单
void readkeyboarddata(int data[],int length);//从键盘读入数据
void directinsertsorting(int data[],int length);//直接插入排序函数

/*……………………………………………………………………//
函 数 名:main（）
描    述:主函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
int main()
{
	int i,data[MAXSIZE],choose;
	int length;//线性表长度
	while(1)
	{
		system("cls");
		showMenu();
		printf("请选择功能编号:\n");
		scanf("%d",&choose);
		switch(choose)
		{
		case 1:
			printf("请输入要排序的数据个数：(注意不超过%d个)\n",MAXSIZE-1);
			scanf("%d",&length);
			if(length>20)
			{
				printf("你输入的个数超过最大限制\n",length);
				system("pause");
				continue;
			}
			printf("请开始输入数据，一共%d个数据，请用空格分开：\n",length);
			readkeyboarddata(data,length);
			directinsertsorting(data,length);
			printf("排序后为： \n");
			for(i=1;i<=length;i++)
				printf("%d  ",data[i]);
			printf("\n");
			system("pause");
			break;
		case 2:
			return 0;
		}	

	}
}

/*……………………………………………………………………//
函 数 名:showMenu
描    述:显示功能菜单
入口参数:无
出口参数:无
//……………………………………………………………………*/
void showMenu()
{
	printf("                ===========================\n");
	printf("                直接插入排序法\n");
	printf("                作者：heqinghqocsh\n");
	printf("                ===========================\n");
	printf("                1.输入数据并完成排序\n");
	printf("                2.退出程序\n");
	printf("                ===========================\n");
}

/*……………………………………………………………………//
函 数 名:readkeyboarddata
描    述:从键盘录入数据
入口参数:数组名，线性表长度
出口参数:无
//……………………………………………………………………*/
void readkeyboarddata(int data[],int length)     //从键盘读入数据
{
	int i;
	for(i=1;i<=length;i++)//空置0单元所以要用 <=
		scanf("%d",&data[i]);
}

/*……………………………………………………………………//
函 数 名:directinsertsorting
描    述:完成元素的排序
入口参数:数组名，线性表长度
出口参数:无
//……………………………………………………………………*/
void directinsertsorting(int data[],int length)  //直接插入排序函数
{
	int term;//指向未排数据的首位置
	int i,j,item;
	for(term=1;term<=length;term++)
	{
		for(i=1;i<term;i++)
			if(data[i]>data[term])
			{
				item=data[term];
				for(j=term;j>i;j--)//将较小的数据移到前面
					data[j]=data[j-1];
				data[i]=item;
				break ;
			}
	}
}