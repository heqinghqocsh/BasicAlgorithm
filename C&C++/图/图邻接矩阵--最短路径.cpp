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
	
	int v0;												//解决最短路径问题使用的入口
	int *distance,*path;								//解决最短路径问题使用的距离数组和路径数组

	char nodesarray[11];								//教材中拓扑排序范例的结点个数建立的数组
	int	 topologicalSort[maxvertices];					//存储进入拓扑排序的结点编号
	int  InDegree[maxvertices];							//有向图所有顶点入度数组
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
	
	void datafordijkstra();								//为求最短路径问题准备数据
	void dijkstra(int v0,int distance[],int path[]);	//求最短路径问题的函数
	void dodijkstra();									//启动最短路径函数的入口
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
void graph::inputdata(void)
{
	int nodestart,nodeend,weight;//起始点、终止点、权值
	Vertices.ClearList();//结点数组清空
	initializationofEdge(maxvertices); 
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
	cout<<"例如:1 2 10 表示添加了一条边(从1号结点到2号结点，权值为10)!:"<<endl;
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
	delete[] nodearray;
	build=1;
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
////////////////
void graph::datafordijkstra()//为求最短路径问题准备数据
{
	Vertices.ClearList();				//结点数组清空
	initializationofEdge(maxvertices); 	//边数组初始化
	inputnodenum=6;						//结点数				
	inputedgenum=8;						//边数
	//                     0   1   2   3   4   5
	char defaultnodes[6]={'a','b','c','d','e','f'};//结点名称
	for(i=0;i<inputnodenum;i++)			
	{		
		insertVertices(defaultnodes[i]);//把结点存入存储结构				
	}		    													           
	insertEdge(0,2,10);					//把边的信息存入存储结构
	insertEdge(0,4,30);
	insertEdge(0,5,100);
	insertEdge(1,2,5);
	insertEdge(2,3,50);
	insertEdge(3,5,10);
	insertEdge(4,3,20);
	insertEdge(4,5,60);
	build=1;
}
void graph::dodijkstra()//启动最短路径函数的入口
{
	int *distance;
	inputnodenum=numofVertices();			//取回结点个数
	distance=new int[inputnodenum];			//距离数组
	path=new int[inputnodenum];				//路径数组
	cout<<"下面开始求某个结点到其他结点的最短距离..."<<endl;
	cout<<"请输入结点编号："<<0<<"~"<<inputnodenum-1<<endl;//提示给定入口
	cin>>v0;//给定入口
	if(v0>=0 && v0<=inputnodenum)			//结点编号参数正确
	{
		dijkstra(v0,distance,path);			//调用实际最短路径函数
		cout<<"从结点"<<getvalue(v0)<<"到其他各结点的最短距离为:"<<endl;
		for(i=0;i<inputnodenum;i++)
			if(distance[i]==10000)
				cout<<"到结点"<<getvalue(i)<<"的最短距离为: ∞"<<endl;
			else
				cout<<"到结点"<<getvalue(i)<<"的最短距离为:"<<distance[i]<<endl;
		cout<<endl;
		cout<<"寻找路径如下:"<<endl;
		cout<<"从结点"<<getvalue(v0)<<"到其他各结点最短路径的上一个结点为:"<<endl;
		for(i=0;i<inputnodenum;i++)
		{
			if(path[i]!=-1)
				cout<<"到结点"<<getvalue(i)<<"的上一个结点为:"<<getvalue(path[i])<<endl;
		}
	}
	else
	{
	cout<<"对不起!结点参数出错!按任意键继续……"<<endl;
	}
}
void graph::dijkstra(int v0,int distance[],int path[])
//求最短路径函数，参数：起点、距离数组、路径数组
{
	int inputnodenum;	
	inputnodenum=numofVertices();			//取回结点个数
	int *mark=new int[inputnodenum];		//标志位数组
	int mindis,nextnode;					//最短路径，下一个结点
	int i,j;								//循环变量
	for(i=0;i<inputnodenum;i++)				//初始化
	{
		distance[i]=getweight(v0,i);		//第一轮距离数组记录从起始点到其他所有点的边权值
		mark[i]=0;							//所有标志位清零
		if(i!=v0 && distance[i]<maxweight)	//如果起始结点可以抵达某个结点
			path[i]=v0;						//则把该结点首先放入路径数组
		else
			path[i]=-1;						//-1代表该路径不通
	}
	mark[v0]=1;								//把起点的标志位翻转为1
	for(i=1;i<inputnodenum;i++)				//在还没有找到最短路径的结点集合中选取最短距离结点nextnode
	{
		mindis=maxweight;					//首先约定最小距离为无穷大
		for(j=0;j<=inputnodenum;j++)		//扫描其它所有点
		{
			if(mark[j]==0 && distance[j]<mindis)//如果没有进入最短路径且距离小于最小距离
			{
				nextnode=j;					//记录本次边对面的点
				mindis=distance[j];			//记录本次最短路径
			}
		}
		if(mindis==maxweight)				//当不存在路径时算法结束
		{
			return;
		}
		mark[nextnode]=1;//标记结点nextnode已经放到了找到最短路径的的集合中
		for(j=0;j<inputnodenum;j++)//修改结点v0到其他的结点最短的距离
		{
			if(mark[j]==0 && getweight(nextnode,j)<maxweight			
				&& distance[nextnode]+getweight(nextnode,j)<distance[j])//发现新的最短路径
			{
				distance[j]=distance[nextnode]+getweight(nextnode,j);   //刷新最短路径
				path[j]=nextnode;										//把该点加入路径
			}
		}
	}
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
    cout<<"      图的最短路径功能演示        "<<endl;
    cout<<"=================================="<<endl;
    cout<<"1.手工建立图  					 "<<endl;
	cout<<"2.启用默认数据建立图 		     "<<endl;
    cout<<"3.用矩阵形式显示图				 "<<endl;
    cout<<"4.求解最短路径问题				 "<<endl;
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
		graphnow.datafordijkstra();
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
		graphnow.dodijkstra();
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

