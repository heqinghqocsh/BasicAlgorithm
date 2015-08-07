//功能：常规的循环结构（loop）来求解斐波那契数列的某个值

#include<stdio.h>
#include<windows.h>

long int fibloop(long int num);//循环结构函数
void startcalcu(void);
long int num;


/*……………………………………………………………………//
函 数 名:main
描    述:主函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
void main(void)
{
	system("color f0");
	SetConsoleTitle("常规的循环结构（loop）来求解斐波那契数列的某个值（C版）");
	printf("常规的循环结构（loop）来求解斐波那契数列的某个值!\n");
    startcalcu();
	system("pause"); 
}

/*……………………………………………………………………//
函 数 名:fibloop
描    述:循环结构函数
入口参数:位置
出口参数:结果
//……………………………………………………………………*/
long fibloop(long num)    //循环结构函数
{
	long backtwo,backone,currentdata;   
	int count;
	if(num<=2)
		return 1;
    else 
	{
		backtwo=1;backone=1;  //先设计两个基准数据
		for(count=3;count<=num;count++)
		{  
			currentdata=backone+backtwo;   //产生最新的一个数据
			backtwo=backone;    //把基准数据往前移动 
			backone=currentdata;
		}  
		return  currentdata;
	}
}  

/*……………………………………………………………………//
函 数 名:startcalcu
描    述:提示
入口参数:无
出口参数:无
//……………………………………………………………………*/
void startcalcu(void)
{
	long int result;
	printf("请输入数字:");
	scanf("%d",&num);
	result=fibloop(num);
	printf("结果是：%d\n",result);
}

