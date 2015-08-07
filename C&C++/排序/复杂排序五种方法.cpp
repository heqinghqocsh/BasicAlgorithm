//功能:复杂排序方法的功能演示
#include<iomanip.h>
#include<iostream.h>
#include<windows.h>
#define MAXNUM  100					    //数据个数最大值
#define MAXSIZE 1000					//数据本身最大值
int flag=0;						    	//用来标识待排数据是否产生
class node    
{
	friend class list;				    //友元函数
public:
	node(){};
	~node(){};
};
class list   
{
public:
	list(){};
	~list(){};
	void create();				    	//创建对象数据函数
	void copy(list initlist);	    	//复制对象数据函数
	void display();				    	//显示数据函数
	int  binaryfind(int *data, int from, int to, int find);//折半查找
	void halfinsert();                  //折半插入排序函数
	int  totalnumbers(list initlist);   //希尔排序时通过数据总数确定步长取值范围
	void shell(int step);               //希尔排序函数
	void quick();                       //快速排序函数主要入口
	int  quicksort(int * Data,int n);   //快速排序函数递归实现
	void heap();                        //堆排序函数主要入口
	void list::heapadjust(int begin,int end);//堆排序函数重组堆
	void merge();						//归并排序函数主要入口
	int  mergesort(int Data[],int n);   //归并排序函数具体实现
private:
	int heapdata[MAXNUM];			//静态数组作为大根堆线性表的存储结构
	int data[MAXNUM];				//静态数组作为线性表的存储结构
	int total;						//数据量
};

int list::totalnumbers(list initlist)//返回数据总数
{
	return initlist.total;
}
void list::create()					//创建对象数据函数
{
	int choice,i;
	char ch;
	if(flag==1)					   //代表此时已经有一组建立好的数据
	{
		cout<<"此时系统已经有一组建立好的数据，您确认想替换吗？(Y||y)：";
		cin>>ch;
		if(ch=='Y'||ch=='y')
			flag=0;
	}
	if(flag==0)
	{
		cout<<"创建待排数据： <1>键盘输入    <2>自动生成  "<<endl<<"请选择：";
		cin>>choice;
		switch(choice)
		{
		case 1:
			cout<<"请输入您需要键盘输入待排数据的个数：";
			cin>>total;
			cout<<"请开始输入数据(提示：一共 "<<total<<"个数据，用空格分开)："<<endl;
			for(i=0;i<total;i++)
				cin>>data[i];
			flag=1;
			break;
		case 2:
			cout<<"请输入您需要系统产生待排数据的个数：";
			cin>>total;
			cout<<"系统自动产生"<<total<<"个数据!"<<endl;
			for(i=0;i<total;i++)	
				data[i]=rand()%MAXSIZE;  //系统给出一个0-MAXSIZE之间的随机数
			flag=1;
			break;
		default:
			cout<<"您输入有误!请重新输入："<<endl;
			break;
		}
		if(flag==1)
		{
			cout<<"待排数据如下..."<<endl;
			display();
			cout<<"待排数据成功建立!"<<endl;
		}
	}
	else
	{
		cout<<"你已经成功取消了上述操作!"<<endl;
	}
} 
void list::copy(list initlist)//复制对象数据函数
{
	int i;
	for(i=0;i<initlist.total;i++)
		data[i]=initlist.data[i];
	total=initlist.total;
}
void list::display()//显示函数
{
	int i;
	for(i=0;i<total;i++)
		cout<<setw(5)<<setiosflags(ios::left)<<data[i];
	cout<<endl;
}
int list::binaryfind(int *data, int from, int to, int find)//折半查找
{
	if(from > to)
		return from; //待找数据合适的位置
	if(find == data[(from+to)/2])
		return (from+to)/2;//待找数据合适的位置
	else if(find < data[(from+to)/2])//所查找数据小于中间数据时，通过递归继续查找正确的位置
		return binaryfind(data,from,(from+to)/2-1,find);
	return binaryfind(data,(from+to)/2+1,to,find);//返回值  待找数据合适的位置
}
///排序函数/////////////
void list::halfinsert()//折半插入排序函数
{
	if(total == 0)
	{
		cout<<"暂时没有数据!操作失败!"<<endl;
		return ;
	}
	cout<<"待排数据是:"<<endl;
	display();
	for(int i =1; i<total; i++)
	{
		int position = binaryfind(data,0,i-1,data[i]);//待找数据合适的位置
		int temp =data[i];
		for(int j = i-1; j>=position;j--)
			data[j+1] = data[j];//从后一位向前一位逐次移动数据
		if(j != i-1)
			data[position] = temp;//将待找数据放入合适的位置
		cout<<"第 "<<i+1<<" 个数据 "<<temp<<"找到位置是"<<position+1<<",结果是:"<<endl;
		display();
	}
	cout<<"排序任务完成!"<<endl;
}
void list::shell(int step)//希尔排序函数
{
	int temp;
	int w;

	while(step>0)//步长最小为1
	{
		for(int j=step;j<total;j++)
		{
			temp=data[j];
			w=j-step;
			while((temp<data[w])&&(w>=0)&&(w<=total))
			{
				data[w+step]=data[w];
				w=w-step;//缩小步长的范围比较数据
			}
			data[w+step]=temp;
		}
		/*显示希尔排序*/
		cout<<endl<<"当步长为"<<step<<"时，此时的排序结果:"<<endl;
		display();
		cout<<endl;
		step=step/2;//调整步长
	}
}
void list::quick()//快速排序函数
{
	cout<<endl<<"快速排序的主要过程显示："<<endl;
	quicksort(data,total);
	cout<<"快速排序的结果："<<endl;
	display();
}
int list::quicksort(int * Data,int n)
{
	int from=0;
	int to=n-1;
	int middle;
	int position=0;
	int space;
	if(n<=1)
		return 0;
    while(from<to)
	{
		if(from==position)
		{
			if(Data[position]<Data[to])
			{
			    to--;
			}
		    else if(Data[position]>Data[to])
			{
				//交换数据
				space=Data[position];
				Data[position]=Data[to];
				Data[to]=space;
				//显示交换后的数据
				cout<<endl;
				display();
				//记录下位置，然后继续向后搜索
			    position=to;
			    from++;
			}
		    else if(Data[position]==Data[to])
			{
			    to--;
			}
		}
		else if(position==to)
		{
			if(Data[from]>Data[position])
			{
				//交换数据
				space=Data[position];
				Data[position]=Data[from];
				Data[from]=space;
				//显示交换后的数据
				cout<<endl;
				display();
				//记录下位置，然后继续向前搜索
			    position=from;
			    to--;
			}
		    else if(Data[from]<Data[position])
			{
			    from++;
			}
		    else if(Data[from]==Data[position])
			{
			    from++;
			}
		}
	}
	middle=position;
	quicksort(Data,middle);
	quicksort(Data+middle+1,n-middle-1);
	return 0;
}
void list::heap()//堆排序函数
{
	for(int k=0;k<total;k++)
		heapdata[k+1]=data[k];
	int i,temp;
	cout<<endl<<"开始对应的二叉树:"<<endl;
	for(i=1;i<=total;i++)
		cout<<setw(6)<<heapdata[i];
	cout<<endl<<"每次排列后的结果是:"<<endl;
	for(i=total/2;i>0;--i) //把heapdata[1..i]建成大根堆，从后面开始
		heapadjust(i,total);
	for(i=total;i>1;--i)
	{
		temp=heapdata[1]; //将堆顶记录和当前未经排序子序列heapdata[1..i] 
		heapdata[1]=heapdata[i]; //中的最后一个记录相互交换
		heapdata[i]=temp;
		heapadjust(1,i-1); //将heapdata[1..i-1]重新调整为大根堆
	}
}
void list::heapadjust(int begin,int end)
{
	//已知heapdata[begin..end]中除heapdata[begin]之外均满足堆的定义,本函数调整heapdata[begin]
    //使heapdata[begin..end]成为一个大根堆
	int i,value;
	value=heapdata[begin];
	for(i=2*begin;i<=end;i*=2) //沿关键字叫大的结点向下筛选
	{
		if(i<end&&heapdata[i]<heapdata[i+1])
			++i; //i为关键字较大的记录的下标
		if(value>=heapdata[i]) 
			break; //value应插入在位置begin上
		heapdata[begin]=heapdata[i];
		begin=i;
	}
	heapdata[begin]=value; //插入
	for(i=1;i<=total;i++)
		cout<<setw(6)<<heapdata[i];
	cout<<endl;
}
void list::merge()//归并排序函数
{
	cout<<endl<<"归并排序的过程显示："<<endl;
	mergesort(data,total);
	cout<<"归并排序的结果："<<endl;
	for(int i=0;i<total;i++)
		cout<<data[i]<<' ';
}
int list::mergesort(int Data[],int n)
{
	int swap;
	int * divide;
	//传递终止条件
	if(n==1)
		return 0;
	//对数据进行分割
	divide=Data+n-n/2;
	mergesort(Data,n-n/2);
	mergesort(divide,n/2);
    //合并数据并排序
	for(int i=0;i<n/2;i++)
	{
		for(int j=n-n/2-1+i;j>=0;j--)
			if(Data[j]<divide[i])
				break;
		swap=divide[i];
		for(int k=n-n/2-1+i;k>j;k--)
		{
			Data[k+1]=Data[k];
		}
		Data[k+1]=swap;
		//输出结果
		for(i=0;i<total;i++)
			cout<<data[i]<<' ';
		cout<<endl;
	}
	return 0;
}
//排序函数结束//////
void showmenu(void)//菜单界面函数
{
	cout<<"============================================="<<endl;
	cout<<"  　      高级排序算法功能展示系统           "<<endl;
	cout<<"    ------------------------------------     "<<endl;
	cout<<"             1: 输入待排数据（建议100个以内）"<<endl;
    cout<<"             2: 显示待排数据                 "<<endl;
	cout<<"             3: 折半插入排序                 "<<endl;
    cout<<"             4: 希尔排序		            	"<<endl;
	cout<<"             5: 快速排序                     "<<endl;
	cout<<"             6: 堆排序       			    "<<endl;
	cout<<"             7: 归并排序			            "<<endl;
 	cout<<"             0: 退出本系统                   "<<endl;
	cout<<"============================================ "<<endl;
	cout<<"请选择： ";
}

void processmenu(void)//菜单选项函数
{
	int choice;
	list fromlist,mylist;      //源对象fromlist;处理对象mylist;
	while(1)
	{
		system("cls");
		showmenu();
		cin>>choice;
		switch(choice)
		{
			case 1:
				fromlist.create();//创造源对象数据
				break;
			case 2:
				if(flag==1)
				{
					mylist.copy(fromlist);//复制对象
					cout<<"待排数据为:"<<endl;
					mylist.display();
				}
				break;
			case 3:
				if(flag==1)
				{
					cout<<"简介："<<endl;
					cout<<"    折半插入排序，是插入排序的改进，它的思路"<<endl;
					cout<<"是把找到正确位置的过程从逐一比较改为二分查找比较，"<<endl;
					cout<<"这样在查找正确位置时就可以大大提升时间效率。"<<endl;
					cout<<"这个思路后面的数据移动就必须改为整体移动的过程。"<<endl;
					mylist.copy(fromlist);
					mylist.halfinsert();
					cout<<endl<<"排序成功!"<<endl<<endl;
				}
				break;
			case 4:
				if(flag==1)
				{
					cout<<"简介："<<endl;
					cout<<"    希尔排序，又称为“缩小增量排序”，它的思路"<<endl;
					cout<<"比较简单，先确定一个步长，然后对于所有在某段里"<<endl;
					cout<<"的所有数据进行插入排序，之后把步长缩小，通常可"<<endl;
					cout<<"以除以2，然后重复这个思路，直到最后的步长为1。"<<endl;
					int step;
					mylist.copy(fromlist);
					cout<<endl<<"请输入步长：";
					cin>>step;
					while(step<1||step>mylist.totalnumbers(mylist))
					{
						cout<<endl<<"输入步长不合适，"<<"请输入步长:";
						cin>>step;
					}
					mylist.shell(step);
					cout<<endl<<"排序成功!"<<endl<<endl;
				}
				break;
			case 5:
				if(flag==1)
				{
					cout<<"简介："<<endl;
					cout<<"    快速排序，思路是第一次把第一个数据换到它正"<<endl;
					cout<<"确的位置上，所谓正确的位置是指它左边的数据都比"<<endl;
					cout<<"它小，它右边的数据都比它大，这样从最后的结果分"<<endl;
					cout<<"析，它的位置就是正确的。然后用递归的思想对于左"<<endl;
					cout<<"右两边的数据继续排序，直到整个数据区变成有序。"<<endl;
					mylist.copy(fromlist);
					mylist.quick();
					cout<<endl<<"排序成功!"<<endl<<endl;
				}
				break;
			case 6:
				if(flag==1)
				{
					cout<<"简介："<<endl;
					cout<<"    堆排序，设有n个元素，首先将这n个元素按关"<<endl;
					cout<<"键码建成堆，将堆顶元素输出，得到n个元素中关键 "<<endl;
					cout<<"码最大（小）值元素。对剩下的n-1个元素重新组堆，"<<endl;
					cout<<"输出堆顶元素，得到次大（小）值元素。反复进行。"<<endl;
					mylist.copy(fromlist);
					mylist.heap();
					cout<<endl<<"排序成功!"<<endl<<endl;
				}
				break;
			case 7:
				if(flag==1)
				{
					cout<<"简介："<<endl;
					cout<<"    归并排序，它的基本操作是将两个有序表合并为"<<endl;
					cout<<"一个有序表。它的思路的突破点是同时启动多个已排"<<endl;
					cout<<"空间，之后逐渐合并这些已排空间，直到全部数据成"<<endl;
					cout<<"为一个已排空间。                              "<<endl;
					mylist.copy(fromlist);
					mylist.merge();
					cout<<endl<<"排序成功!"<<endl<<endl;
				}
				break;
			case 0:
				cout<<endl<<"您已经成功退出本系统，欢迎再次使用!!!"<<endl;
				exit(1);
				break;
			default:
				{
					cout<<"对不起，您输入有误! 请再次输入<0~7>:"<<endl;
					system("pause"); 
				}
		}
	if(flag==0)
		cout<<"对不起，还没有建立待排数据!"<<endl;
	system("pause"); 	
	}	
}

//=======主函数=========	
void main(void)
{
	system("color f0"); //第一个为背景白色(f)，第二个为字体颜色黑色(0)
	processmenu();		//菜单选项函数
}
