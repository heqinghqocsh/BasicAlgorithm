/*功能描述：
图的相关功能实现，存储结构使用邻接矩阵
*/
#include<windows.h>
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
enum returninfo {success,fail,overflow,underflow,nolchild,norchild,nofather,havesonl,havesonr,
                 haveason,havetwosons,range_error,quit};	//定义返回信息清单
int build;//用于控制是否是重建图，为0时表示第一次建立图，为1时表示重建图
/************************************************************/
//顺序表类 把图中结点用顺序表来存储解决图中结点的动态插删问题
const int MaxListSize=26;//约定本顺序表最多只存26个字母
class SeqList
{
private:
	char node[MaxListSize];//启用0坐标，即0-25号坐标
	int size;
public:
	SeqList();
	~SeqList();
	int ListSize()const;
	int ListEmpty()const;
	int Find(char &item)const;
	char Getdata(int pos)const;
	void Insert(const char&item,int pos);
	int Delete(const int pos);
	void ClearList();
};
SeqList::SeqList()//顺序表的构造函数
{
	size=0;
}
SeqList::~SeqList(){}//顺序表的析构函数
int SeqList::ListSize()const//求顺序表的结点个数的函数
{
	return size;
}
int SeqList::ListEmpty()const//判断顺序表是否为空的函数
{
	if(size==0)
		return 1;
	else
		return 0;
}
int SeqList::Find(char &item)const//查找某个结点的函数
{
	if(size==0)
	{
		return -1;
	}
	int i=0;
	while(i<size && item!=node[i]){i++;}
	if(i<size)
	{
		return i;
	}
	else return -1;
}
char SeqList::Getdata(int pos)const//读取某个位置结点的函数
{
	if(pos<0||pos>size-1)
	{
		cout<<"对不起!位置参数越界出错!"<<endl;
		return(false);
	}
	return node[pos];
}
void SeqList::Insert(const char &item,int pos)//插入一个结点到顺序表中
{
	int i;
	if(size==MaxListSize)
	{
		cout<<"顺序表已满无法插入!"<<endl;
		return;
	}
	else if(pos<0||pos>size)//插入在最后一个元素右边是合法的
	{
		cout<<"对不起!位置参数越界出错!"<<endl;
		return;
	}
	else
	{
		for(i=size;i>pos;i--)
		{
			node[i]=node[i-1];
			cout<<node[i]<<"//////////////////"<<endl;
		}
		node[pos]=item;
		size++;
	}
}
//从顺序表中删除一个结点
int SeqList::Delete(const int pos)
{
	if(size==0)
	{
		cout<<"顺序表已空无法删除!"<<endl;
		return 0;
	}
	else if(pos<0||pos>size-1)
	{
		cout<<"对不起!位置参数越界出错!"<<endl;
		return 0;
	}
	else
	{
		char temp=node[pos];
		for(int i=pos;i<size-1;i++)
		{
			node[i]=node[i+1];
		}
		size--;
		return 1;
	}
}
void SeqList::ClearList()//销毁整个顺序表
{
	size=0;
}
/***************************************************************************/
//队列类：解决图的广度优先遍历
const int maxsize=100;
//定义了循环队列的类
class SeqQueue
{
private:
	char queuedata[maxsize];//限制最多的元素个数
	int  front;//定义一个队首指针
	int  rear;//定义一个队尾指针
	int  count;//元素个数计数器
public:
	SeqQueue(void);//构造函数
	~SeqQueue(){};//析构函数
	int  isempty()const{return front==rear;}
	void enqueue(const char&item);//元素入队函数
	char dequeue();//出队函数
	void showseq();//遍历函数
	void getfront();//返回头结点的函数
};
SeqQueue::SeqQueue()
{
	front=0;//头尾指针各占一个空间，那么总的可以储存的元素的个数为maxsize-1
	rear =0;
	count=0;//计数器开始为0
}
void SeqQueue::enqueue(const char&item)
{
	if(front==(rear+1)%maxsize)//队列满的条件
	{
		cout<<"对不起!队列已满!无法添加!"<<endl;
	}
	else
	{
		queuedata[rear]=item;//否则元素从队尾入队
		rear=(rear+1)%maxsize;//队尾先加一后取模
		count++;//计数器加一
	}
}
char SeqQueue::dequeue()
{
	if(count==0)//队列为空的条件
	{
		cout<<"对不起!队列已空!无法删除!"<<endl;
		return false;
	}
	else
	{
		char datatemp=queuedata[front];//否则元素从队头出队
		front=(front+1)%maxsize;//队头后移
		count--;//元素个数减一
		return datatemp;
	}
}
void SeqQueue::showseq()
{
	cout<<"队列全部元素如下:"<<endl;
	for(int i=front;i!=rear;)//队首并未存储元素故要从front开始遍历
	{
		cout<<" "<<queuedata[i];
		i=(i+1)%maxsize;
	}
	cout<<endl;
	cout<<"当前元素个数为: "<<count<<endl;
	cout<<endl;
}
void SeqQueue::getfront()
{
	if(count==0)//队列为空的条件
	{
		cout<<"对不起!队列已空!"<<endl;
		return;
	}
	else
	{
		cout<<"队头的元素的值为 :"<<queuedata[front]<<endl;
	}
}
/////////////
//图类
const int maxvertices=26;//定义结点个数最大值为26 
const int maxweight=10000;//当两个结点之间不存在边时距离无穷大用10000来模拟
class graph
{
private:
	int i,j;											//循环变量
	int flag;											//标志位
	int inputnodenum,inputedgenum;							//输入的结点个数、边数
	int numofedges;										//记录边的条数
	char *nodearray;									//输入结点时使用的一维数组
	SeqList Vertices;									//图的结点信息，启用了一个线性表
	int Edge[maxvertices][maxvertices];					//图的边信息,使用了一个二维数组，是一个方阵 
	

	char nodesarray[11];								//教材中拓扑排序范例的结点个数建立的数组
	int	 topologicalSort[maxvertices];					//存储进入拓扑排序的结点编号
	int  Indegree[maxvertices];							//有向图所有顶点入度数组
	int  deleflag[maxvertices];							//标记已逻辑删除顶点
public:
	graph(const int size=maxvertices);					//图的构造函数
	~graph(){};											//图的析构函数
	void initializationofEdge(int size);				//边的邻接矩阵初始化 
    void inputdata(void);								//手工输入数据
	void autocreatgraph();								//启用默认数据
	void showgraph();									//显示图的邻接矩阵
	void showVertex();									//显示图的结点
	int  graphempty()const{return Vertices.ListEmpty();}//判断图是否为空
	int  numofVertices(){return Vertices.ListSize();}	//求图的结点个数
	int  numofEdges(void){return numofedges;}			//求图的边数
	char getvalue(const int i);							//求取图某个结点的值
	int  getweight(const int nodestart,const int nodeend);//求两个结点之间的边的权值
	void insertVertices(const char& vertices);			//向图中添加一个结点
	int  deleteVertex(const int v);						//删除一个结点
	int  insertEdge(const int nodestart,const int nodeend,int weight);//添加一条边
	int  deleteEdge(const int nodestart,const int nodeend);//删除一条边
	int  getfirstneighbor(const int v);//为实现图的遍历而必须定义的求取其第一个相邻结点的函数
	int  getnextneighbor(const int nodestart,const int nodeend);//求取其下一个相邻结点的函数
	void depthfirstsearch(const int v,int visited[],void visit(char item));//深的优先遍历
	void breadthfirstsearch(const int v,int visited[],void visit(char item));//广度优先遍历
	

	void initopological();								//拓扑排序环境初始化
	void datafortopological();							//为拓扑排序准备数据
	void topological();									//拓扑排序函数
};
graph::graph(const int size)//图的构造函数
{
	initializationofEdge(maxvertices); 
}
void graph::initializationofEdge(int size)  //边的邻接矩阵初始化
{
	for(int i=0;i<size;i++)//邻接矩阵的初始化
	{
		for(int j=0;j<size;j++)
			if(i==j)
			{
				Edge[i][j]=0;//两个相同结点之间的边的权值为0
			}
			else
				Edge[i][j]=maxweight;//初始状态不同结点之间不存在边，权值无穷大用10000来表示
	}
	numofedges=0;//初始状态边的条数为0
}
void graph::showgraph()//图的显示函数
{
	for(i=0;i<Vertices.ListSize();i++)//用邻接矩阵来模拟图的边的相关信息
	{
		for(j=0;j<Vertices.ListSize();j++)
		{
			if(getweight(i,j)==maxweight)
				cout<<setw(5)<<"∞";//表示两个结点之间没有边
			else
				cout<<setw(5)<<getweight(i,j);
		}
		cout<<endl;
	}
}
void graph::showVertex()//显示图的结点
{
	for(i=0;i<Vertices.ListSize();i++)//显示坐标
		cout<<setw(5)<<i;
	cout<<endl;
	for(i=0;i<Vertices.ListSize();i++)//显示数据
		cout<<setw(5)<<Vertices.Getdata(i);
	cout<<endl;
}
char graph::getvalue(const int i)//求取图的某个结点的值
{
	if(i<0||i>Vertices.ListSize())
	{
		cout<<"对不起参数越界出错!"<<endl;
		return false;
	}
	else
		return Vertices.Getdata(i);//采用顺序表的操作达成目标
}
int graph::getweight(const int nodestart,const int nodeend)//求两个结点之间的边的权值
{
	if(nodestart<0||nodestart>Vertices.ListSize()||nodeend<0||nodeend>Vertices.ListSize())
	{
		cout<<"对不起参数越界出错!"<<endl;
		return false;
	}
	else
		return Edge[nodestart][nodeend];
}
void graph::insertVertices(const char& vertices)//添加一个结点
{
	Vertices.Insert(vertices,Vertices.ListSize());//为了简单把添加结点放在顺序表的最后位置
}
int graph::deleteVertex(const int v)//删除一个结点
{
	for(int i=0;i<Vertices.ListSize();i++)//删除结点必须把与这个结点相关联的全部的边首先删除
		for(int j=0;j<Vertices.ListSize();j++)
		{
			if(i==v||j==v && Edge[i][j]>0 && Edge[i][j]<maxweight)
			{
				Edge[i][j]=maxweight;
				numofedges--;
			}
		}
	int flag=Vertices.Delete(v);
	if(flag==1)//提供一个标志位为后面的调用方便
		return 1;
	else
		return 0;
}
int graph::insertEdge(const int nodestart,const int nodeend,int weight)//添加一条边
{
	if(nodestart<0||nodestart>Vertices.ListSize()||nodeend<0||nodeend>Vertices.ListSize())
	{
		cout<<"对不起参数越界出错!"<<endl;
		return 0;
	}
	else
	{
		Edge[nodestart][nodeend]=weight;
		numofedges++;
		return 1;
	}
}
int graph::deleteEdge(const int nodestart,const int nodeend)//删除一条边
{
	if(nodestart<0||nodestart>Vertices.ListSize()||nodeend<0||nodeend>Vertices.ListSize())
	{
		cout<<"对不起参数越界出错!"<<endl;
		return 0;
	}
	else
	{
		Edge[nodestart][nodeend]=maxweight;
	    numofedges--;
		return 1;
	}
}
int graph::getfirstneighbor(const int v)//求取其第一个相邻结边
{
	if(v<0||v>Vertices.ListSize())
	{
		cout<<"对不起参数越界出错!"<<endl;
		return false;
	}
	else
	{
		for(int col=0;col<=Vertices.ListSize();col++)
		{
			if(Edge[v][col]>0 && Edge[v][col]<maxsize)
				return col;//若存在相邻的结点返回其下标
		}
		return -1;//否则返回-1
	}
}
int graph::getnextneighbor(const int nodestart,const int nodeend)//求取其下一条邻接边
{//找结点nodestart的<nodestart,nodeend>邻接边的下一条邻接边
	if(nodestart<0||nodestart>Vertices.ListSize()||nodeend<0||nodeend>Vertices.ListSize())
	{
		cout<<"对不起参数越界出错!"<<endl;
		return false;
	}
	else
	{//使col为nodeend+1因此寻找的边是nodestart的<nodestart,nodeend>邻接边的下一条邻接边
		for(int col=nodeend+1;col<=Vertices.ListSize();col++)
		{
			if(Edge[nodestart][col]>0&&Edge[nodestart][col]<maxsize)
				return col;
		}
		return -1;
	}
}
void graph::depthfirstsearch(const int startpoint,int visited[],void visit(char item))//深度优先遍历
{
	int neighborpoint;
	visit(getvalue(startpoint));//访问结点startpoint
	visited[startpoint]=1;//标记结点startpoint已经被访问
	neighborpoint=getfirstneighbor(startpoint);//求结点startpoint的第一个邻接结点
	while(neighborpoint!=-1)//当邻接结点存在时循环
	{
		if(!visited[neighborpoint])
			depthfirstsearch(neighborpoint,visited,visit);//对结点startpoint递归
		neighborpoint=getnextneighbor(startpoint,neighborpoint);
		//结点neighborpoint为<startpoint,neighborpoint>邻接边的下一个邻接结点
	}
}
void graph::breadthfirstsearch(const int startpoint,int visited[],void visit(char item))//广度优先遍历
{
	char getqueuehead,neighborpoint;
	SeqQueue queue;
	visit(getvalue(startpoint));//访问初始结点startpoint
	visited[startpoint]=1;//标记startpoint已经访问
	queue.enqueue(startpoint);//结点startpoint入队
	while(!queue.isempty())//步骤1：当队列非空时继续执行
	{
		getqueuehead=queue.dequeue();//出队取队头结点getqueuehead
		neighborpoint=getfirstneighbor(getqueuehead);//查队头结点的第一个邻接结点neighborpoint
		while(neighborpoint!=-1)//步骤2：若结点neighborpoint存在则继续执行 否则返回步骤1
		{
			if(!visited[neighborpoint])//若结点neighborpoint尚未被访问
			{
				visit(getvalue(neighborpoint));//访问结点neighborpoint
				visited[neighborpoint]=1;//标记neighborpoint已经访问
				queue.enqueue(neighborpoint);//结点neighborpoint入队
			}
			neighborpoint=getnextneighbor(getqueuehead,neighborpoint);
			//查结点startpoint,neighborpoint的下一个邻接结点为neighborpoint 返回步骤2
		}
	}
}
void printchar(char item)
{
	cout<<setw(5)<<item;
}
void graph::initopological()//拓扑排序环境初始化
{
	Vertices.ClearList();					//结点数组清空
	initializationofEdge(maxvertices); 	
	for(j=0;j<maxvertices;j++)				//初始化结果数组、入度数组、删除标志数组
	{
	   topologicalSort[j]=0;
	   Indegree[j]=0;						//用列下标统计入度，便于理解
	   deleflag[j]=0;
	}
}
void graph::inputdata(void)
{
	int nodestart,nodeend,weight;//起始点、终止点、权值
	cout<<"下面添加结点信息!"<<endl;
	cout<<"----------------"<<endl;
	cout<<"请输入结点个数(小于 "<<maxvertices<<"):";
	cin>>inputnodenum;
    nodearray=new char[inputnodenum];//建立字符数组
	cout<<"请输入"<<inputnodenum<<"个结点(单个Ascii码字符)，空格隔开，输入完毕后回车:"<<endl;
	for(i=0;i<inputnodenum;i++)
		{
			cin>>nodearray[i];
			insertVertices(nodearray[i]);	
		}
	cout<<inputnodenum<<"个结点已经添加成功了!字符的的默认编号是:"<<endl;
	for(i=0;i<inputnodenum;i++)//显示对应坐标	
		cout<<setw(5)<<i;
	cout<<endl;
	for(i=0;i<inputnodenum;i++)//显示数组中字符
		cout<<setw(5)<<nodearray[i];
	cout<<endl<<endl;
	cout<<"下面添加边信息!"<<endl;
	cout<<"---------------"<<endl;
	cout<<"请输入边数: ";
	cin>>inputedgenum;
	cout<<"例如:1 2 1 表示添加了一条边(从1号结点到2号结点，权值为1)!:"<<endl;
	for(i=0;i<inputedgenum;i++)
	{
		cout<<"下面添加第"<<i+1<<"条边的信息: "<<endl;
	    cin>>nodestart>>nodeend>>weight;
        flag=insertEdge(nodestart,nodeend,weight);
		if(flag==1)
			cout<<"从"<<nodestart<<"号结点"<<"到"<<nodeend<<"号结点之间已经添加了权值为"
			    <<weight<<"的一条边!"<<endl<<endl;
	}
	cout<<"图已经建立!"<<endl;
	//delete[] nodearray;
	build=1;
}
////////////////
void graph::datafortopological()//为拓扑排序准备数据，无环有向图
{
	inputnodenum=11;						//教材范例的结点个数
	inputedgenum=13;						//教材范例的边数

	nodesarray[0]='a';
	nodesarray[1]='b';
	nodesarray[2]='c';
	nodesarray[3]='d';
	nodesarray[4]='e';
	nodesarray[5]='f';
	nodesarray[6]='g';
	nodesarray[7]='h';
	nodesarray[8]='i';
	nodesarray[9]='j';
	nodesarray[10]='k';
	for(i=0;i<inputnodenum;i++)//拷贝到结点数组中			
		insertVertices(nodesarray[i]);				

	insertEdge(0,2,1);//教材范例实际边的信息，两个结点可以抵达时矩阵的相关位置设置为1
	insertEdge(0,3,1);
	insertEdge(1,3,1);
	insertEdge(1,4,1);
	insertEdge(2,5,1);
	insertEdge(3,5,1);
	insertEdge(4,6,1);
	insertEdge(5,7,1);
	insertEdge(6,8,1);
	insertEdge(6,9,1);
	insertEdge(7,10,1);
	insertEdge(8,10,1);
	insertEdge(9,10,1);
	build=1;
}
void graph::topological()
{
	int tempcount;						//临时计数器
	for(j=0;j<inputnodenum;j++)			//求所有结点的入度，从每一列开始扫描，然后看哪一行进入
	{
		tempcount=0;					//本次临时计数器记录每一列中1的个数
		for(i=0;i<inputnodenum;i++)		//列优先扫描
			if(getweight(i,j)==1)
				tempcount++;			//两点通达则入度加1
		Indegree[j]=tempcount;			//每一列统计完毕后存入入度数组的下标位置
	}
	cout<<endl<<"所有结点入度如下:"<<endl;//显示入度信息
	for(j=0;j<inputnodenum;j++)
		cout<<nodesarray[j]<<"=>"<<Indegree[j]<<"  ";
	cout<<endl;
	tempcount=0;//本次临时计数器记录逻辑删除点的个数，同时正好等于进入拓扑排序结果数组的下标控制变量
	for(i=0;i<inputnodenum;i++)//从每一个结点开始检测
		if((Indegree[i]==0) && (deleflag[i]==0))//入度为0和删除标记为0的顶点
		{
			topologicalSort[tempcount]=i;//输出到结果数组中
			tempcount++;                 //计数器加1，同时为下标
			for(j=0;j<inputnodenum;j++)  //逻辑上删除该点后，每一列扫描一次
				if(getweight(i,j)==1)    //如果发现该列的该行原来为1
					Indegree[j]--;       //在入度数组中将该结点的入度减1
			deleflag[i]=1;               //在删除标记数组中将该结点删除标记翻转为1
		}
	if(tempcount==inputnodenum)//如果全部结点都进入了拓扑序列，说明该有向图没有环路
	{ 
		cout<<endl<<"有向图的拓扑序列为："<<endl;//输出拓扑序列
		for(i=0;i<inputnodenum;i++) 
			if(i==inputnodenum-1)
				cout<<"["<<nodesarray[topologicalSort[i]]<<"]";//最后一个结点
			else 
				cout<<"["<<nodesarray[topologicalSort[i]]<<"]"<<"→";//中间结点
		cout<<endl;
	}
	else
		cout<<"本有向图不存在拓扑序列，有环路存在!"<<endl;

} 
////////////////
//界面处理对象：界面库
class interfacebase
{
private:
	int i;							//循环变量
	int nodestart,nodeend,weight;	//起始点、终止点、权值
	int flag;						//标志位
    graph graphnow;					//图对象的实例化
public:
	void showmenu(void);
    void processmenu(void);
};
void interfacebase::showmenu(void)
{
    cout<<"=================================="<<endl;
    cout<<"      图的拓扑排序功能演示        "<<endl;
    cout<<"=================================="<<endl;
    cout<<"1.手工建立图  					 "<<endl;
	cout<<"2.启用默认数据建立图 		     "<<endl;
    cout<<"3.用矩阵形式显示图				 "<<endl;
	cout<<"4.求解拓扑排序问题				 "<<endl;
    cout<<"0.退出							 "<<endl;
    cout<<"=================================="<<endl;
}
void interfacebase::processmenu()
{
    char choice,yesno;			//用于用户选择菜单选项
	//char newnode;
	//int *visited;
    cout<<"请输入选项：";
    cin>>choice;
    switch(choice)
    {
    case '1':
		cout<<"================"<<endl;
		if(build==1)
		{
        	cout<<"危险操作，原有数据将被删除!你确定吗?确定按(Y||y)键!否则按任意键!"<<endl;
			cin>>yesno;
			if(yesno!='y' && yesno!='Y')
			{
				cout<<"已经取消建立图!"<<endl;
				break;
			}
		}
		graphnow.initopological();
		graphnow.inputdata();
		cout<<"================"<<endl;
        break;
	case '2':
		cout<<"================"<<endl;
		if(build==1)
		{
        	cout<<"危险操作，原有数据将被删除!你确定吗?确定按(Y||y)键!否则按任意键!"<<endl;
			cin>>yesno;
			if(yesno!='y' && yesno!='Y')
			{
				cout<<"已经取消建立图!"<<endl;
				break;
			}
		}
		graphnow.initopological();
		graphnow.datafortopological();
		cout<<"调入默认数据成功!!!"<<endl;
		cout<<"当前图的坐标和结点如下:"<<endl;
		graphnow.showVertex();
		cout<<"当前图的邻接矩阵如下:"<<endl;
        graphnow.showgraph();
		cout<<"================"<<endl;
        break;
    case '3':
        if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"图未建立，本次操作失败!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
		cout<<"================"<<endl;
		cout<<"当前图的坐标和结点如下:"<<endl;
		graphnow.showVertex();
		cout<<"当前图的邻接矩阵如下:"<<endl;
        graphnow.showgraph();
		cout<<"================"<<endl;
        break;
    case '4':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"图未建立，本次操作失败!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
        cout<<"================"<<endl;
		cout<<"当前图的坐标和结点如下:"<<endl;
		graphnow.showVertex();
		cout<<"当前图的邻接矩阵如下:"<<endl;
        graphnow.showgraph();
		graphnow.topological();
		cout<<"================"<<endl;
        break;
    case '0':
		cout<<"您选择了退出，谢谢使用..."<<endl;
        system("pause");
        exit(1);
    default:
        cout<<"输入有错，请重新输入..."<<endl;
    }
}
int main(void) //程序主入口
{
	system("color f0");
    system("cls");
    interfacebase interfacenow;
	build=0;
    while (1)
    {
        interfacenow.showmenu();
        interfacenow.processmenu();
        system("pause");
        system("cls");
    }
    return 0;
}//主函数结束

