#include<stdio.h>
#include<windows.h>
class swapClass
{
public:
	swapClass(){};
	~swapClass(){};
	void swap(int &a,int &b);
	void swap(char &a,char &b);//重载第一个
};

void swapClass::swap(int &a,int &b)
{
	a = a-b;
	b = b+a;
	a = b-a;
}

void swapClass::swap(char &a,char &b)
{
	a = a-b;
	b = b+a;
	a = b-a;
}

void main()
{
	system("color f0");
	char ch1,ch2;
	int a = 10,b = 20;
	ch1 = 'a';
	ch2 = 'd';
	swapClass swapInstance;

	printf("注：两个重载函数的函数体都一样，\n可以实现字符，整数的交换，\n不借助中间变量.\n\n");

	printf("请输入要交换的两个字符（空格隔开）:\n");
	fflush(stdin);
	scanf("%c %c",&ch1,&ch2);

	printf("请输入要交换的两个整数（空格隔开）:\n");
	fflush(stdin);
	scanf("%d%d",&a,&b);

	printf("交换之前为：\n");
	printf("ch1=%c ch2=%c\n",ch1,ch2);
	printf("a=%d b=%d\n",a,b);

	swapInstance.swap(ch1,ch2);
	swapInstance.swap(a,b);

	printf("交换之后为：\n");
	printf("ch1=%c ch2=%c\n",ch1,ch2);
	printf("a=%d b=%d\n",a,b);
}
