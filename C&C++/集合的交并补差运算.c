//程序名：【程序构建 3-3】集合的交，并，差功能（纯C版）.cpp
//功能：完成集合的求交，求并，求差及显示功能。

//改进：1.对用户的输入不局限于英文字母  2.优化程序性能  3.修复一些bug，如之前没有释放空间的操作  4.优化部分代码

#include<stdio.h> 
#include<stdlib.h> 
#include<conio.h>
#include<string.h>
#include<windows.h>

typedef struct Setmember//定义集合中元素结构体
{ 
	char data; 
	Setmember *next;
} Setmember; 

#define len sizeof(struct Setmember)//宏定义要开辟的空间大小
//定义三个头结点，分别是集合一和集合二以及他们的交并差三条链表的头结点
Setmember *head1,*head2,*headresult;

//函数声明
void init();                                                        //初始化工作，为程序运行做好准备
int  main_menu();                                                  	//主菜单函数
void read_data(Setmember *head);                                   	//读取数据函数
void display(Setmember *head);                                      //显示数据函数
void destroy(Setmember *head);                                                     //销毁链表，释放空间
void Setintersection(Setmember *head1,Setmember *head2, Setmember *headresult);   //求集合交集函数
void Setunion(Setmember *head1,Setmember *head2, Setmember *headresult);          //求集合并集函数
void Setdifference(Setmember *head1,Setmember *head2, Setmember *headresult);     //求集合差集函数
/*……………………………………………………………………//
函 数 名:main
描    述:主函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
void main()
{ 
	init();//初始化
	system("color f0");
	SetConsoleTitle("集合的交并差运算");
	for(;;)//无条件的循环语句
	{
		system("cls");								/*清屏*/
		switch(main_menu())
		{
			
		case 1:
			
			destroy(head1);//先释放链表head1
			destroy(head2);//先释放链表head2
			
			printf("请您用字符连续输入集合一和集合二中的元素，\n");
			fflush(stdin);//消除回车影响
			printf("请输入集合1：\n"); 
			read_data(head1); 
			fflush(stdin);
			printf("请输入集合2：\n"); 
			read_data(head2); 
			system("pause");
			break;
		case 2:
			printf("集合1为：\n"); 
			display(head1); 
			printf("集合2为：\n"); 
			display(head2); 
			system("pause");
			break;
		case 3:
			printf("集合1为：\n"); 
			display(head1); 
			printf("集合2为：\n"); 
			display(head2); 
			printf("集合1与集合2的并为:\n"); 
			Setunion(head1,head2,headresult); 
			display(headresult); 
			system("pause");
			destroy(headresult);//处理善后，释放链表headresult
			break;
		case 4:
			printf("集合1为：\n"); 
			display(head1); 
			printf("集合2为：\n"); 
			display(head2); 
			printf("集合1与集合2的交为:\n"); 
			Setintersection(head1,head2,headresult); 
			display(headresult); 
			system("pause");
			destroy(headresult);//处理善后，释放链表headresult
			break;
		case 5:
			printf("集合1为：\n"); 
			display(head1); 
			printf("集合2为：\n"); 
			display(head2);
			printf("集合1与集合2的差为:\n"); 
			Setdifference(head1,head2,headresult); 
			display(headresult); 
			system("pause");
			destroy(headresult);//处理善后，释放链表headresult
			break;
		case 0: 
			system("cls");
			exit(0);
		default :
			{	
				fflush(stdin);											/*清缓存*/
				printf("\t选择错误，请正确输入您的选择(1~6):\n");
				system("pause");
			}
			
		}
	}
}

/*……………………………………………………………………//
函 数 名:init()
描    述:初始化工作，为程序运行做好准备
入口参数:无
出口参数:无
//……………………………………………………………………*/
void init()
{
	//开辟集合一的头结点
	head1=(Setmember *)malloc(len); 
	head1->next=NULL; 
	//开辟集合二的头结点
	head2=(Setmember *)malloc(len); 
	head2->next=NULL; 
	//开辟集合运算结果的头结点
	headresult=(Setmember *)malloc(len); 
	headresult->next=NULL;
}

/*……………………………………………………………………//
函 数 名:destroy()
描    述:初始化工作，为程序运行做好准备
入口参数:无
出口参数:无
//……………………………………………………………………*/
void destroy(Setmember *head)
{
	Setmember *presentp,*searchp; 
	searchp = head->next;               //释放head1链表
	while(searchp)
	{
		presentp = searchp;
		searchp = searchp->next;
		delete presentp;
	}
}

/*……………………………………………………………………//
函 数 名:main_menu()
描    述:显示功能菜单
入口参数:无
出口参数:无
//……………………………………………………………………*/
int main_menu()
{
	
	int choose;
	printf("\n\n\n");
	printf("\t\t****************集合的常用运算系统****************\n");
	printf("\t\t   1、输入集合一和集合二\n");
	printf("\t\t   2、显示已经输入的集合一和集合二\n");
	printf("\t\t   3、集合一与集合二的并集为\n");
	printf("\t\t   4、集合一与集合二的交集为\n");
	printf("\t\t   5、集合一与集合二的差集为\n");
	printf("\t\t   0、退出\n");
	printf("\t\t******************************************************\n");
	printf("请输入功能选项：");
	scanf("%d",&choose);
	return choose;
}
/*……………………………………………………………………//
函 数 名:read_data
描    述:读取数据
入口参数:无
出口参数:无
//……………………………………………………………………*/
void read_data(Setmember *head)
{ 
	Setmember *newdatap,*searchp = head; 
	char temp; 
	scanf("%c",&temp); 
	while(temp!='\n') //判断用户输入的是否是回车符，以此判断用户是否输入完毕
	{
		newdatap=(Setmember *)malloc(len); 
		newdatap->data=temp;                      //赋值
		searchp->next = newdatap;                //挂链
		searchp = searchp->next;
		scanf("%c",&temp); 
	}
	searchp->next = NULL;
} 
/*……………………………………………………………………//
函 数 名:display
描    述:显示集合元素函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
void display(Setmember *head)
{ 
	Setmember *searchp=head->next; 
	printf("\t{");
	if(searchp == NULL)
		printf("Φ");
	else
		while(searchp!=NULL) 
		{ 
			printf("%c ",searchp->data); 
			searchp=searchp->next; 
		} 
		printf("}\n"); 
} 
/*……………………………………………………………………//
函 数 名:Setunion
描    述:计算集合一与集合二的并函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
void Setunion(Setmember *head1,Setmember *head2, Setmember *headresult)
{ 
	Setmember *searchp1,*searchp2,*newdata,*temp;
	temp = headresult;
	searchp1=head1->next; 
	while(searchp1!=NULL) 
	{ 
		newdata=(Setmember *)malloc(len); //开辟空间
		newdata->data=searchp1->data;     //赋值
		temp->next = newdata;             //挂链
		temp = temp->next; 
		searchp1=searchp1->next; 
	} 
	searchp2=head2->next; 
	while(searchp2!=NULL) 
	{ 
		searchp1=head1->next; 
		while(searchp1!=NULL)
		{
			if(searchp2->data==searchp1->data)
				break;
			searchp1=searchp1->next; 
		}
		if(searchp1 == NULL)
		{
			newdata=(Setmember *)malloc(len); 
			newdata->data=searchp2->data; 
			temp->next = newdata;             //挂链
			temp = temp->next; 
		}
		searchp2=searchp2->next; 
	} 
	temp->next = NULL;
} 
/*……………………………………………………………………//
函 数 名:Setintersection
描    述:计算集合一和集合二的交函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
void Setintersection(Setmember *head1,Setmember *head2, Setmember *headresult)
{ 
	Setmember *searchp1,*searchp2,*newdata,*temp; 
	temp = headresult;
	searchp1=head1->next; 
	while(searchp1!=NULL) 
	{ 
		searchp2=head2->next; 
		while(searchp2!=NULL)
		{
			if(searchp1->data==searchp2->data)//判断元素是否相等，如果是就将元素挂链到headresult后面
			{
				newdata=(Setmember *)malloc(len); 
				newdata->data=searchp1->data; 
				temp->next = newdata;             //挂链
				temp = temp->next; 
				break;
			}
			searchp2=searchp2->next; 
		}
		searchp1=searchp1->next; 
	} 
	temp->next = NULL;
} 
/*……………………………………………………………………//
函 数 名:Setdifference
描    述:计算集合一与集合二的差函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
void Setdifference(Setmember *head1,Setmember *head2, Setmember *headresult)
{ 
	Setmember *searchp1,*searchp2,*newdata,*temp; 
	searchp1=head1->next;
	temp = headresult;
	while(searchp1!=NULL) 
	{
		searchp2=head2->next; 
		while((searchp2!=NULL)&&(searchp1->data!=searchp2->data)) 
			searchp2=searchp2->next; 
		if(searchp2==NULL) //条件searchp2==NULL表示此轮比较完毕
		{ 
			newdata=(Setmember *)malloc(len); 
			newdata->data=searchp1->data; 
			temp->next = newdata;             //挂链
			temp = temp->next; 
			
		}
		searchp1=searchp1->next; 
	} 
	temp->next = NULL;
} 
