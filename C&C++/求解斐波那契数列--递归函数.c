//功能：用递归函数（Recursion）来计算斐波那契数列的某个值

#include<stdio.h>
#include<windows.h>


long int fibrecursion(long int num);
void startcalcu();
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
	SetConsoleTitle("用递归函数（Recursion）来计算斐波那契数列的某个值");
	printf("用递归函数（Recursion）来计算斐波那契数列的某个值!\n");
    startcalcu();
	system("pause"); 
}

/*……………………………………………………………………//
函 数 名:fibrecursion
描    述:递归函数
入口参数:要计算的位置
出口参数:结果
//……………………………………………………………………*/
long fibrecursion(long num)
{
	if  (num<=2)  
		return 1;     //递归出口
	else  
		return(fibrecursion(num-1)+fibrecursion(num-2));//递归调用
} 

/*……………………………………………………………………//
函 数 名:startcalcu
描    述:提示
入口参数:无
出口参数:无
//……………………………………………………………………*/
void startcalcu()
{
	long int product;
	printf("请输入数字:");
	scanf("%d",&num);
	product=fibrecursion(num);
	printf("结果是：%d\n",product);
}        
