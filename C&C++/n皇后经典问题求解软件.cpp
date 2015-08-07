//主要功能：用棋盘图示的方式展示n皇后经典问题的求解（C版）。
//由于求解结果较多，直接写入文本文件后打开即可。
//课题名称：n皇后经典问题求解软件

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>  

#define QUEENMAXCOUNT  40		//设置皇后的最大个数
#define KINDSOFWRITEFILE  1000	//设置保存文件排列种类最大值
int queenarray[QUEENMAXCOUNT];		//用于保存皇后排列信息
tm starttimer, finishtimer; //开始时间结束时间
int  kindscount;			 //排列种类计数器
int  actualcount;			 //当前情况下皇后个数


void startruning();			 //初始化函数
void finish();				 //结束化函数
void nNQueens(int queesnumnow);	//回溯法求解函数
bool place(int queesnumnow,int col); //条件判断函数
bool writefile();				 //写文件函数

void clearscreen(void);//清屏函数
void showmenu(void);//显示菜单
void processmenu(void);//根据输入执行指定功能

/*……………………………………………………………………//
函 数 名:main
 描    述:主函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
void main(void)                     //程序主入口
{   
	system("color f0");//设置颜色
	clearscreen();//先清屏
    while (1)
	{
		showmenu();//显示菜单
		processmenu();//执行指定功能
		system("pause");//暂停一下
		clearscreen();//清屏
    }
}//主函数结束

 /*……………………………………………………………………//
 函 数 名:startruning
 描    述:初始化函数
 入口参数:无
 出口参数:无
//……………………………………………………………………*/
void startruning()
{
	kindscount = 0;				//计数器初始化

	time_t presemtTime;

	printf("请输入皇后个数（注意不大于%d)\n",QUEENMAXCOUNT);
	scanf("%d",&actualcount);//输入皇后的个数
	if(actualcount > QUEENMAXCOUNT)
	{
		printf("\n【温馨提示】皇后个数大于%d，不符合要求！\n",QUEENMAXCOUNT);
		printf("==============================================\n");
		return ;
	}
	else if(actualcount > 10)		//当皇后个数大于10时，运算量很大
	{
		printf("\n【温馨提示】皇后个数较多，运算中，请等待......\n");
	}
	else if(actualcount < 4)
	{
		printf("\n【提示】%d皇后问题没有解!!!\n",actualcount);
		printf("==============================================\n");
		return;   //此时无解
	}		
	time(&presemtTime);
	starttimer = *localtime(&presemtTime);  //程序开始时间
	nNQueens(0); 
	time(&presemtTime);
	finishtimer = *localtime(&presemtTime); //程序结束时间
	finish();
}

void nNQueens(int queesnumnow)
{
	if(kindscount < KINDSOFWRITEFILE )
	{  //控制写如文件的个数
		for(int col = 0;col < actualcount;col++)
		{
			if(place(queesnumnow,col))//判断位置是否符合要求
			{
				queenarray[queesnumnow] = col;
				if(queesnumnow == actualcount-1) //约束条件
				{
					kindscount++;	 //计数器
					writefile();	 //写到文件中
				}
				else
					nNQueens(queesnumnow+1);
			}
		}
	}
}

/*……………………………………………………………………//
函 数 名:finish
描    述:结束化函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
void finish()//返回结果信息
{
	int hour,minute,second;//小时，分钟，秒
	hour = finishtimer.tm_hour-starttimer.tm_hour;
	minute = finishtimer.tm_min-starttimer.tm_min;
	second = finishtimer.tm_sec-starttimer.tm_sec;

	if(actualcount<11)
		printf("\n皇后排列方式一共有%d种。\n\n",kindscount);
	else
		printf("\n皇后排列的种类太多，不便给出总数，只取其中的%d种写入文件。\n",KINDSOFWRITEFILE);
	printf("\n【时间提示】您本次操作所用时间为(注：精确到秒)：");

	printf("%d时%d分%d秒。\n\n",hour,minute,second);

	printf("运算完毕！系统将自动打开文件，请查看...\n");		
	ShellExecute(NULL,"open","n-皇后问题.txt",NULL,NULL,SW_SHOWNORMAL);
	printf("==============================================\n");
}

/*……………………………………………………………………//
函 数 名:place
描    述:判断两个皇后是否在同一列或者一条斜线上
入口参数:
出口参数:返回两个皇后是否在同一列或者一条斜线上的信息
//……………………………………………………………………*/
bool place(int queesnumnow,int col)//判断两个皇后是否在同一列或者一条斜线上
{     
	for(int row = 0;row < queesnumnow;row++)
		if((queenarray[row] == col) 
			|| (abs(queenarray[row]-col) == abs(row-queesnumnow)))
			return false;
		return true;
}

/*……………………………………………………………………//
函 数 名:writefile
描    述:将结果写入文件
入口参数:无
出口参数:返回写入文件的信息
//……………………………………………………………………*/
bool writefile()
{
	if(kindscount == 1)   //当count=1时，将.txt文件清空。
	{
			FILE * out = fopen("n-皇后问题.txt","w");//定义文件指针
		if(out)			
			fprintf(out,"\t\t\t  %d皇后问题求解如下 \n",actualcount);
		fclose(out);
	}		
	FILE * out = fopen("n-皇后问题.txt","ab");//定义文件指针

	int colcount,rowcount,col;
	fprintf(out,"\n\t\t第【%d】种方式：(",kindscount);
	for(col = 0;col < actualcount-1;col++)
		fprintf(out,"%d,",queenarray[col]+1);
	fprintf(out,"%d)\r\n",queenarray[actualcount-1]+1);
	for(colcount = 0;colcount < actualcount;colcount++)
	{
		if(colcount==0)
		{
			fprintf(out,"\t\t┏━");
			for(col = 1;col < actualcount;col++)
				fprintf(out,"┳━");
			fprintf(out,"┓\r\n");
		}
		else
		{
			fprintf(out,"\t\t┣━");
			for(col = 1;col < actualcount;col++)
				fprintf(out,"╋━");
			fprintf(out,"┫\r\n");
		}
		
		fprintf(out,"\t\t┃");
		for(rowcount = 0;rowcount < actualcount;rowcount++)
		{
			if(rowcount == queenarray[colcount])
				fprintf(out,"★┃");
			else
				fprintf(out,"  ┃");
		}
		fprintf(out,"\r\n");
	}
	fprintf(out,"\t\t┗━");
	for(col = 1;col < actualcount;col++)
		fprintf(out,"┻━");
	fprintf(out,"┛\r\n");
	fclose(out);     //关闭文件
	return true;
}

/*……………………………………………………………………//
函 数 名:clearscreen
描    述:清屏
入口参数:无
出口参数:无
//……………………………………………………………………*/
void clearscreen(void)
{
    system("cls");
}

/*……………………………………………………………………//
函 数 名:showmenu
描    述:显示菜单
入口参数:无
出口参数:无
//……………………………………………………………………*/
void showmenu(void)
{
    printf("======================================\n");	
	printf("         n皇后经典问题求解软件        \n");	
	printf("======================================\n");	
    printf("软件功能说明：                        \n");	
    printf("  用n*n棋盘图示的方式展示八皇后经典问\n");	
    printf("题的求解。由于求解结果较多，直接写入文\n");	
    printf("本文件即可。                          \n");	
	printf("======================================\n");	
    printf("             功能菜单                 \n");	
    printf("======================================\n");	
    printf(" 1.求解n皇后问题                      \n");	
    printf(" 2.退出软件                           \n");	
	printf("======================================\n");	
	printf("请输入您的选择：");
}
/*……………………………………………………………………//
函 数 名:processmenu
描    述:执行指定功能
入口参数:无
出口参数:无
//……………………………………………………………………*/
void processmenu(void)
{
	char menuchoice;
	fflush(stdin);//消除回车影响
	scanf("%c",&menuchoice);
	switch(menuchoice)    //根据用户的选择进行相应的操作
	{
	case '1':
		startruning();	  //调用类成员函数
		break;
	case '2':
		printf("\n\n您已经成功退出本系统，欢迎再次使用!!!\n");
		system("pause");
		exit(0);
	default:
		printf("对不起，您输入的功能编号有错!请重新输入!!!\n");
		break;
	}
}
