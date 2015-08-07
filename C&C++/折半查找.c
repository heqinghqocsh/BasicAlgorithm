//折半查找二种方法（非递归折半查找、递归折半查找）的细节对比程序

#include<stdio.h>
#include<windows.h>
 
#define arraymaxnum 21//约定数组大小,0号单元默认不用，故用户数据可以接受20个
#define defaultnum 10//约定默认数据数组大小，数据使用教材实际范例
int defaultdata[defaultnum]={0,12,22,36,48,52,56,64,76,83};//0号下标默认不用，故存0
int flag=0;//表示用户没有输入数据，使用默认数据
int count[2]={0,0};//存查找的次数

int halfsearching(int *data,int length,int seekdata);//非递归折半查找
int halfrsearching(int *data,int head,int tail,int seekdata);//递归折半查找,r:递归
void displaydata(int *data,int length);

//菜单显示
int workingdata[arraymaxnum]; 
int datanumber,searchdata;
void showmenu(void);
void processmenu(void);

/*……………………………………………………………………//
函 数 名:main
描    述:主函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
void main(void) //程序主入口
{
	system("color f0");
	system("cls");
	SetConsoleTitle("折半查找（C版）作者：heqinghqocsh");
    while (1)
	{
		showmenu();
		processmenu();
		system("pause");
		system("cls");
    }
}//主函数结束

/*……………………………………………………………………//
函 数 名:halfsearching
描    述:非递归折半查找
入口参数:目标数组，数组长度，要查找的数据
出口参数:目标数据的位置信息
//……………………………………………………………………*/
int halfsearching(int *data,int length,int seekdata)
{
	int low=1,high=length,flag=0,mid;
	while(low<=high)
	{
		mid=(low+high)/2;
		count[0]++;
		if(data[mid]==seekdata)//此处采用了数组下标地址的方法读取数据
		{
			flag=1;
			break;
		}
		else if(data[mid]>seekdata)
			high=mid-1;
		else
			low=mid+1;
	}
	if(flag==1)
		return mid;
	else
		return 0;
}

/*……………………………………………………………………//
函 数 名:halfrsearching
描    述:递归折半查找
入口参数:目标数组，头位置，尾位置，要查找的数据
出口参数:目标数据的位置信息
//……………………………………………………………………*/
int halfrsearching(int *data,int head,int tail,int seekdata)
{
	int mid=(tail+head)/2;
	count[1]++;
	if(tail<head)
		return 0;
	if(*(data+mid)==seekdata)//此处采用了数组名起始地址加上偏移量的方法读取数据
		return mid;
	else if(*(data+mid)<seekdata)
		return halfrsearching(data,mid+1,tail,seekdata);
	else
		return halfrsearching(data,head,mid-1,seekdata);
}

/*……………………………………………………………………//
函 数 名:displaydata
描    述:显示目标数组
入口参数:目标数组，数组长度
出口参数:无
//……………………………………………………………………*/
void displaydata(int *data,int length)//从坐标1开始显示到第number个数据
{
	int i;
	printf("坐标：");
	for(i=1;i<=length;i++)
		printf("%-5d",i);
	printf("\n");
	printf("数据：");
	for(i=1;i<=length;i++)
		printf("%-5d",data[i]);
	printf("\n");
}

/*……………………………………………………………………//
函 数 名:showmenu
描    述:菜单显示
入口参数:无
出口参数:无
//……………………………………………………………………*/
void showmenu()
{
	printf("  折半查找功能演示  \n");
   	printf("====================\n"); 
	printf("提示：直接选择进入3 \n"); 
	printf("      即使用默认数据\n"); 
	printf("====================\n"); 
	printf("1.键盘输入新数据    \n");
	printf("2.恢复使用默认数据  \n"); 
	printf("3.开始查找          \n"); 
	printf("0.结束程序          \n"); 
	printf("====================\n");
}

/*……………………………………………………………………//
函 数 名:processmenu
描    述:根据用户输入执行指定功能
入口参数:无
出口参数:无
//……………………………………………………………………*/
void processmenu()
{   
	int choice,position,i;
	printf("请输入选项：");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:
		do
		{
			printf("请输入数据个数：(不超过%d个)\n",arraymaxnum-1);
			scanf("%d",&datanumber);
		}while(datanumber>=arraymaxnum); 
		printf("请输入数据（注意必须越来越大）：\n");
		for(i=1;i<=datanumber;i++)
		{
			printf("请输入第 %d 个数据：\n",i);
			scanf("%d",&workingdata[i]);
			if(workingdata[i]<workingdata[i-1])
				do
				{
					printf("数据不符合要求，请重新输入本数据(注意数据必须递增)：\n");
					scanf("%d",&workingdata[i]);
				}while(workingdata[i]<workingdata[i-1]);
		}

		flag=1;//表示用户输入数据了
		printf("您输入的数据为：\n");
		printf("==============\n");
		displaydata(workingdata,datanumber);
		printf("==============\n");
		break;
	case 2:
		for(i=1;i<=defaultnum;i++)
			workingdata[i]=defaultdata[i];
		flag=0;//表示数据恢复了
		printf("==============\n");
		printf("默认数据已经恢复！\n");
		printf("==============\n");
		break;

	case 3:
		if(flag==0)//测试标志位
		{
			datanumber=defaultnum-1;
			for(i=1;i<=datanumber;i++)//把默认数据传输过来成为工作数据
				workingdata[i]=defaultdata[i];
			printf("本程序默认工作数据为：\n");
		}
		else
		{
			printf("用户输入的工作数据为：\n");
		}
		displaydata(workingdata,datanumber);
		printf("请输入您要找的数据：\n");
		scanf("%d",&searchdata);
		printf("==============\n");
		count[0]=count[1]=0;
		printf("查找结果如下：\n");
		//开始查找的过程
		position=halfsearching(workingdata,datanumber,searchdata);
		if(position)
			printf("折半非递归法查找成功。数据在 %2d 号位置上。比较次数 %d\n",position,count[0]);
		else
			printf("折半非递归法查找失败。\n");

		position=halfrsearching(workingdata,1,datanumber,searchdata);
		if(position)
			printf("折半递归方法查找成功。数据在 %2d 号位置上。比较次数 %d\n",position,count[1]);
		else
			printf("折半递归方法查找失败。\n");
		break;
	case 0:
		system("pause");
		exit(1);
	default: 
		printf("输入有错，请重新输入...\n");
	}
}
