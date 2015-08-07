//顺序查找三种方法（从左到右、从右到左、带哨兵元素）的细节对比程序

#include<stdio.h>
#include<windows.h>

#define datawidth 5     //设置数据显示宽度
#define arraymaxnum 21  //约定数组大小,0号单元默认不用，故用户数据可以接受20个
#define defaultnum  13  //约定默认数据数组大小，数据使用教材实际范例
int defaultdata[defaultnum]={0,32,10,41,60,24,82,60,90,45,60,23,75};//0号下标默认不用，故存0
int flag=0;             //表示用户没有输入数据，使用默认数据



int  ltorsearching(int *data,int length,int seekdata);//l:left左 r:right右 to:到
int  rtolsearching(int *data,int length,int seekdata);
int guardsearching(int *data,int length,int seekdata);//哨兵元素查找法
void   displaydata(int *data,int length             );

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
	SetConsoleTitle("顺序查找（C版）作者：heqinghqocsh");
    while (1)
	{
		showmenu();
		processmenu();
		system("pause");
		system("cls");
    }
}//主函数结束

/*……………………………………………………………………//
函 数 名:ltorsearching
描    述:从左到右查找
入口参数:目标数组，数组长度，要查找的数据
出口参数:数据的位置信息
//……………………………………………………………………*/
int ltorsearching(int *data,int length,int seekdata)
{
	int i=1;//从左到右时，开始查找的下标为1
	while(i<=length && data[i]!=seekdata)//两个条件为：当没有找完而且没有找到时一直循环
		i++;
	if(i<=length)//如果是正常范围内结束，说明找到了，否则说明查找失败
		return i;
	else
		return 0;
}

/*……………………………………………………………………//
函 数 名:rtolsearching
描    述:从右到左查找
入口参数:目标数组，数组长度，要查找的数据
出口参数:数据的位置信息
//……………………………………………………………………*/
int rtolsearching(int *data,int length,int seekdata)
{
	int i=length;//从右到左时，开始查找的下标为length
	while(i>0 && data[i]!=seekdata)
		i--;
	if(i>=1)
		return i;
	else
		return 0;
}

/*……………………………………………………………………//
函 数 名:guardsearching
描    述:哨兵查找
入口参数:目标数组，数组长度，要查找的数据
出口参数:数据的位置信息
//……………………………………………………………………*/
int guardsearching(int *data,int length,int seekdata)
{
	int i=length;//哨兵查找
	data[0]=seekdata;
	while(data[i]!=seekdata)//此算法的优点，把两个条件改成了一个，减少了逻辑运算量	
		i--;
	return i;
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
描    述:显示菜单
入口参数:无
出口参数:无
//……………………………………………………………………*/
void showmenu(void)
{
	printf("  顺序查找功能演示  \n");
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
		printf("请输入数据（空格隔开）：\n");
		for(i=1;i<=datanumber;i++)
			scanf("%d",&workingdata[i]);
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
		printf("查找结果如下：\n");
		//开始查找的过程
		position=ltorsearching(workingdata,datanumber,searchdata);
		if(position)
			printf("从左到右查找成功。数据在 %-2d 号位置上。\n",position);
		else
			printf("从左到右查找法查找失败。\n");
		position=rtolsearching(workingdata,datanumber,searchdata);
		if(position)
			printf("从右到左查找成功。数据在 %-2d 号位置上。\n",position);
		else
			printf("从右到左查找法查找失败。\n");
		position=guardsearching(workingdata,datanumber,searchdata);
		if(position)
			printf("用哨兵法查找成功。数据在 %-2d 号位置上。\n",position);
		else
			printf("用哨兵查找法法查找失败。\n");
		printf("==============\n");
		break;
	case 0:
		system("pause");
		exit(1);
	default: 
		printf("输入有错，请重新输入...\n");
	}
}
