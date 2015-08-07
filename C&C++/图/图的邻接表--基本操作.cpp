/*功能描述：
图用邻接表实现基本功能
*/
//本程序有部分源码需要进一步的完善
#include<windows.h>
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
enum returninfo {success,fail,overflow,underflow,nolchild,norchild,nofather,havesonl,havesonr,
                 haveason,havetwosons,range_error,quit
                };					//定义返回信息清单

#define  size 21//结点个数约定为20个，从1号地址开始使用
int build;		//标志位，提醒目前为空表
//结点对象
class Node                                       
{
public:
    int	  data;                                     
    Node *next;                             
    Node()                                       
    {                                           
        this->next = NULL;
    }
    Node(int data, Node *next=NULL)             //构造结点，指定元素和后继结点
    {
        this->data = data;
        this->next = next;
    }
};
//链表对象
class linklist                           
{    
private:	
	Node *head;								//单链表的头指针
public:
	int   length;							//数据个数
    linklist();								//构造函数     
    ~linklist();							//析构函数
	int   clearlink();						//清空链表中的数据
    int   setheadNULL();					//把头结点的链域置空
    void  printlinklist();					//遍历链表	
    Node *inserthead(int data);				//把结点插入在第一个位置作为头结点
    Node *insert(int x,int i);				//把x值插入到第i个位置           
    int   getheaddata();					//取回头结点中的值
	bool  del(int data) ;					//删除值为data的结点
    Node  *find(int value, Node* start);	//从start结点开始找值为value的结点      
    Node  *find(int value);					//查找值为value的结点
	int   *nodetoarraydata();				//把链表数据转换为数组数据
   	int   findsmallernum(int data);			//找到比data小的数据个数
	int   getnextnode(int i);				//返回邻接的下一个结点
};
linklist::linklist()          //构造空单链表
{
    this->head  =NULL;
	this->length=0;
}
linklist::~linklist()        
{
    this->head  =NULL;//链表结点释放此处没有写
}
int linklist::clearlink()//清除掉所有边信息的点
{
	Node *searchp=head->next;//head中存储的是结点名称
	Node *followp;
	while(searchp!=NULL)
	{
		followp=searchp;
		searchp=searchp->next;
		head->next=searchp;
		delete followp;
    }
	head->next=NULL;
  return 1;
}
int  linklist::setheadNULL()
{
	Node *temp=head;
	delete temp;
	head=NULL;
	return 1;
}
void linklist::printlinklist()//遍历链表所有结点
{
	Node *searchp=head;
	if(searchp==NULL)
		cout<<"无数据！";
	while(searchp!=NULL)                    //循环显示所有数据
	{
		cout<<"[ "<<searchp->data;   
		if (searchp->next==NULL) 
			cout<<" |^]"; 
		else 
			cout<<" |-]->";
		searchp=searchp->next;
	}
}
Node *linklist::inserthead(int data)
{
	Node *followp;
    followp = new Node(data, head);
    head = followp;
	length++;
	return followp;
}
Node *linklist::insert( int data,int pos) //插入data作为第pos个结点，返回新插入结点指针
{
    Node *followp;
	int j=0; 
	if (head==NULL || pos<=0)                      //头插入
    {
        followp = new Node(data, head);
        head = followp;
    }
    else                                        
    {
        Node *searchp=head;
	    while (searchp->next!=NULL&&j<pos-1)           //寻找插入位置
        {
            j++;
            searchp = searchp->next;
        }                                        //循环停止时，searchp指向第pos-1个结点或链表最后一个结点
        followp = new Node(data, searchp->next);             //插入data作为searchp结点的后继结点
        searchp->next = followp;
		length++;
    }
    return followp;
}
int linklist::getheaddata()//头结点是否为空
{
	if(head==NULL)
		return -1;
	else
		return head->data;
}
bool linklist::del(int data)  //删除data结点
{
    Node *searchp=head,*followp=head;
    while(searchp->next!=NULL && searchp->data!=data)
	{
		followp=searchp;
		searchp=searchp->next;
	}
	if(searchp->data==data)
	{
		followp->next=searchp->next;
		delete searchp;
		return true;
	}
	else   
		return false; 
}
Node *linklist::find(int value, Node *start)    //从单链表start结点开始顺序查找指定元素
{                                                
    Node *searchp=start;
    while (searchp!=NULL && searchp->data!=value)
	{
        searchp = searchp->next;
	}
    return searchp;
}
Node *linklist::find(int value)    
{
    if (head==NULL)
        return NULL;
    else
    return find(value, head->next); 
}
int *linklist::nodetoarraydata()
{
	int  *followp = new int[size];
	Node *searchp=head->next;
	int  i=1;
	while(searchp!=NULL)
	{
		
		followp[i]=searchp->data;
		i++;
		searchp=searchp->next;
	}
	followp[0]=i;
	return followp;
}
int linklist::findsmallernum(int data)//横向查找小于某个数据的个数
{

    Node *searchp=head->next;
	int nums=0;
    while (searchp!=NULL && searchp->data<data)
	{
       nums++;
	   searchp=searchp->next;
	}
	return nums;
}
int linklist::getnextnode(int pos)//取出从头结点后面开始的第pos个结点的值
{
	Node *searchp=head->next;
	int nextnum=1;//位置计数器
	while(searchp!=NULL && nextnum!=pos)
	{
		searchp=searchp->next;
		nextnum++;
	}
	if(searchp==NULL)
		return -1;
	else 
		return searchp->data;
}

//链式队列对象
class linkqueue                                //链式队列类
{
private:
	Node *front, *rear;                       //front、rear分别指向队首和队尾结点
public:
    linkqueue();                               //构造空队列
    ~linkqueue();                              //析构
    bool isempty();                              //判断是否空队列
    void enqueue(int x);                           //入队
    int  dequeue();                                 //出队，若队列空则抛出异常
    void printlinkqueue();
};
linkqueue::linkqueue()                    //构造空队列
{
    front = rear = NULL;
}
linkqueue::~linkqueue()                   //析构函数
{
    Node *searchp=front, *followp;
    while (searchp!=NULL)//释放空间
    {
        followp = searchp;
        searchp = searchp->next;
        delete followp;
    }
    front = rear = NULL;
}
bool linkqueue::isempty()                   //判断是否空队列
{
    return front==NULL && rear==NULL;
}
void linkqueue::enqueue(int x)               //入队
{
    Node *followp = new Node(x);
    if (isempty())
        front = followp;                               //空队插入
    else 
        rear->next = followp;                          //插入在队列之尾
    rear = followp;
}  
int linkqueue::dequeue()                      //出队，返回队头元素，若队列空则抛出异常 
{
    if (!isempty())
    {
       int x = front->data;                       //取得队头元素
       Node *searchp=front;
       front = front->next;                     //删除队头结点
       delete searchp;
       if (front==NULL)                         //空队列时，两指针同步
          rear = NULL;
       return x;
    }
	else 
		return -1;
}
void linkqueue::printlinkqueue()
{
	Node *searchp=front;
    while (searchp!=NULL)
    {
       
        cout<<searchp->data<<"---";
		searchp=searchp->next;
    }
}
void quickSort(int table[], int length, int low, int high)        //一趟快速排序，递归算法
{                                                          
    int lowtemp, hightemp;
    int basedata;                         
    if (low>=0 && low<length && high>=0 && high<length && low<high) 
    {
        lowtemp=low;
		hightemp=high;
        basedata=table[lowtemp];                         
        while (lowtemp!=hightemp)
        {
            while (lowtemp<hightemp && basedata<=table[hightemp])         
                hightemp--;
            if (lowtemp<hightemp)
                table[lowtemp++]=table[hightemp];             
            while (lowtemp<hightemp && table[lowtemp]<basedata)          
                lowtemp++;
            if (lowtemp<hightemp)
                table[hightemp--]=table[lowtemp];            
        }
        table[lowtemp]=basedata;                            
        quickSort(table, length, low, hightemp-1);           
        quickSort(table, length, lowtemp+1, high);        
    }
}
int *doquickSort(int array[], int length)               //快速排序
{
    quickSort(array, length, 0, length-1);				//四个参数：数组名、长度、两边的下标
    return array;
}
/////////////////////////////////////////////////////////
//图的邻接表对象
class ALGraph
{
private:
	linklist *Graph;					//构造一个链表的实例，起名为Graph
	linkqueue queue;					//构造一个链队的实例，起名为queue，为广度优先遍历准备
	int nodenumber;						//用于产生存放结点的下标位置，同时记录结点个数
	int edgenumber;						//实际边数记录
	int row;							//控制结点数组的行数
	int i;								//循环变量
	int nodenum,edgenum;				//临时存储结点数和边数
	int node[size];						//临时存储图的结点
	int *sortednodes;					//存储排序后的结点
	int startpoint,endpoint;			//起始结点和终止结点
public:
	ALGraph(int nodenumber=1,int edgenumber=0);//结点数组空置0下标，故nodenumber从1开始，边数起始为0
	~ALGraph();
	void inigraph();					//图目前的数据清空以备重新输入数据
	void inputdata(void);				//手工输入数据
	void autocreatgraph();				//启用默认数据
	void showgraph();					//显示邻接表
	void showtotalnodenumber();			//显示结点总个数
	void showtotaledgenumber();			//显示边的总个数
	int  findnode(int nodedata);		//查找结点在数组中的行数	
	void insertmanynodes(int data);		//一次插入一批结点使用的插入结点函数
	void insertonenode(int data);		//一次仅仅插入一个结点使用的插入结点函数
	int  deletenode(int data);			//删除结点
	void insertedge(int startpoint,int endpoint);	//插入图的边   
	int  deleteedge(int startpoint,int endpoint);	//删除图的边
	Node *findedge(int startpoint,int endpoint);	//查找两点之间的边
	void searchnext(int data);						//查找下一个邻接点
	void DFSTraverse();								//深度优先遍历入口
	void TDFSTraverse(int row,int flag[],int stackarray[]);			//深度优先遍历函数
	void BFSTraverse();								//广度优先遍历入口
	void TBFSTraverse(int row,int flag[]);			//广度优先遍历递归函数
};
ALGraph::ALGraph(int nodenumber,int edgenumber)
{
	this->Graph=new linklist[size];//定义了邻接表的指针数组
	this->nodenumber=nodenumber;
	this->edgenumber=edgenumber;
}
ALGraph::~ALGraph()
{
   delete[] Graph;
}
void ALGraph::inigraph()//图目前的数据清空以备重新输入数据
{
	for(i=1;i<nodenumber;i++)//此处实际上从坐标1只循环到达nodeposition-1的坐标，这正好是数据量
		Graph[i].clearlink();//先把边信息的链表结点全部删除和释放空间
	for(i=1;i<nodenumber;i++)//再把结点信息在数组中的链域置空
		Graph[i].setheadNULL();
	nodenumber=1;
	edgenumber=0;
}
void ALGraph::inputdata(void)
{
	inigraph();
	cout<<"请输入结点个数:";
	cin>>nodenum;
	if(nodenum<=0)
	{
		cout<<"输入数据有错，本次操作放弃!!!"<<endl;
	}
	else
	{
		cout<<"请输入结点:";
		for (i=0; i<nodenum; i++)
		cin>>node[i];
		sortednodes=doquickSort(node,nodenum);
		for (i=0; i<nodenum; i++)
			insertmanynodes(sortednodes[i]);
		cout<<"================"<<endl;
		cout<<"当前图的邻接表如下:"<<endl;
		showgraph();
		cout<<"请输入边个数:"<<endl;
		cin>>edgenum;
		if(edgenum<=0)
		{
			cout<<"输入数据有错，本次操作放弃!!!"<<endl;
		}
		else
		{
			cout<<"请输入每条边连接的两个点:"<<endl;//还要考虑点不存在
			for(i=0;i<edgenum;i++)
			{
				cin>>startpoint>>endpoint;
				if(findnode(startpoint)!=-1&&findnode(endpoint)!=-1)
					insertedge(findnode(startpoint),findnode(endpoint));
				else
					cout<<startpoint<<"与"<<endpoint<<"之间的边不存在！"<<endl;
			}
			cout<<"================"<<endl;
			cout<<"当前图的邻接表如下:"<<endl;
			showgraph();		
		}
	}
}
void ALGraph::autocreatgraph()//启用有向图默认数据
{
	int defaultnodenum=8,
		defaultnode[]={11,33,22,44,55,88,77,66},
		defaultedgenum=12,
		defaultedge[12][2]=
			{{11,22},{11,44},{11,77},
			 {22,33},{22,44},
			 {33,88},
			 {44,55},
			 {55,88},
			 {66,77},{77,66},
			 {77,44},
			 {88,66}};
	inigraph();
	for (i=0; i<defaultnodenum; i++)
		sortednodes=doquickSort(defaultnode,defaultnodenum);
	for (i=0; i<defaultnodenum; i++)
	    insertmanynodes(sortednodes[i]);
	for(i=0;i<defaultedgenum;i++)
	 	insertedge(findnode(defaultedge[i][0]),findnode(defaultedge[i][1]));
}
void ALGraph::showgraph()//显示图的邻接表形式
{
	if(nodenumber==1)
		cout<<"目前图没有数据!!!"<<endl;
	else
	{	
		cout<<"坐标"<<" 结点名"<<" 边关系链表"<<endl;
		for(int i=1;i<nodenumber;i++)//此处实际上从坐标1只循环到达nodeposition-1的坐标，这正好是数据量
		{
			cout<<" "<<i<<"   ";
			Graph[i].printlinklist();//显示了链表中的所有数据
			cout<<endl;
		} 
	}
}
void ALGraph::showtotalnodenumber()//显示总结点个数
{
	cout<<nodenumber-1<<endl;//nodeposition每次指向下一个可用空间，故实际数量需要减一
}
void ALGraph::showtotaledgenumber()//显示边的总个数
{
	cout<<edgenumber<<endl;
}
int ALGraph::findnode(int nodedata)//结点是否存在
{
	row=0;//真实数据地址从1到nodenumber-1
	while((row<nodenumber) && (Graph[row].getheaddata()!=nodedata))//当没找完而且没有找到时
		row++;
    if(row>=nodenumber)//没有找到时
		row=-1;
	return row;
}
void ALGraph::insertmanynodes(int data)//一次插入一批结点使用的插入结点函数，不考虑数据的排序
{
	if(findnode(data)==-1)
	{
	    Graph[nodenumber].inserthead(data); //进入结点依次往下存放
		nodenumber++;						//结点计数器加一
	}
   else
		cout<<data<<"结点已存在，操作失败!!!"<<endl;
}
void ALGraph::insertonenode(int data)//插入结点
{
//	int pos;
	if(findnode(data)==-1)
	{
	    Graph[nodenumber].inserthead(data);/////////此处没有保证插入在正确的位置上仅仅放在最后了
	nodenumber++;
/*
	//int tempdata=data;
	//linklist
	i=1;//从第一个坐标起，查找小于data的个数
	while (Graph[i].getheaddata()<data) //求得新结点数据应放置的正确位置
			i++;							//结束后i正好为正确插入位置
		
		
		
		for (pos=nodenumber;pos<=i;pos--)
			Graph[pos]=Graph[pos-1];
		Graph[pos-1].inserthead(data);

			nodenumber++;
		//Graph=doquickSort(Graph[], nodenumber) 
*/
	}
   else
		cout<<data<<"结点已存在，操作失败!!!"<<endl;
}

int ALGraph::deletenode(int data)//删除结点
{
		cout<<"删除结点功能暂未提供，请放弃本次操作!!!"<<endl;
/*
查找该元素是否存在
找到该元素所在的行，并记录该下标
开始删除所有相关的边信息链表结点同时计数
把总边数减去该计数器的值
从第一行开始 逐行扫描
    启用搜索指针和尾随指针 找到该下标的链表结点 一律删除 每次删除时边的计数器继续减一
循环完成后，把删除行下面所有行上移一行
总结点个数减一
*/
	return 1; 
}

void ALGraph::insertedge(int startpoint,int endpoint)
{
	Node* searchp=Graph[startpoint].find(endpoint);
	if(searchp==NULL||searchp->data!=endpoint)
	{
    	Graph[startpoint].insert(endpoint,Graph[startpoint].findsmallernum(endpoint)+1);
		//找到正确位置，插入边的信息链表结点
		edgenumber++;
	}
	else
		cout<<"该边已存在，操作失败!!!"<<endl;
}
int ALGraph::deleteedge(int startpoint,int endpoint)
{
	if(Graph[startpoint].del(endpoint)==true)
	{
		cout<<"删除边成功！"<<endl;
		edgenumber--;
	return 1;
	}
	else
	{
		cout<<"该边不存在，操作失败!!!"<<endl;
	return -1;
	}
}
Node *ALGraph::findedge(int startpoint,int endpoint) //查找startpoint与endpoint之间的边        
{           
	return Graph[startpoint].find(endpoint);        
}
void ALGraph::searchnext(int data)//查找data的相邻结点
{
	int *adjvexdataarray;
	if(Graph[findnode(data)].length==1)
	{
		cout<<data<<"没有相邻结点!!!"<<endl;
	}
	else
	{
		adjvexdataarray=Graph[findnode(data)].nodetoarraydata();
		cout<<data<<"的相邻结点为：";
		for(int i=1;i<adjvexdataarray[0];i++)
			cout<<Graph[adjvexdataarray[i]].getheaddata()<<"  ";
		cout<<endl;
		delete[] adjvexdataarray;
	}
}
void ALGraph::DFSTraverse()//深度优先遍历入口
{
	int *flag=new int [nodenumber];	//结点被访问标志，0表示未被访问，1表示已访问
	for(i=1;i<nodenumber;i++)	//标志位数组初始化，全部赋值为0
		flag[i]=0; 
	int	*stackarray=new int [nodenumber+1];//保存路径的数组，起到栈的作用
	for(i=0;i<nodenumber;i++)//初始状态全部赋值为-1
	{
		stackarray[i]=-1;
	}
	for(i=1;i<nodenumber;i++)		//每一个结点都作为起始结点一次，确保非联通图也可以完成遍历
		if(flag[i]==0)
			TDFSTraverse(i,flag,stackarray);
}
////////////////////////////////////////////////////////////////////////////////////
void ALGraph::TDFSTraverse(int row,int flag[], int stackarray[])//深度优先遍历函数
{
		int *adjvexdataarray1;	//邻接边信息链表转换成的数组
	int nextnum;			//下一个邻接点的编号
	int visitednum=1;		//已访问结点的个数
    //if(row==-1) return;
	stackarray[0]=1;		//0号坐标中存放访问过的结点数量，此处预设为1，则最后访问结点数量需要减一
	while(row!=-1 && stackarray[0]<nodenumber)//如果进入点存在并且已访问的结点数量没有到达总结点量则循环
	{
		if(flag[row]==0)							//如果没访问，就访问
		{
			cout<<Graph[row].getheaddata()<<"  ";	//把该编号对应的结点名输出
			stackarray[stackarray[0]]=row;          //保存路径信息
	        stackarray[0]++;                        //stackarray[0]-1为存放已访问结点个数
			flag[row]=1;
		}
		adjvexdataarray1=Graph[row].nodetoarraydata();//把链表中所有邻接结点信息转换成数组，地址从1开始
		///////////////
		//cout<<"这里是每次每一行结点信息转换为数组后的信息"<<endl;
		//for(i=1;i<nodenumber;i++)
		//	cout<<adjvexdataarray1[i]<<endl;
		//cout<<"每一行结点信息转换为数组后的信息结束"<<endl;
		///////////////
		nextnum=1;									 //开始处理第一个相邻结点	                       
	    row=Graph[row].getnextnode(nextnum);		 //获取相邻结点对应在结点数组中的行号
		while(flag[row]==1 && row!=-1 && stackarray[0]<nodenumber)//如果该结点被访问过则查找下一个邻接点
			row=adjvexdataarray1[nextnum++];			 //直到找到一个没有被访问过的结点编号 
		
		
		//TDFSTraverse(row,flag,stackarray);//从新的一行进入，递归完成遍历工作
		visitednum=stackarray[0]-1;                  //记录已访问数据个数
		if(stackarray[0]<nodenumber && row==-1)      //结点没访问完，同时相邻结点都访问完毕
		{   visitednum--;							 //开始回溯过程	
			row=stackarray[visitednum];				 //从保存的路径中回退到上一个已访问结点
		}
   }
}
/*
void ALGraph::TDFSTraverse(int row,int flag[])//深度优先遍历函数
{
	int *adjvexdataarray;	//邻接边信息链表转换成的数组
	int nextnum;			//下一个邻接点的编号
	int visitednum=1;		//已访问结点的个数
	int	*stackarray=new int [nodenumber+1];//保存路径的数组，起到栈的作用
	for(int i=0;i<nodenumber;i++)//初始状态全部赋值为-1
	{
		stackarray[i]=-1;
	}
	stackarray[0]=1;			//0号坐标中存放访问过的结点数量，此处预设为1，则最后访问结点数量需要减一
	while(row!=-1 && stackarray[0]<nodenumber)//如果进入点存在并且已访问的结点数量没有到达总结点量则循环
	{
	    if(flag[row]==0)							//如果没访问，就访问
		{
			cout<<Graph[row].getheaddata()<<"  ";	//把该编号对应的结点名输出
			stackarray[stackarray[0]]=row;          //保存路径信息
	        stackarray[0]++;                        //stackarray[0]-1为存放已访问结点个数
			flag[row]=1;
		}
		adjvexdataarray=Graph[row].nodetoarraydata();//把链表中所有邻接结点信息转换成数组，地址从1开始
		nextnum=1;									 //开始处理第一个相邻结点	                       
	    row=Graph[row].getnextnode(nextnum);		 //获取相邻结点对应在结点数组中的行号
		while(flag[row]==1 && row!=-1 && stackarray[0]<nodenumber)//如果该结点被访问过则查找下一个邻接点
			row=adjvexdataarray[nextnum++];			 //直到找到一个没有被访问过的结点编号 
		visitednum=stackarray[0]-1;                  //记录已访问数据个数
		if(stackarray[0]<nodenumber && row==-1)      //结点没访问完，同时相邻结点都访问完毕
		{   visitednum--;							 //开始回溯过程	
			row=stackarray[visitednum];				 //从保存的路径中回退到上一个已访问结点
		}
   }
}
*/

//////////////////////////////////////////////////////////////////////////////////
void ALGraph::BFSTraverse()//广度优先遍历入口
{
	int *flag=new int [nodenumber];	//结点被访问标志，0表示未被访问，1表示已访问
	for(int i=1;i<nodenumber;i++)	//标志位数组初始化，全部赋值为0
		flag[i]=0; 
	for(i=1;i<nodenumber;i++)		//每一个结点都作为起始结点一次，确保非联通图也可以完成遍历
		if(flag[i]==0)
			TBFSTraverse(i,flag);
}
void ALGraph::TBFSTraverse(int row,int flag[])//广度优先遍历递归函数
{
	int *adjvexdataarray;
    if(flag[row]==0)  //从row行进入，代表着第row个数据目前是新的起点，标志位为0表示数据没有被访问
	{
		cout<<Graph[row].getheaddata()<<"  ";	//取出并显示第一个结点中的结点名
	    flag[row]=1;							//翻转标志位
	}
	adjvexdataarray=Graph[row].nodetoarraydata();//把row行结点的所有相关结点信息存入一个临时数组
   	for(int i=1;i<adjvexdataarray[0];i++)    //0号地址中为相关边的条数，逐一结点访问并且进队
	{
		if(flag[adjvexdataarray[i]]==0)     //数据没有被访问，输出显示
		{
			cout<<Graph[adjvexdataarray[i]].getheaddata()<<"  ";
			flag[adjvexdataarray[i]]=1;
			queue.enqueue(adjvexdataarray[i]);
		}
    }
	if( (row=queue.dequeue())!=-1)//队列不为空，出队产生出下一个进入的行坐标
	{
		TBFSTraverse(row,flag);//从新的一行进入，递归完成遍历工作
	}
}
////////////////////////////////////////////
//界面处理对象：界面库
class interfacebase
{
private:
	ALGraph graphnow;	//图对象的实例化
public:
	void showmenu(void);
    void processmenu(void);
};
void interfacebase::showmenu(void)
{
    cout<<"=================================="<<endl;
    cout<<"      图的邻接表功能演示          "<<endl;
    cout<<"=================================="<<endl;
    cout<<"1.手工建立一个图					 "<<endl;
	cout<<"2.启用默认数据建立图				 "<<endl;
    cout<<"3.显示图邻接表，显示结点数和边数	 "<<endl;
    cout<<"4.查找某结点的相邻结点			 "<<endl;
    cout<<"5.添加一个结点                    "<<endl;
    cout<<"6.删除一个结点			         "<<endl;
    cout<<"7.添加一条边						 "<<endl;
	cout<<"8.删除一条边						 "<<endl;
    cout<<"a.深度优先遍历图					 "<<endl;
    cout<<"s.广度优先遍历图					 "<<endl;
    cout<<"0.退出							 "<<endl;
    cout<<"=================================="<<endl;
}
void interfacebase::processmenu()
{
	char choice,yesno;			//用于用户选择菜单选项
	int  nodestart,nodeend;		//插入边或删除边的起点和终点
	int  removenode;			//用于删除结点
	int  mark;					//返回一个标志位，用于删除边使用
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
		build=1;
		cout<<"================"<<endl;
        break;
	case '2':
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
		graphnow.autocreatgraph();
		build=1;
		cout<<"================"<<endl;
		cout<<"当前图的邻接表如下:"<<endl;
        graphnow.showgraph();
		cout<<"================"<<endl;
					//cout<<endl<<"深度优先遍历序列为 :"<<endl;//调试使用
					//graphnow.DFSTraverse();
					//cout<<endl<<"广度优先遍历序列为 :"<<endl;
					//graphnow.BFSTraverse();
					//cout<<endl;
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
		cout<<"当前图的邻接表如下:"<<endl;
        graphnow.showgraph();
		cout<<"当前结点个数为 :";
	    graphnow.showtotalnodenumber();
		cout<<"当前图的边数为 :";
	    graphnow.showtotaledgenumber();
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
		cout<<"当前图的邻接表如下:"<<endl;
        graphnow.showgraph();
		int node;
		cout<<"请输入结点名: ";
			cin>>node;
			if(graphnow.findnode(node)==-1)      //查找
				cout<<"此结点不存在"<<endl;
			else
			{
				graphnow.searchnext(node);
			}
		cout<<"================"<<endl;
		break;
	case '5':
        if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"图未建立，本次操作失败!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
		cout<<"================"<<endl;
		cout<<"当前图的邻接表如下:"<<endl;
        graphnow.showgraph();
		cout<<"请输入要插入的结点 : ";
		cin>>node;
		if(graphnow.findnode(node)==-1)  
		{
			graphnow.insertonenode(node);
			cout<<"插入结点成功！"<<endl;
			cout<<"当前图的邻接表如下:"<<endl;
			graphnow.showgraph();
		}
		else 
			cout<<"该结点已存在!插入失败!!!"<<endl;
        cout<<"================"<<endl;
		break;
    case '6':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"图未建立，本次操作失败!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
        cout<<"================"<<endl;
		cout<<"当前图的邻接表如下:"<<endl;
        graphnow.showgraph();
		cout<<"请输入要删除的结点名: ";
		cin>>removenode;
		cout<<"危险操作!你确定吗?确定按(Y||y)键!否则按任意键!"<<endl;
		cin>>yesno;
		if(yesno=='y'||yesno=='Y')
		{			 
			mark=graphnow.deletenode(removenode);
			if(mark==1)
			{
				cout<<"结点"<<removenode<<"已经被删除!"<<endl;
				cout<<"当前图的邻接表如下:"<<endl;
				graphnow.showgraph();
			}
		}
		else
			cout<<"本次操作已经放弃!!!";
		cout<<"================"<<endl;
        break;
    case '7':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"图未建立，本次操作失败!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
        cout<<"================"<<endl;
		cout<<"当前图的邻接表如下:"<<endl;
        graphnow.showgraph();
		cout<<"请输入要插入边的起点和终点: "<<endl;
			cin>>nodestart>>nodeend;
			if(graphnow.findnode(nodestart)==-1 || graphnow.findnode(nodeend)==-1)
				cout<<"结点名有错!插入边失败!!!"<<endl;
			else
			{
				graphnow.insertedge(graphnow.findnode(nodestart),graphnow.findnode(nodeend));
				cout<<"当前图的邻接表如下:"<<endl;
				graphnow.showgraph();
			}
		cout<<"================"<<endl;	
		break;
	case '8':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"图未建立，本次操作失败!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
        cout<<"================"<<endl;
		cout<<"当前图的邻接表如下:"<<endl;
        graphnow.showgraph();
		cout<<"请输入要删除边连接的两个结点: "<<endl;
		cin>>nodestart>>nodeend;
		if(graphnow.findnode(nodestart)==-1||graphnow.findnode(nodeend)==-1)
			cout<<"结点名有错!删除边失败!!!"<<endl;
		else
		{
			cout<<"危险操作!你确定吗?确定按(Y||y)键!否则按任意键!"<<endl;
			cin>>yesno;
			if(yesno=='y'||yesno=='Y')
			{
				mark=graphnow.deleteedge(graphnow.findnode(nodestart),graphnow.findnode(nodeend));
				if (mark==1)
					cout<<"从结点"<<nodestart<<"到"<<"结点"<<nodeend<<"的边已被删除!"<<endl;
				cout<<"当前图的邻接表如下:"<<endl;
				graphnow.showgraph();
			}
			else
			cout<<"本次操作已经放弃!!!";
		}
		cout<<"================"<<endl;
		break;
	case '9':
		//graphnow.inigraph();
		break;
	case 'a':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"图未建立，本次操作失败!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
		cout<<"================"<<endl;
		cout<<"当前图的邻接表如下:"<<endl;
        graphnow.showgraph();
        cout<<"================"<<endl;
		cout<<"约定从第一个结点开始遍历。"<<endl;//对无向图有效。
		cout<<"深度优先遍历序列为 :"<<endl;	
					graphnow.DFSTraverse();
		cout<<endl;
		cout<<"================"<<endl;
        break;
    case 's':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"图未建立，本次操作失败!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
		cout<<"================"<<endl;
		cout<<"当前图的邻接表如下:"<<endl;
        graphnow.showgraph();
        cout<<"================"<<endl;
		cout<<"约定从第一个结点开始遍历。"<<endl;//对非联通图有效。对无向图有效。
		cout<<"广度优先遍历序列为 :"<<endl;
					graphnow.BFSTraverse();
		cout<<endl;
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
