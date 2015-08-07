//功能：基数排序功能演示程序
#include<iomanip.h>
#include<iostream.h>   
#include<windows.h>   
#include<math.h> 
#define Maxnum 100000	  //设置随机数据最大值
#define Defaultnumber 10  //设置默认数组的大小
#define Datawidth 7		  //设置显示数据宽度
#define QueueNum 10		  //设置10个队，分别保存0 ~ 9的关键码 
#define Maxsize 1000  	  //数据量最大限
/////
int flag=0;				  //标志位，判断用户是否输入数据，没有输入为0，有则改为1
int defaultdata[Defaultnumber]={126,342,75,673,198,95,913,436,223,531};//默认数据
class queuenode;		  //队结点类
class linkqueue;		  //队操作类
class radixsort;		  //基数排序类
class interfacebase;	  //菜单类
/////
class queuenode			  //队结点类
{	
	friend class linkqueue;
private: 
    int data;			  //队列结点数据
    queuenode *link;      //结点链指针
public:
    queuenode ( int d=0, queuenode *l = NULL ) : data (d), link (l) { }
};
class linkqueue			  //队操作类
{	
private: 
    queuenode *front, *rear;                             //队头、队尾指针指针
public: 
    linkqueue ( ) : rear(NULL), front(NULL){ }
    ~linkqueue ( );						                 //队列的析构函数
    void enqueue (const int &item );                    //将新元素item插入到队列的队尾
    void dequeue ( );					                 //删除并返回队头元素
    int  getfront ( );					                 //查看队列头元素值
	int  isempty ( ) const{ return front == NULL; }	     //判断队列是否为空
};
/*队列的析构函数*/         
linkqueue:: ~linkqueue ( ) 
{
    queuenode *tempp;
    while ( front!=NULL )						//逐步释放非空结点
	{   
        tempp=front;  
		front=front->link;  
		delete tempp;								
    }
}
/*将新元素item插入到队列的队尾*/
void linkqueue:: enqueue ( const int& item ) 
{
    if (front == NULL)//创建第一个结点
		front=rear=new queuenode(item, NULL);
	//队列不空, 插入
    else        
         rear=rear->link=new queuenode(item, NULL);
}
/*删除并返回队头元素*/
void linkqueue:: dequeue ( ) 
{
	queuenode *tempp = front;		   
	front = front->link;   	
	delete tempp;    			
}
/*查看队列头元素值*/
int linkqueue:: getfront ( )
{
	return front->data;
}
///////////// 
class radixsort//基数排序类
{
public:
	radixsort(){}
	~radixsort(){}
	int  searchmax();					//找到数据中的最大值
	void send(int *datasent,int total); //传递函数
	void displayresult();				//显示
	void doradixsort();				    //排序

private:
	linkqueue queue[QueueNum];          //多个队列，都是链表队列 
	int inputdata[Maxsize];			    //接收数据数组
	int count;							//数据总数
	int index;							//进位标志
	int max;							//数据最大位数
};
int radixsort::searchmax()
{	
		int maxvalue=inputdata[0];	    //maxvalue用来保存数据最大值，初始值为第一个数据
		for(int i=1;i<count;i++)        //扫描法确定最大值
			if(maxvalue<inputdata[i])
				maxvalue=inputdata[i];
		return maxvalue;
	
}
void radixsort::send(int *datasent,int total)//传递函数
{
	count=total;
	for(int i=0;i<count;i++)
		inputdata[i]=datasent[i];
	max=searchmax();//求出数据中的最大值
	for(i=1;;i++)//求出数据的最大位数
	{
		if(max/((int)pow(10,i))==0)
		{
			max=i;
			break;
		}
	}
	index=1;//从个位开始进队
}
void radixsort::displayresult()
{
	if(!inputdata)
		cout<<"数据还没有创建。"<<endl;
	else
	{
    	doradixsort();
    	cout<<endl<<"排序后数据是:"<<endl;
    	for(int i=0;i<count;i++)
		{
	    	cout<<setw(Datawidth)<<inputdata[i];
    		if((i+1)%10==0)
	    		cout<<endl;
		} 
		cout<<endl;
		cout<<"===================="<<endl;
		cout<<"基数排序成功！！！  "<<endl;
		cout<<"===================="<<endl;
	}
}
void radixsort::doradixsort()
{
	for(int i=0;i<max;i++)							//根据位数值控制循环次数
	{
		for(int j=0;j<count;j++)					//对所有数据进队
		{						
			int k=inputdata[j]%(10*index)/index;	//队号
			queue[k].enqueue(inputdata[j]);		    //按位数从小到大，分别进队
		}
		int outqueueindex=0;						//出队数据下标
		for(j=0;j<QueueNum;j++)						//按队号出队
		{
			while(!queue[j].isempty())				//判断队列为非空
			{
				inputdata[outqueueindex++]=queue[j].getfront(); //取头结点
				queue[j].dequeue();					//出队
			}
		}
		index*=10;									//向高进位
		/*显示进出队一次后的数据*/
    	cout<<endl<<"第"<<i+1<<"次出队后效果为："<<endl;
    	for(int k=0;k<count;k++)
		{
	    	cout<<setw(Datawidth)<<inputdata[k];
    		if((k+1)%10==0)
	    		cout<<endl;
		} 
	}
}
///////
class interfacebase//菜单类
{
private:
	radixsort radix;							//创建基数排序的数组
	int datasent[Maxsize];						//存储数据
	int total;									//数据总数
public:
	void clearscreen(void);						//清屏
	void showmenu(void);						//菜单
	int  userchoice(void);						//菜单选择参数
	void processmenu(int menuchoice);			//菜单选项
	void display();								//显示数据
};
void interfacebase::clearscreen(void)			//清屏
{
    system("cls");
}
void interfacebase::showmenu(void)				//菜单
{
  	cout<<"基数排序功能演示程序"<<endl;
    cout<<"===================="<<endl;
	cout<<"1.手工输入数据"<<endl;
    cout<<"2.自动产生数据"<<endl;
    cout<<"3.开始基数排序"<<endl;
    cout<<"4.退出程序"<<endl;
	cout<<"===================="<<endl;
}
int interfacebase::userchoice(void)				//菜单选择参数
{	int menuchoice;
	cout<<"请输入您的选择：";   
	cin>>menuchoice;
	cout<<"===================="<<endl;
	return menuchoice;
}
void interfacebase::processmenu(int menuchoice)//菜单选项
{
	int j;										//循环变量
	switch(menuchoice)							//根据用户的选择进行相应的操作
	{
	case 1:
			    cout<<"请输入您需要键盘输入待排数据的个数：";
				cin>>total;
				while(total<1||total>Maxsize)	//防止数据量有误
				{
					cout<<"请输入您需要键盘输入待排数据的个数：";
					cin>>total;
				}
				cout<<"请开始输入数据(提示：一共 "<<total<<"个数据，用空格分开)："<<endl;
				for(j=0;j<total;j++)
					cin>>datasent[j];
				radix.send(datasent,total);		//将数据传入到基数排序中
				flag=1;
				break;
				
	case 2:
				cout<<"请输入您需要系统产生待排数据的个数：";
				cin>>total;
				while(total<1||total>Maxsize)	//防止数据量有误
				{
					cout<<"请输入您需要键盘输入待排数据的个数：";
					cin>>total;
				}
				cout<<"系统自动产生"<<total<<"个数据!"<<endl;
				for(j=0;j<total;j++)
					datasent[j]=rand()%Maxnum;  //系统给出一个0-Maxnum之间的随机数
				radix.send(datasent,total);		//将数据传入到基数排序中
				flag=1;
				break;
	case 3:
				if(flag==0)
					radix.send(defaultdata,Defaultnumber);	//将默认数据传入到基数排序中
				radix.displayresult();
				break;
	case 4:
				exit(0);
	default:
				cout<<"对不起，您输入的功能编号有错!请重新输入!!!"<<endl;
		    	break;
	}
}
void interfacebase::display()
{
	if(flag==0)
	{
		cout<<"若不输入数据，默认数据为："<<endl;
		for(int j=0;j<Defaultnumber;j++)
			cout<<setw(Datawidth)<<defaultdata[j];
		cout<<endl;
	}
	if(flag==1)
	{
		cout<<"用户输入的数据为："<<endl;
		for(int j=0;j<total;j++)
		{	
			cout<<setw(Datawidth)<<datasent[j];
			if((j+1)%10==0)
	    		cout<<endl;
		}
		cout<<endl;
	}
}
/////
void main(void)                     //程序主入口
{   
	system("color f0");
	int menuchoice;                 //下面要用到
	interfacebase interfacenow;
	interfacenow.clearscreen();
    while (1)
	{
  		interfacenow.showmenu();
		interfacenow.display();
		menuchoice=interfacenow.userchoice();
		interfacenow.processmenu(menuchoice);
		system("pause"); 
		interfacenow.clearscreen();
    }
}//主函数结束