//稀疏矩阵的压缩与解压缩

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <iomanip.h>
#include <time.h>
#include <fstream.h>

const max=10;                       						   
typedef struct triplesdata_type
{
	int datarow;
	int datacol;
	int dataval;
}triplesdatas;
triplesdatas triplesdata[max],iterm[max]; 			  						     
int matrixdata[max][max];//稀疏矩阵值
//定义存储文件名
char strMatin[] = "矩阵压缩前原始数据.txt";//保存矩阵原始数据文件名
char strMatout[] = "矩阵压缩后三元组数据.txt";//矩阵输出文件名
char strTriin[] = "三元组原始数据.txt";//保存三元组原始数据文件名
char strTriout[] = "三元组解压后矩阵数据.txt";//三元组输出文件名

//约定三元组个数为稀疏矩阵元素个数总数的20%以下加上第一行的总行总列，实际上可能没有用完此空间，类似线性表
//压缩函数
void matinput(int row,int col);	           //手工输入稀疏矩阵					   
void matcreat(int row,int col);			   //自动产生稀疏矩阵	
void transpose(int row,int col);		   //压缩稀疏矩阵成为三元组	
//解压缩函数   
void triinput(int row,int wide,int length);//手工输入三元组   
void tricreat(int row);				       //自动产生三元组		   
bool testequal(int point,int *data);	   //去掉重复数据
void simpleselectsorting(int k,int *data); //排序使分割后的行列信息符合行优先	   
void retranspose(int row);				   //解压三元组成为稀疏矩阵
void clearscreen(void);						
void showmenu(void);						
void processmenu(void);
//////各函数的具体实现
void matinput(int row,int col)//手工输入稀疏矩阵
{
	FILE *matin;//保存矩阵原始数据文件指针
	if((matin=fopen(strMatin,"w"))==NULL)
	{
		printf("文件【%s】打不开或不存在!\n");
		system("pause");
		exit(0);
	}
	int i,j;
	int number;//非零元数目，随机产生
	int count=0;//计数，数非零元个数
	int judge=0;//判定非零元数目是否超出
	printf("这是%d行%d列的矩阵范例：\n",row,col);
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
			printf("%6d",rand()%10);
		printf("\n");
	}
	do
	{
		printf("请输入稀疏矩阵中非零元个数：(约定不超过总数的%d%,即<=%d)\n",2*max,row*col*max/50);
		scanf("%d",&number);
	}while(number>(row*col*max/50));//默认个数为总数的20%以下
	printf("请输入%d 行%d 列的矩阵：\n",row,col);
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			scanf("%d",&matrixdata[i][j]);
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
		{
			if(matrixdata[i][j]!=0)
				count++;
			if(count>number)//如果超出个数，后面的数据都自动归零
			{
				judge=1;
				matrixdata[i][j]=0;
			}
		}
	if(judge)
		printf("\n多余非零元数据已重置！\n\n");
	printf("这是您输入的稀疏矩阵:\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			printf("%-6d",matrixdata[i][j]);
			fprintf(matin,"%-6d",matrixdata[i][j]);//往文件中存	
		}
		printf("\n");
		fprintf(matin,"\n");
	}
	printf("\n");
	fclose(matin);
}
void matcreat(int row,int col)//自动产生稀疏矩阵
{
	FILE *matin;//保存矩阵原始数据文件指针
	if((matin=fopen(strMatin,"w"))==NULL)
	{
		printf("文件【%s】打不开或不存在!\n");
		system("pause");
		exit(0);
	}
	int i,j;
	int dataij[max*max/5];
	int count;
	int rowc,colc;
	do
	{
		count=rand()%(row*col/5); //确定稀疏矩阵非零元个数
	}while (count<(row*col/5-3)); //设法使得稀疏数据量接近总量的20%，避免数据量过少
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			matrixdata[i][j]=0;   //赋初值
	for(i=0;i<count;i++)          //利用技巧解决了非零元分布的均匀性
	{
		dataij[i]=rand()%100;  //先产生一个两位数，首位可以为0
		rowc=dataij[i]/10;//十位数约定给行下标
		colc=dataij[i]%10;//个位数约定给列下标  
		do
		{
			matrixdata[rowc][colc]=rand()%100;  //把这个位置控制住，再产生一个一位数的随机数存入
		}while(matrixdata[rowc][colc]<10);
	}
	printf("这是产生的稀疏矩阵：\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			printf("%-6d",matrixdata[i][j]);
			fprintf(matin,"%-6d",matrixdata[i][j]);//往文件中存
		}
		printf("\n");
		fprintf(matin,"\n");
	}
	printf("\n");
	fclose(matin);
}
void transpose(int row,int col)//压缩稀疏矩阵成为三元组
{
	FILE *matout;//矩阵数据输出文件指针
	if((matout=fopen(strMatout,"w"))==NULL)
	{
		printf("文件【%s】打不开或不存在!\n",strMatout);
		system("pause");
		exit(0);
	}
	int i,j;//i代表行，j代表列
	int count=0;//计录非0元个数 
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			if(matrixdata[i][j]!=0)
			{
				triplesdata[count+1].datarow=i;//记录非零元的行
				triplesdata[count+1].datacol=j;//记录非零元的列
				triplesdata[count+1].dataval=matrixdata[i][j];//记录非零元的值，三元到位
				count++;
			}
	//以下为三元组第一行中存储的总行数、总列数、非零元个数
	triplesdata[0].datarow=row;
	triplesdata[0].datacol=col;
	triplesdata[0].dataval=count;
	printf("这是三元组的形式:\n");
	printf("行    列    值\n");
	for(i=0;i<=count;i++)
	{
		printf("%-6d%-6d%-6d\n",triplesdata[i].datarow,triplesdata[i].datacol,triplesdata[i].dataval);
		fprintf(matout,"%-6d%-6d%-6d\n",triplesdata[i].datarow,triplesdata[i].datacol,triplesdata[i].dataval);//往文件中存
	}
	printf("\n");
	fclose(matout);
}
void triinput(int row,int wide,int length)//手工输入三元组
{
	printf("请输入%d行的三元组:\n",row);
	for(int i=1;i<=row;i++)
	{
		do
		{
			printf("请输入第%d行数据：",i);
			scanf("%d%d%d",&triplesdata[i].datarow,&triplesdata[i].datacol,&triplesdata[i].dataval);
		}while(triplesdata[i].datarow>=wide||triplesdata[i].datacol>=length||triplesdata[i].dataval==0);
	}
	//以下为三元组第一行中存储的总行数、总列数、非零元个数
	triplesdata[0].datarow=wide;
	triplesdata[0].datacol=length;
	triplesdata[0].dataval=row;
	//行排序
	for(int term=1;term<=row;term++)
		for(i=1;i<=term;i++)	
			if(triplesdata[i].datarow>triplesdata[term].datarow)
			{
				iterm[i]=triplesdata[term];//保留未排数据首位置的值
				for(int j=term;j>i;j--)	//移动数据
					triplesdata[j]=triplesdata[j-1];
				triplesdata[i]=iterm[i];//把数据存入
				break;
			}		
	printf("\n这是您输入的三元组：\n");
	for(i=1;i<=row;i++)
		printf("%6d%6d%6d\n",triplesdata[i].datarow,triplesdata[i].datacol,triplesdata[i].dataval);
	printf("\n");
}
void tricreat(int row)//自动产生三元组	
{
	int dataij[max];
	for(int k=1;k<=row;k++)//这里从1开始，下面再考虑0行的三个数据
	{
		do
		{
			dataij[k]=(rand()%100);//产生0 ~ 99的数据
		}while(testequal(k,dataij));//只要检测的结果为真就重新产生数据
	}
	for(k=2;k<=row;k++)
		simpleselectsorting(row,dataij);
	/*分离数据，得到行列*/
	for(k=1;k<=row;k++)
	{
		triplesdata[k].datarow=dataij[k]/10;//十位数为行值
		triplesdata[k].datacol=dataij[k]%10;//个位数为列值
		do
		{
			triplesdata[k].dataval=(rand()%100);//第三列放2位数的数据
		}while(triplesdata[k].dataval<10);
	}
	//求总列数
	int datacmax=triplesdata[1].datacol;
	for(int i=2;i<=row;i++)
		if(datacmax<triplesdata[i].datacol)
			datacmax=triplesdata[i].datacol;
	//以下为三元组第一行中存储的总行数、总列数、非零元个数
	triplesdata[0].datarow=dataij[row]/10+1;
	triplesdata[0].datacol=datacmax+1;
	triplesdata[0].dataval=row;
	printf("\n");
}
bool testequal(int point,int *data)//判断是否是重复数据
{
	for(int i=1;i<point;i++)
		if(data[point]==data[i])
			return 1;//1代表出现了相等的情况
	return 0;//0代表没有相等的情况
}
void simpleselectsorting(int k,int *data)//排序使分割后的行列信息符合行优先
{
	int min;
	for(int term=1;term<=k;term++)
		for(int i=term+1;i<=k;i++)	
			if(data[i]<data[term])
			{
				min=data[i];
				data[i]=data[term];
				data[term]=min;
			}		
}
void retranspose(int row)//解压三元组成为稀疏矩阵
{
	FILE *triin;          //tri:triples:三元组 in: 输入
	FILE *triout;   //tri:triples:三元组 out:输出
	if((triin=fopen(strTriin,"w"))==NULL)
	{
		printf("文件【%s】打不开或不存在!\n",strTriin);
		system("pause");
		exit(0);
	}

	if((triout=fopen(strTriout,"w"))==NULL)
	{
		printf("文件【%s】打不开或不存在!\n",strTriout);
		system("pause");
		exit(0);
	}
	int i,j;//i代表行，j代表交换中的行
	int maxrow,maxcol;//最大行，最大列
	int rowc,colc;
	printf("这是行优先三元组的形式:\n");
	printf("行    列    值      \n");
	for(i=0;i<=row;i++)
	{
		printf("%-6d%-6d%-6d\n",triplesdata[i].datarow,triplesdata[i].datacol,triplesdata[i].dataval);
		fprintf(triin,"%-6d%-6d%-6d\n",triplesdata[i].datarow,triplesdata[i].datacol,triplesdata[i].dataval);//往文件中存
	}
	maxrow=triplesdata[0].datarow;//最大行
	maxcol=triplesdata[0].datacol;//最大列
	for(i=0;i<maxrow;i++)         //先行把所有数据预置为0
		for(j=0;j<maxcol;j++)
			matrixdata[i][j]=0;
	for(i=1;i<=row;i++)                    //把三元组信息恢复到稀疏矩阵中去
	{
		rowc=triplesdata[i].datarow;//等号对齐有利于看清楚功能
		colc=triplesdata[i].datacol;//恢复行和列的值
		matrixdata[rowc][colc]=triplesdata[i].dataval;//再恢复稀疏矩阵中元素的值/////////////////////////
	}
	printf("\n解压缩后总行:%d，总列:%d,非零元个数：%d",maxrow,maxcol,row);
	printf("这是解压后稀疏矩阵的数据:\n");
	for(i=0;i<maxrow;i++)
	{
		for(j=0;j<maxcol;j++)
		{
			printf("%-6d",matrixdata[i][j]);
			fprintf(triout,"%-6d",matrixdata[i][j]);
		}
		fprintf(triout,"\n");
		printf("\n");
	}
	printf("\n");
	fclose(triin);
	fclose(triout);
}

//////////////
void clearscreen(void)			//清屏
{
    system("cls");
}
void showmenu(void)				//菜单
{
  	printf("      稀疏矩阵的压缩与解压缩的应用(C版)      \n");
	printf("========================================\n");
	printf("  （约定：内部预置一个数组，用户的    ）\n");
	printf("  （      稀疏矩阵大小在其中即可      ）\n");
	printf("  （      所有数组均启用了0下标       ）\n");
	printf("  （      所有产生的数据同时写入了文件）\n");
	printf("========================================\n");
	printf("   一、稀疏矩阵的压缩                   \n");
	printf("      1.用户自己输入矩阵                \n");
    printf("      2.计算机随机产生稀疏矩阵          \n");
	printf("                                        \n");
	printf("   二、三元组矩阵的解压缩               \n");
    printf("      3.用户自己输入三元组              \n");
    printf("      4.计算机随机产生三元组矩阵        \n");
	printf("                                        \n");
	printf("      5.退出系统                        \n");
	printf("========================================\n");
}
void processmenu(void)//菜单选项
{				
	int menuchoice;					
	int row;								   //行
	int col;								   //列
	int counts;
	int num;
	printf("请输入您的选择：");   
	scanf("%d",&menuchoice);
	printf("========================================\n");

	switch(menuchoice)						   //根据用户的选择进行相应的操作
	{
	case 1:
				printf("请输入行、列值：(最大值小于等于%d 用空格隔开)\n",max);
				scanf("%d%d",&row,&col);
			    matinput(row,col);
	            transpose(row,col);
				break;
				
	case 2:
				printf("请输入行、列值：(最大值小于等于%d 用空格隔开)\n",max);
				scanf("%d%d",&row,&col);
				matcreat(row,col);
				transpose(row,col);
				break;

	case 3:
				do
				{
					printf("请输入三元组解压缩后矩阵的行列数：\n");
					do
					{
						printf("建议三元组中的行列值：4<行值<%d,4<列值<%d\n",max);//保证稀疏矩阵合适大小
						scanf("%d%d",&row,&col);
					}while(row>max||row<1||col>max||col<1);
					counts=row*col*max/50;
				}while(counts<2);
				do
				{
					printf("请输入非零元个数：（%d ~ %d）\n",counts-2,counts);
					scanf("%d",&num);
				}while(num<counts-2||num>counts);
				triinput(num,row,col);
				retranspose(num);
				break;
	case 4:
				row=rand()%9+1;
				tricreat(row);
				retranspose(row);
				break;

	case 5:		
				exit(1);
	default:
				printf("对不起，您输入的功能编号有错!请重新输入!!!\n");
		    	break;
	}
};
//程序主入口
void main(void)                     
{   
	system("color f0");
	srand(time(NULL));
	clearscreen();
    while (1)
	{
  		showmenu();
		processmenu();
		system("pause"); 
		clearscreen();
    }
}//主函数结束
