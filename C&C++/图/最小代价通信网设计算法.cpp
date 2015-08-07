/*
在n个城市之间铺设电话通信网，求出最佳方案，可以最省钱。
求解算法为：在可能架设的所有线路中选取n-1条，既能连通n-1个城市，
又使总投资达到“最小”。
网采用邻接矩阵为存储结构，以结点偶对(A,B)的形式输出最小生成树的边。
结点名称不论输入大小写都转换为大写。
*/
//======================================================================================
//功能：最小生成树的两种算法
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;
enum  returninfo{success,wrong,fail,error};  //定义错误类型清
const int Maxsize=26;                       //设置邻接矩阵的最大限，此处用字母个数
float MGraph[Maxsize][Maxsize]={0};         //邻接矩阵初始化为0
int	  flag[Maxsize]={0};                    //初始化标志位全部为0
int   delflag[Maxsize]={0};                 //初始化已经删除结点的标志位为0
int   nodenumber=10,deletenumber=0;         //nodenumber结点个数，deletenumber被删除结点的个数
int	  datamark=0;							//标志目前是否已经有图的数据，0为没有建立
//结点类
class node     //创建一个node类来表示边的信息
{
public:
	node(char initpointstart,char initpointend,float initweight,node *initnext=NULL);
	node(node *initnext=NULL);//构造函数重载，为头结点节省空间
	~node();
	void display(void);		//显示边的结点以及权值信息
	char pointstart;		//边的起点【约定ASCII码小】
	char pointend;			//边的终点【约定ASCII码大】
	float weight;			//边的权值
	node *next;				//后继结点指针
};
node::node(char initpointstart,char initpointend,float initweight,node *initnext)
{
	pointstart=initpointstart;
	pointend=initpointend;
	weight=initweight;
	next=initnext;
}
node::node(node *initnext)
{
	next=initnext;
}
node::~node()
{}
void node::display(void)
{
	cout<<"   ("<<pointstart<<","<<pointend<<")="<<weight<<endl;//依次为边的起点、终点、权值
}
//链表类
class linklist     //定义链表linklist类
{
	friend class interfacebase;
	friend class minispantree;
private:
	node *headp;
	int number;    //统计每个链表中结点的个数
public:
	linklist();                                        //构造函数
	~linklist();									   //析构函数
	void clearlist(void);                              //清空链表
	bool empty(void) const;                            //判断是否空链
};
linklist::linklist()                 //构造函数
{
	headp=new node;                  //申请新结点，作为头结点
	headp->next=NULL;                //头结点的地址域预设为空地址
	number=0;                        //计数器清零，表明开始时没有实际数据
}
linklist::~linklist()                //析构函数
{
    clearlist();                     //删除所有数据，释放所有结点
	delete headp;                    //把头结点也释放掉
	number=0;                        //计数器清零，表明开始时没有实际数据
}
void linklist::clearlist(void)       //清空链表
{
	node *searchp=headp->next,*followp=headp;    //初始化两个指针
    while(searchp!=NULL)
	{
		followp=searchp;
		searchp=searchp->next;
		delete followp;
	}
	headp->next=NULL;              //保留了最后一个结点，就是头结点，并且链域置为空
	number=0;                      //计数器也清零
}
bool linklist::empty(void)const   //是否空链
{
	if(number==0)
		return true;
	else
		return false;
}
//最小生成树类
class minispantree
{
public:
	minispantree();
	~minispantree();
	bool readfile();				//读文件操作
	void traveral(void);			//显示当前邻接矩阵
	returninfo nodeinsdel(void);	//结点的增删操作
	returninfo edgeinsdel(void);	//边的增删操作
	returninfo edgemodify(void);	//修改边的权值
	void failflag(void);			//显示标志位信息
	char letterchange(char nodenameofedge);	//小写字母换成大写信息
	returninfo kruskal();			//kruskal算法
	returninfo prim();				//prim算法
protected:
	linklist list[4];
	//0、1下标表示prim算法初始和最终数据,2、3下标表示kruskal算法的初始和最终数据
};
minispantree::minispantree(){}
minispantree::~minispantree(){}
bool minispantree::readfile()     //读文件操作
{
	char choice;
	choice='0';
	cout<<endl<<"请选择不同的文件："<<endl;
	cout<<"	1、正常默认数据"<<endl
		<<"	2、有孤立结点不能形成联通图的默认数据"<<endl
		<<"	3、有重复数据的默认数据"<<endl
		<<"	4、结点有超范围错误的默认数据"<<endl
		<<"	5、读入用户给定的数据文件（文件名约定为：graphdata.txt）"<<endl
		<<"	6、退出"<<endl<<"请选择：";

	/*do
	{
		cin>>choice;
    }while(choice<'1'&&choice>'6');
	*/
	
	while(choice!='1'&&choice!='2'&&choice!='3'&&choice!='4'&&choice!='5'&&choice!='6')
		cin>>choice;
    
	fstream in;
	switch(choice)    //根据用户的选择进行相应的操作
	{
	case '1':
		cout<<endl<<"读入正常的默认数据！可以产生最小代价生成树！"<<endl;
		in.open("graphdata01.txt");
		break;
	case '2':
		cout<<endl<<"读入有孤立结点的默认数据！不能形成联通图！"<<endl;
		in.open("graphdata02.txt");
		break;
	case '3':
		cout<<endl<<"读入有重复数据的默认数据！相同数据后面的有效！"<<endl;
		in.open("graphdata03.txt");
		break;
	case '4':
		cout<<endl<<"读入结点超范围错误的默认数据！忽略超范围结点！"<<endl;
		in.open("graphdata04.txt");
		break;
	case '5':
		cout<<endl<<"读入用户给定的数据文件（文件名约定为：graphdata.txt）"<<endl;
		in.open("graphdata.txt");
		break;
	case '6':
		{cout<<endl<<"您已经选择放弃读文件！"<<endl;
		return false;
		}
	default:
		break;
	}
	if(!in)
		return false;
    else
	{
		int row,col,edgenumber,edgenumbernow;		//行坐标、列坐标、边的个数，临时边数计数器
		float edgeweight;							//权值
		char nodenameofedge[5];						//nodenameofedge为边的信息的字符数组，长度为5
		for(row=0;row<Maxsize;row++)				//每次重新开始工作都要初始化相关数组和数值
			for(col=0;col<Maxsize;col++)
				MGraph[row][col]=0;
		deletenumber=0;                             //删除结点数归零
		for(col=0;col<nodenumber;col++)
			delflag[col]=0;                         //删除结点标志位归零
		in>>nodenumber;								//读入图的结点总数
	    in>>edgenumber;								//读入图的边总数
		edgenumbernow=edgenumber;					//启用一个临时边数计数器
		while(edgenumbernow!=0)						//如果边存在，则读入边信息和权值	
		{
			in>>nodenameofedge>>edgeweight;			//nodenameofedge形式类似为<AB>=
			nodenameofedge[1]=letterchange(nodenameofedge[1]);	//坐标0为左括号，坐标1为第一个字母
			nodenameofedge[2]=letterchange(nodenameofedge[2]);  //坐标2为第二个字母，均转换为大写
			row=nodenameofedge[1]-'A';				//计算行坐标
			col=nodenameofedge[2]-'A';				//计算列坐标
			if(row<nodenumber && col<nodenumber )
			{
				MGraph[row][col]=edgeweight;			//在邻接矩阵上面相应操作
				MGraph[col][row]=edgeweight;			//无向图，所有对称的位置同时赋值	
			}
			edgenumbernow--;//边数计数器减一，为结束本次处理做准备
		}
	}
	in.close();    //关闭流文件
	return true;
}
void minispantree::traveral(void)
{
	int i,j;
	char inode='A';
	cout<<"    ┃";
	for(i=0;i<nodenumber;i++)
		cout<<setw(6)<<setiosflags(ios::right)<<inode++;
	inode='A';     //重新赋值
	cout<<endl<<"━━╋";
	for(i=0;i<nodenumber;i++)
		cout<<"━━━";
	for(i=0;i<nodenumber;i++)
	{
		cout<<endl<<"  "<<setw(2)<<inode++<<"┃";
		for(j=0;j<nodenumber;j++)
		{
			if(delflag[i]==1 || delflag[j]==1)      //删除点
				cout<<setw(6)<<setiosflags(ios::right)<<"▅";
			else if(i!=j && MGraph[i][j]==0)  //无边
				cout<<setw(6)<<setiosflags(ios::right)<<"∞";
			else
				cout<<setw(6)<<setiosflags(ios::right)<<MGraph[i][j];
		}
		cout<<endl<<"    ┃";
	}
	cout<<endl<<endl<<"【温馨提示】数据显示为 ▅ 的表示该点被删除，无数据显示。"<<endl<<endl;
}
returninfo minispantree::nodeinsdel(void)  //结点信息的增删操作
{
	char inode;
	int row,col,choice;
	cout<<"	1、增加结点操作"<<endl<<"	2、删除结点操作"<<endl<<"	3、退出"<<endl<<"请选择：";
	cin>>choice;
	if(choice==1)
	{
		cout<<"您可以选择的新增结点有： ";
		delflag[nodenumber]=1;
		nodenumber++;
		for(row=0;row<nodenumber;row++)
			if(delflag[row]==1)
				cout<<setw(5)<<char(row+'A');
		cout<<endl<<endl<<"	请选择：";
		cin>>inode;
		inode=letterchange(inode);      //输入数据检测
		if(inode==0)					//输入数据有错
			return error;
		if(delflag[inode-'A']!=1)		//没有输入正确
			return error;
		nodenumber--;
		delflag[nodenumber]=0;             //重新回到0
		if(inode-'A'==nodenumber)
		{	nodenumber++; deletenumber++;}      //如果新增结点为后续点则nodenumber++
		delflag[inode-'A']=0;			//赋值0
		deletenumber--;
	}
	else if(choice==2)
	{
		cout<<"您可以选择的删除结点有： ";
		for(row=0;row<nodenumber;row++)
			if(delflag[row]==0)
				cout<<setw(5)<<char(row+'A');
			cout<<endl<<endl<<"	请选择：";
			cin>>inode;
			inode=letterchange(inode);   //输入数据检测
			if(inode==0)                 //输入数据有错
				return error;
			if(delflag[inode-'A']==1)    //没有输入正确
				return error;
			deletenumber++;                   //被删结点数deletenumber++
			delflag[inode-'A']=1;        //赋值1
			for(row=0;row<nodenumber;row++)  //删除点上的边全部为0
				for(col=0;col<nodenumber;col++)
					if(col==inode-'A' || row==inode-'A')
						MGraph[row][col]=0;
	}
	else
		return fail;     //退出
	return success;
}
returninfo minispantree::edgeinsdel(void)  //边信息的增删操作
{
	char nodenamestart,nodenameend;
	int  row,col,choice;
	float weight;
	cout<<"	1、增加边信息操作"<<endl<<"	2、删除边信息操作"<<endl<<"	3、退出"<<endl<<"请选择：";
	cin>>choice;
	if(choice==1)
	{
		cout<<"请输入增加边对应的结点名称（格式：A B 【空格分开】）：";
		cin>>nodenamestart>>nodenameend;
		nodenamestart=letterchange(nodenamestart);     //输入数据检测
		nodenameend=letterchange(nodenameend);
		if(nodenamestart==0 || nodenameend==0) //输入数据有误
			return error;
		row=nodenamestart-'A';
		col=nodenameend-'A';
		if(delflag[row]==1 || delflag[col]==1)  //检测点是否存在
			return error;
		if(MGraph[row][col]!=0)
		{
			cout<<"当前此边的权值是："<<MGraph[row][col]<<endl;
			return fail;
		}
		cout<<"请输入该边的权值：";
		cin>>weight;
		MGraph[row][col]=weight;         //在邻接矩阵上面相应操作
		MGraph[col][row]=weight;
	}
	else if(choice==2)
	{
		cout<<"请输入删除边对应的结点名称（格式：A B 【空格分开】）：";
		cin>>nodenamestart>>nodenameend;
		nodenamestart=letterchange(nodenamestart);     //输入数据检测
		nodenameend=letterchange(nodenameend);
		if(nodenamestart==0 || nodenameend==0) //输入数据有误
			return error;
		row=nodenamestart-'A';
		col=nodenameend-'A';
		if(delflag[row]==1 || delflag[col]==1)  //检测点是否存在
			return error;
		if(MGraph[row][col]==0)
			return fail;
		MGraph[row][col]=0;         //在邻接矩阵上面相应操作
		MGraph[col][row]=0;
	}
	else
		return fail;     //退出
	return success;
}
returninfo minispantree::edgemodify()  //修改边的权值信息
{
	char nodenamestart,nodenameend,choice;
	float edgeweight;
	int row,col;
	cout<<"请输入所修改边对应的结点名称（格式：A B 【空格分开】）：";
	cin>>nodenamestart>>nodenameend;
	nodenamestart=letterchange(nodenamestart);    //输入数据检测
	nodenameend=letterchange(nodenameend);
	if(nodenamestart==0 || nodenameend==0) //输入数据有误
		return error;
	row=nodenamestart-'A';
	col=nodenameend-'A';
	if(delflag[row]==1 || delflag[col]==1)  //检测点是否存在
		return error;
	if(MGraph[row][col]==0)    //检测该边是否存在
		return error;
	cout<<"当前此边的权值是："<<MGraph[row][col]<<endl;
	cout<<"确认要进行修改吗（Y/y）：";
	cin>>choice;
	if(choice=='Y' || choice=='y')
	{
		cout<<"请输入你要重新设定的权值：";
		cin>>edgeweight;
		MGraph[row][col]=edgeweight;         //在邻接矩阵上面相应操作
		MGraph[col][row]=edgeweight;
	}
	else
		return fail;
	return success;
}
void minispantree::failflag(void) //显示标志位置的信息
{
	int i;
	cout<<"┌──";
	for(i=0;i<nodenumber;i++)
		cout<<"┬─";
	cout<<"┐"<<endl;
	cout<<"│结点│";
	for(i=0;i<nodenumber;i++)
		cout<<char(i+'A')<<" │";
	cout<<endl<<"├──";
	for(i=0;i<nodenumber;i++)
		cout<<"┼─";
	cout<<"┤"<<endl;
	cout<<"│标志│";
	for(i=0;i<nodenumber;i++)
	{
		if(delflag[i]==1)
			cout<<"▅│";
		else
			cout<<flag[i]<<" │";
	}
	cout<<endl<<"└──";
	for(i=0;i<nodenumber;i++)
		cout<<"┴─";
	cout<<"┘"<<endl<<endl;
}
char minispantree::letterchange(char nodenameofedge) //处理输入字母信息（如果小写换大写）
{
	if(nodenameofedge>='a' && nodenameofedge<='a'+nodenumber-1)
		return char(nodenameofedge-32);    //小写换大写
	else if(nodenameofedge>='A' && nodenameofedge<='A'+nodenumber-1)
		return nodenameofedge;         //大写则不改
	else
		return 0;            //表示输入的数据有错
}
returninfo minispantree::prim()     //prim算法
{
	//list[4]：其中0、1坐标表示prim算法的初始链表和最终结果链表
	list[0].clearlist();//每次调用算法前将初始和最终数据清空
	list[1].clearlist();  
	char beginnode;//进入结点名称
	node *newnode,*searchp,*followp,*listrear;//新结点、搜索指针、尾随指针、尾部指针
	int i,j;//循环遍历
	int nodeflag=0;//结点标志位
  	for(i=0;i<nodenumber;i++)     //标志位归零
		flag[i]=0;
	cout<<"请在下面范围中输入起始结点名称【A-"<<char('A'+nodenumber-1)<<"】：";
	cin>>beginnode;
	beginnode=letterchange(beginnode);    //小写转换成大写
	if(beginnode==0) //输入数据有误
		return error;
	i=int(beginnode-'A');//计算出进入结点的序号
    flag[i]=1;       //把该序号代表的起始点的标志位翻转为1
	while(list[1].number!=nodenumber-1-deletenumber)
	{
		for(j=0;j<nodenumber;j++)
			if(MGraph[i][j]!=0)    //i固定不变，把所在行的列全部过一遍
			//如果邻接矩阵中权值不为0,则把该边加到链表中
			{
				newnode=new node(i+'A',j+'A',MGraph[i][j]);//结点中存入响应的结点名和权值
				if(list[0].empty()) //如果此时链表为空
				{
					newnode->next=NULL;
					list[0].headp->next=newnode;
					list[0].number++;
				}
				else
				{
					//如果这条边已经存在的话，则无需加入
					searchp=list[0].headp->next;//启动搜索指针
					followp=list[0].headp;      //启动尾随指针 
					while(searchp!=NULL && searchp->weight<MGraph[i][j])//升序排列，找正确位置
					{
						followp=searchp;
						searchp=searchp->next;
					}
					while(searchp!=NULL && searchp->weight==MGraph[i][j])//当发现权值相等时
					{
						if(searchp->pointstart==i+'A' && searchp->pointend==j+'A')//起点终点也相同
						{
							nodeflag=1;
							delete newnode;//释放新结点
							break;
						}
						searchp=searchp->next;//往后移动指针
					}
					if(followp!=NULL && nodeflag==0)
					{
						newnode->next=followp->next;//插入新结点到链表中
						followp->next=newnode;
						list[0].number++;			//计数器加一
						nodeflag=0;					//重新归零
					}
				}
			}
		if(list[0].number==0 )
		{	if(delflag[i]==1)
			{
				cout<<endl<<"你输入的结点 "<<char(i+'A')<<" 已被删除!"<<endl;
				cout<<endl<<"【温馨提示】"<<endl
					<<"	1.标志值为0表示为暂未选入的结点点群；"<<endl
					<<"	2.标志值为1表示已被选入的结点群；"<<endl
					<<"	3.标志值为 ▅ 表示已删除结点群。"<<endl<<endl;
				failflag();          //显示标志位信息
				return error;
			}
			cout<<endl<<"【温馨提示】"<<endl
				<<"	1.标志值为0表示为暂未选入的结点点群；"<<endl
				<<"	2.标志值为1表示已被选入的结点群；"<<endl
				<<"	3.标志值为 ▅ 表示已删除结点群。"<<endl<<endl;
			failflag();          //显示标志位信息
			return fail;
		}
		searchp=list[0].headp->next;	//取当前list[0]链表中权值最小的边
		while(searchp->next!=NULL && 
			flag[int(searchp->pointstart-'A')]+flag[int(searchp->pointend-'A')]==2)
		//此时searchp涉及边的起点和终点均在已选行列，舍弃，否则构成回路。
		{
			list[0].headp->next=searchp->next;
			delete searchp;  //释放空间
			searchp=list[0].headp->next;//重新启动搜索指针
		}
		//此时searchp指向一个有效边，将其加入到list[1]中，并且将结点加入已选行列
		i=flag[int(searchp->pointstart-'A')]<flag[int(searchp->pointend-'A')]?
			(searchp->pointstart-'A'):(searchp->pointend-'A');//选取小者标志位
		flag[i]=1;
		newnode=new node(searchp->pointstart,searchp->pointend,searchp->weight);//三个数据存入结点
		newnode->next=NULL;
		if(list[1].empty()) //如果此时为空
		{
			list[1].headp->next=newnode;
			listrear=newnode;//启用一个链表的尾部指针用于每次插入在最后的位置上
		}
		else
		{
			listrear->next=newnode;//挂链到最后一个结点
			listrear=newnode;//移动尾部指针，为下一次挂链做准备
		}
		list[1].number++;
	}
	for(i=0;i<nodenumber;i++)//扫描判断是否为最小生成树，全部标志位为1则可构成最小生成树，否则不连通
		if(flag[i]!=1 && delflag[i]==0)   //最终状态是全部标志位为1，否则不能构成最小生成树
		{
			cout<<endl<<"【温馨提示】"<<endl
				<<"	1.标志值为0表示为暂未选入的结点点群；"<<endl
				<<"	2.标志值为1表示已被选入的结点群；"<<endl
				<<"	3.标志值为 ▅ 表示已删除结点群。"<<endl<<endl;
			failflag();          //显示标志位信息
			return fail;
		}
	float total=0;					//总权值清零
	searchp=list[1].headp->next;	//对结果链表进行扫描
	while(searchp!=NULL)			//显示最小生成树信息
	{
		searchp->display();			//显示当前边的信息
		total+=searchp->weight;		//累加最小生成树的权值
		searchp=searchp->next;
	}
	cout<<endl<<"最小生成树的总权值为："<<total<<endl;//显示总权值
	return success;
}
returninfo minispantree::kruskal() //kruskal算法
{
	char nodenamestart,nodenameend;				//边的开始结点名，结束结点名
	node *newnode,*searchp,*followp,*listrear;	//新结点、搜索指针、尾随指针、链表尾部指针
	int mark=0;									//mark标志记录当前结点属于哪个边集
	int noderow,nodecol,tempvalue,tempbigger;	//结点对应的行、列，临时存储使用的变量名两个
	int nodeflag;						//标志链表结点是否可以进入最小生成树，为1进入，为0失败
	int i,j,k;							//循环变量名
	for(k=0;k<nodenumber;k++)			//是否已经进入最小生成树的标志位全部清零
		flag[k]=0;
	list[2].clearlist();				//每次开始时将初始链表和最终结果链表清空
	list[3].clearlist();  
	//list[4]：2、3坐标表示kruskal算法的初始链表和最终结果链表
	for(i=0;i<nodenumber-1;i++)//扫描邻接矩阵中所有结点所在行和列
		for(j=i+1;j<nodenumber;j++)//用行优先法处理处理上三角矩阵的所有非0的权值
		{
			if(MGraph[i][j]!=0) //将非零的权值涉及的行列坐标和权值数据加入到链表中【按权值升序排列】
			{
				nodenamestart=i+'A';//利用Ascii码把行坐标转换成结点名
				nodenameend=j+'A';  //利用Ascii码把列坐标转换成结点名
				newnode=new node(nodenamestart,nodenameend,MGraph[i][j]);
				//申请新结点，把边涉及的两个结点和权值存入
				if(list[2].empty()) //如果此时链表为空，则作为第一个结点挂入
				{
					newnode->next=NULL;
					list[2].headp->next=newnode;
				}
				else
				{
					followp=list[2].headp;
					searchp=list[2].headp->next;
					while(searchp!=NULL && searchp->weight<MGraph[i][j])//为了保证有序，找正确位置
					{
						followp=searchp;
						searchp=searchp->next;
					}
					newnode->next=searchp;//找到后挂链，保持权值从小到大排列
					followp->next=newnode;
				}
				list[2].number++;//结果链表个数计数器加一
			}
		}
	//下面将从有序链表结点中按照从小到大的次序选出最小生成树合法的边
	searchp=list[2].headp->next;//启动搜索指针
	while(searchp!=NULL && list[3].number!=nodenumber-1)//当链表没有完而且产生的边数不够时继续产生
	{
		nodeflag=1; //每次开始重新设置为1，假设当前结点是可以加入最小生成树的
		noderow=searchp->pointstart-'A';//把当前起点的结点名换为原邻接矩阵中的行坐标
		nodecol=searchp->pointend-'A';  //把当前终点的结点名换为原邻接矩阵中的列坐标
		if(flag[noderow]+flag[nodecol]==0)  //如果都是为0，说明这两个结点都可以进入最小生成树
		{
			flag[noderow]=++mark;//每当新的边集合开始时标志位不断增加1，用来判断该图是否是联通图
			flag[nodecol]=mark;
		}
		else if(flag[noderow]*flag[nodecol]==0) //只有一个为0
		{
			tempvalue=(flag[noderow]>flag[nodecol])?flag[noderow]:flag[nodecol]; //选择非零的值
			flag[noderow]=tempvalue;//目的是保持进入当前的边集中
			flag[nodecol]=tempvalue;
		}
		else if(flag[noderow]*flag[nodecol]!=0) //如果都不为0的情况，分情况讨论
		{
			if(flag[noderow]==flag[nodecol]) //标志位两者相等，说明在一个边集中，也就是环，必须舍弃
				nodeflag=0;                   //结点舍弃通过标志位翻转为0达成，此中只有这一种情况
			else      //两者都不为0且不相等，说明开始时不在一个边集中，现在联通了，需要合并边集，故取小值
			{
				tempvalue=(flag[noderow]<flag[nodecol])?flag[noderow]:flag[nodecol]; //准备小的标志位
				tempbigger=(flag[noderow]>flag[nodecol])?flag[noderow]:flag[nodecol];//记录大的标志位
				for(k=0;k<nodenumber;k++)//所有标志位扫描，等于大标志位的全部刷新为小的标志位
					if(flag[k]==tempbigger)
						flag[k]=tempvalue;
			}
		}
		else     //如果有其他现象则表明有错并且显示所有结点的标志
		{
			return error;
		}
		if(nodeflag==1)//表示这个结点符合最小生成树的条件
		{
			//将此结点添加到最终状态链表中【尾插法】
			newnode=new node(searchp->pointstart,searchp->pointend,searchp->weight);
			newnode->next=NULL;
			if(list[3].empty()) //如果此时链表为空，则作为第一个结点挂入
			{
				list[3].headp->next=newnode;
				listrear=newnode;//启用一个链表的尾部指针用于每次插入在最后的位置上
			}
			else
			{
				listrear->next=newnode;//挂链到最后一个结点
				listrear=newnode;//移动尾部指针，为下一次挂链做准备
			}
			list[3].number++;//计数器加一
		}
		searchp=searchp->next;//继续处理下一个结点，边数足够时马上停止
	}
	for(k=0;k<nodenumber;k++)//扫描判断是否为最小生成树，全部标志位为1则可构成最小生成树，否则不连通
		if(flag[k]!=1 && delflag[k]==0)   //只要遇到一个结点标志位不为1而且不是被删除的结点，则失败
		{
			cout<<endl<<"【温馨提示】"<<endl<<"	1.标志值为0表示为孤立结点；"
				<<endl<<"	2.标志值为非0且相等的表示互联的结点集合；"
				<<endl<<"	3.标志值为 ▅ 表示已删除结点集合。"<<endl<<endl;
			failflag();				//显示标志位信息
			return fail;			//直接退出
		}
	float total=0;//总权值累加器清零
	searchp=list[3].headp->next;//启动搜索指针
	while(searchp!=NULL)//显示最后最小生成树的边
	{
		searchp->display();//每一个结点的三个值被依次输出
		total+=searchp->weight;//总权值累加
		searchp=searchp->next;//移动链表搜索指针
	}
	cout<<endl<<"最小生成树的总权值为："<<total<<endl;//显示总权值
	return success;
}

//界面类
class interfacebase
{
private:
	minispantree listonface;  //定义一个对象listonface
public:
	void clearscreen(void);
	void showmenu(void);
	int  userchoice(void);
	void processmenu(char choice);
};
void interfacebase::clearscreen(void)
{
    system("cls");
}
void interfacebase::showmenu(void)
{
  	cout<<"   电话通信网最小生成树功能演示菜单  "<<endl;
    cout<<"====================================="<<endl;
    cout<<"1.文件读取结点、边和权值信息			"<<endl;
    cout<<"2.增加或删除结点						"<<endl;
	cout<<"3.增加或删除边						"<<endl;
    cout<<"4.修改权值							"<<endl;
    cout<<"5.显示当前邻接矩阵					"<<endl;
	cout<<"6.Prim算法(普利姆算法)				"<<endl;
	cout<<"7.Kruskal算法(克鲁斯卡尔算法)		"<<endl;
    cout<<"8.结束程序							"<<endl;
	cout<<"====================================="<<endl;
}
int interfacebase::userchoice(void)
{	char choice;
	cout<<"请输入您的选择：";
	cin>>choice;
	return choice;
}
void interfacebase::processmenu(char choice)
{
	int returnvalue;

	switch(choice)    //根据用户的选择进行相应的操作
	{
	case '1':
		if(!listonface.readfile())
		{
		cout<<endl<<endl<<"放弃读文件或读文件出错，按任意键继续..."<<endl;
		break;
		}
		else
		{
			cout<<"成功读入文件中的结点、边和权值等信息!构建邻接矩阵如下："<<endl<<endl;
			listonface.traveral();                 //显示邻接矩阵
			datamark=1;
			cout<<endl<<endl<<"操作完成，按任意键继续..."<<endl;
		}
		break;
	case '2':
		returnvalue=listonface.nodeinsdel();
		if(returnvalue==fail)
			cout<<endl<<endl<<"成功退出该项操作!请按任意键继续..."<<endl;
		else if(returnvalue==error)
			cout<<endl<<endl<<"输入的数据有错，操作失败!请按任意键继续..."<<endl;
		else
		{
			cout<<endl<<endl<<"操作成功!请按任意键继续..."<<endl;
			datamark=1;
		}
		break;
	case '3':
		if(datamark==0)
		{
			cout<<endl<<"目前没有图的信息，无法操作!请按任意键继续..."<<endl;
			break;
		}
		returnvalue=listonface.edgeinsdel();
		if(returnvalue==fail)
			cout<<endl<<endl<<"成功退出该项操作!请按任意键继续..."<<endl;
		else if(returnvalue==error)
			cout<<endl<<endl<<"输入的数据有错，操作失败!请按任意键继续..."<<endl;
		else
			cout<<endl<<endl<<"操作成功!请按任意键继续..."<<endl;
		break;
	case '4':
		if(datamark==0)
		{
			cout<<endl<<"目前没有图的信息，无法操作!请按任意键继续..."<<endl;
			break;
		}
		returnvalue=listonface.edgemodify();
		if(returnvalue==fail)
			cout<<endl<<endl<<"成功退出该项操作!请按任意键继续..."<<endl;
		else if(returnvalue==error)
			cout<<endl<<endl<<"输入的数据有错!请按任意键继续..."<<endl;
		else
			cout<<endl<<endl<<"操作成功!请按任意键继续..."<<endl;
		break;
	case '5':
		if(datamark==0)
		{
			cout<<endl<<"目前没有图的信息，无法操作!请按任意键继续..."<<endl;
			break;
		}
		cout<<endl<<endl<<"当前系统中的邻接矩阵信息如下："<<endl<<endl;
		listonface.traveral();
		cout<<endl<<endl<<"信息显示成功!请按任意键继续..."<<endl;
		break;
	case '6':
		if(datamark==0)
		{
			cout<<endl<<"目前没有图的信息，无法操作!请按任意键继续..."<<endl;
			break;
		}
		cout<<endl<<"您选择了Prim算法："<<endl;
		returnvalue=listonface.prim();
		if(returnvalue==error)
			cout<<endl<<endl<<"数据有错，计算失败!请按任意键继续..."<<endl;
		else if(returnvalue==fail)
			cout<<endl<<endl<<"构成最小生成树的条件不满足!请按任意键继续..."<<endl;
		else
			cout<<endl<<endl<<"Prim算法成功!请按任意键继续..."<<endl;
		break;
	case '7':
		if(datamark==0)
		{
			cout<<endl<<"目前没有图的信息，无法操作!请按任意键继续..."<<endl;
			break;
		}
		cout<<endl<<"您选择了Kruskal算法："<<endl;
		returnvalue=listonface.kruskal();
		if(returnvalue==fail)
			cout<<endl<<endl<<"构成最小生成树的条件不满足!请按任意键继续..."<<endl;
		else if(returnvalue==error)
			cout<<endl<<endl<<"数据有错，计算失败!请按任意键继续..."<<endl;
		else
			cout<<endl<<endl<<"Kruskal算法成功!请按任意键继续..."<<endl;
		break;
	case '8':
				cout<<endl<<endl<<"您已经成功退出本系统，欢迎再次使用!!!"<<endl;
		        exit(0);
	default:
				cout<<endl<<endl<<"对不起，您输入的功能编号有错!请重新输入!!!"<<endl;
		    	break;
	}
}
int main(void)                     //程序主入口
{
	char choice;
	system("color f0");
	interfacebase interfacenow;
	interfacenow.clearscreen();
    while (1)
	{
  		interfacenow.showmenu();
		choice=interfacenow.userchoice();
		interfacenow.processmenu(choice);
		getch();
		interfacenow.clearscreen();
    }
    return 0;
}//主函数结束
