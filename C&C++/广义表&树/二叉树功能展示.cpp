/*功能描述：
      1. 建立二叉树三种方法(广义表形式内置、键盘输入广义表和逐个数据构建)。
	  2. 输出二叉树两种方法(广义表形式和缩格形式)。
	  3. 二叉树多种遍历(递归三种、非递归三种、层次遍历共七种，使用线性表逻辑结构输出。
	  4. 二叉树内全部数据信息显示。
	  2. 增加、删除和查找数据结点。
	  3. 提供当前工作指针的转移(移至左儿子、移至右儿子、移至父亲和移至树根、移至被查找对象)
*/

#include<windows.h>
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
enum returninfo {success,fail,overflow,underflow,nolchild,norchild,nofather,havesonl,havesonr,
                 haveason,havetwosons,range_error,quit
                };					//定义返回信息清单
#define Maxsize 100									//定义广义表数组的长度
char defaultbtree1[]="a(b,c(,d))";					//默认广义表数据表示的二叉树范例1
char defaultbtree2[]="a(b(c(d,e),f(,g)),h(i,j))";	//默认广义表数据表示的二叉树范例2
class node
{
    friend class btree;//二叉树类的友元类
public:
    node(char initdata='0',int initdeep=0,node *initl=NULL,node *initr=NULL,
		node *initf=NULL,node *initn=NULL);
    ~node() {};
protected:
    char data;		//二叉树结点中的数据，此处定义为字符
    int	 deep;		//设置二叉树结点的深度
    node *lchild;	//左儿子
    node *rchild;	//右儿子
    node *father;	//父亲结点
    node *next;		//用单链表处理所有结点时指向下一个结点
};
node::node(char initdata,int initdeep,node *initl,node *initr,node *initf,node *initn)
{
    data=initdata;
    deep=initdeep;
    lchild=initl;
    rchild=initr;
    father=initf;
    next=initn;
}
class stackdata //创建一个stackdata类，在非递归遍历算法中需要
{
    friend class btree;
private:
    node *link;
    int  flag;
public:
    stackdata()  {};
    ~stackdata() {};
};
class btree  //创建一个二叉树类
{
private:
    char btreedata[Maxsize];		//广义表字符数组
    char answer;					//用于回答菜单选项
    node *root;						//指向根结点位置的指针
    node *workinp,*linkrear;		//定义一个工作指针，尾部指针
    int  btreecount;				//结点个数计数器
    bool firstbracket;				//显示广义表时处理第一个括号，为1是，变成0就不是了
	int  countnow;					//每一次需要使用计数器时临时保存该值
    int  leafcount;
    int  countall;
    int	 sondeep;					//创建儿子结点时保存当前深度
public:
    btree(node *initrootp);
    btree()
    {
        root=NULL;
		firstbracket=1;
		countall=0;					//递归函数内部统计结点个数
		btreecount=0;               //二叉树统计后的结点个数
    };
    ~btree() {};
    void initfirstbracket();		//把第一个括号标志位恢复成1
    returninfo createbtree(int choice); //根据广义表字符串生成二叉树，choice=1为默认数据，2为键盘输入
    returninfo createroot();		//建立树根函数
    void visit(node *searchp);      //访问当前结点数据域
    void showbtreedata();			//在主界面中显示当前工作数组
    int  rgetcount(node *searchp);  //递归统计二叉树中的结点个数
    int  getcount();				//记录二叉树中的结点个数
    returninfo changeworkinpp();    //将工作指针指向左儿子、右儿子或者父亲
    returninfo findnode();			//查找结点
    returninfo addchild();          //增加左儿子或者右儿子
    returninfo deletenode();        //删除结点
    returninfo getinformation();    //获取二叉树结点和叶子信息
    returninfo gliststravel(node *searchp);//以广义表glists表示法输出二叉树
    returninfo indenttravel(node *searchp);//以凹入indent表示法输出二叉树
    returninfo preorder    (node *searchp);//递归先根遍历
    returninfo inorder     (node *searchp);//递归中根遍历
    returninfo postorder   (node *searchp);//递归后根遍历
    returninfo nrpreorder  (node *searchp);//非递归先根遍历
    returninfo nrinorder   (node *searchp);//非递归中根遍历
    returninfo nrpostorder (node *searchp);//非递归后根遍历
    returninfo levelorder  (node *searchp);//层次遍历
};
////////////////////////////////////////////////////////////////////////////////////////ok
btree::btree(node *initrootp)
{
    root=initrootp;
    workinp=NULL;
}
void btree::initfirstbracket()//回归为第一个括号为真
{
    firstbracket=1;
}
returninfo btree::createbtree(int choice)  //广义表字符串生成链接存储二叉树 
{
    bool startbuild;//判断是否可以开始建立二叉树
    char charnow;
    node *newnode;
    startbuild=0;//开始默认为不能建立二叉树
    if(root==NULL)
        startbuild=1;
    else
    {
        cout<<"安全提示： 原二叉树已经建立，操作将会将其中数据全部破坏!"<<endl;
        cout<<"您确认继续进行此操作  (Y|y):";
        cin>>answer;
        if(answer=='Y'||answer=='y')
        {
            //此处应该把原二叉树的所有结点空间用后根遍历法或链表遍历法释放空间，暂时没有提供
            startbuild=1;
        }
        else
        {
			return fail;
        }
    }
    if(startbuild==1)
    {
        if(choice==1)
        {
            cout<<endl<<"1.范例1（简单广义表）   2.范例2（复杂广义表）"<<endl;
            cin>>choice;
            if(choice==1)
                strcpy(btreedata,defaultbtree1);
            else if(choice==2)
                strcpy(btreedata,defaultbtree2);
            else
                return fail;
        }
        else
        {
            cout<<"广义表表示法输入二叉树 (注意用英文输入法)："<<endl;
			cout<<"注意：首位必须是一个字母!"<<endl;
            cout<<"【范例：a(b(c,d),d(,g)) 】"<<endl;
            cin>>btreedata;//字符数组
        }
        root=new node(btreedata[0],1);		//把第一个数据给树根
        workinp=root;						//建立当前工作指针
        linkrear=root;						//记录链表尾部，为在后面添加新结点做准备
        for(int i=1; btreedata[i]!='\0'; i++) //从第二个数据起到最后的数据为止，循环处理
        {
            charnow=btreedata[i];
            switch(charnow)
            {
            case '(':
                if(btreedata[i+1]==',')
                {
                    i=i+2; //连续往后走两步，跳过括号和逗号
                    sondeep=workinp->deep+1;//产生目前结点的深度
                    newnode=new node(btreedata[i],sondeep);
                    newnode->lchild=NULL;
                    newnode->rchild=NULL;
                    workinp->rchild=newnode; //右儿子
                    newnode->father=workinp;
                    linkrear->next=newnode;//从后面添加
                    linkrear=newnode;//尾指针后移
                    i++;//再走一步，到下一个字符
                }
                else
                {
                    i++;//往后走一步，到字符处
                    sondeep=workinp->deep+1;//产生目前结点的深度
                    newnode=new node(btreedata[i],sondeep);
                    newnode->lchild=NULL;
                    newnode->rchild=NULL;
                    workinp->lchild=newnode; //左儿子
                    newnode->father=workinp;
                    linkrear->next=newnode;//从后面添加
                    linkrear=newnode;//尾指针后移
                    workinp=workinp->lchild;//指针移位
                }
                break;
            case ',':
                i++; //往后走一步，到字符处
                workinp=workinp->father;//指针移位
                sondeep=workinp->deep+1;//产生目前结点的深度
                newnode=new node(btreedata[i],sondeep);
                newnode->lchild=NULL;
                newnode->rchild=NULL;
                workinp->rchild=newnode; //右儿子
                newnode->father=workinp;
                linkrear->next=newnode;//从后面添加
                linkrear=newnode;//尾指针后移
                workinp=workinp->rchild;//指针移位
                break;
            case ')':
                workinp=workinp->father;
                break;
            default:
                return fail;
                break;
            }
			linkrear->next=NULL;//确保单链表最后一个结点的链域为空
        }
    }
    return success;
}
returninfo btree::createroot() //建立树根
{
    bool startinput;//判断是否可以开始输入树根
    char newrootdata;
    startinput=0;//开始默认为不能输入树根
    if(root==NULL)
        startinput=1;
    else
    {
        cout<<"安全提示： 原二叉树已经建立，操作将会将其中数据全部破坏!"<<endl;
        cout<<"您确认继续进行此操作  (Y|y):";
        cin>>answer;
        if(answer=='Y'||answer=='y')
        {
            //此处原二叉树所有结点空间用后根遍历法释放空间没有提供
            startinput=1;
        }
        else
        {
            return fail;
        }
    }
    if(startinput==1)
    {
        cout<<"请输入二叉树根结点数据：";
        cin>>newrootdata;
        root=new node(newrootdata,1);	//存入二叉树根结点数据并设置深度为1
		root->lchild=NULL;				//左儿子链域置空
        root->rchild=NULL;				//右儿子链域置空
        root->father=NULL;				//父亲链域置空
        root->next  =NULL;				//单链表下一个结点链域置空
        workinp=root;					//设置工作指针为当前根结点
        linkrear=root;					//记录链表尾部，为在后面添加新结点做准备
        return success;
    }
    return success;
}
void btree::visit(node *searchp)		//显示二叉树结点数据
{
    cout<<setw(2)<<searchp->data;		//显示宽度，如果需要可修改
}
void btree::showbtreedata()
{
    cout<<btreedata;
}
int btree::rgetcount(node *searchp)      //统计二叉树中结点个数
{
	if(searchp!=NULL)
    {
        countall++;						//countall用于递归函数内部记录元素个数
        rgetcount(searchp->lchild);
        rgetcount(searchp->rchild);
    }
	return countall;
}
int btree::getcount()    //记录二叉树中的结点个数
{
    countall=0;							//递归函数计数器首先清零
	btreecount=rgetcount(root);			//btreecount用来记录当前二叉树真正的元素个数
    return btreecount;
}
returninfo btree::changeworkinpp()//转移工作指针
{
    char subchoice;		//子菜单选项变量
    if(root==NULL)
        return underflow;
    else
    {
        initfirstbracket();
		indenttravel(root);//缩格式显示二叉树
        cout<<endl;
        cout<<"1.移至当前工作指针结点的左儿子"<<endl;
        cout<<"2.移至当前工作指针结点的右儿子"<<endl;
        cout<<"3.移至二叉树的根              "<<endl;
        cout<<"4.移至当前工作指针结点的父亲  "<<endl;
        cout<<"5.放弃移动工作指针操作        "<<endl;
        cout<<"请选择：";
        cin>>subchoice;
        switch(subchoice)
        {
        case '1' :        //移至左儿子
            if(workinp->lchild==NULL)
                return nolchild;
            else
                workinp=workinp->lchild;
            break;
        case '2' :       //移至右儿子
            if(workinp->rchild==NULL)
                return norchild;
            else
                workinp=workinp->rchild;
            break;
        case '3' :       //移至树根
            workinp=root;
            break;
        case '4' :       //移至父亲
            if(workinp->father==NULL)
                return nofather;
            else
                workinp=workinp->father;
            break;
        case '5' :
            return quit;
            break;
        default:
            return fail;
            break;
        }
    }
    initfirstbracket();
	indenttravel(root);//缩格式显示二叉树
    cout<<endl;
    return success;
}
returninfo btree::findnode() //查找所需结点，利用单链表进行
{
    node *searchp;
    char finddata,newdata;//需要查找的数据、修改结点需要的新数据
    int flag=0;
    searchp=root;
    if(searchp==NULL)
        return underflow;
    cout<<"请输入你要查找的结点数据：";//查找结点
    cin>>finddata;
    while(searchp!=NULL)//在有多个相同数据时可以依次询问是否为待查数据
    {
        if(searchp->data==finddata)//判断是否和当前指针对应对象相同
        {
            cout<<endl<<"该结点的数据为：";
            visit(searchp);
            if(searchp->lchild!=NULL)
            {
                cout<<endl<<"该结点左儿子为：";
                visit(searchp->lchild);
            }
            else
                cout<<endl<<"该结点无左儿子!";
            if(searchp->rchild!=NULL)
            {
                cout<<endl<<"该结点右儿子为：";
                visit(searchp->rchild);
            }
            else
                cout<<endl<<"该结点无右儿子!"<<endl;
            cout<<endl<<"该结点数据是否为你要找的？(Y或者y):";
            cin>>answer;
            if(answer=='Y'||answer=='y')
            {
                workinp=searchp;
                flag=1;
                break;
            }
            else
                cout<<endl<<"不是你要查找的！继续查找..."<<endl;
        }
        searchp=searchp->next;
    }
    if(flag==1)
    {
        cout<<endl<<"查找到结点数据为：";
        visit(searchp); 
		cout<<endl;
        cout<<endl<<"您需要修改该数据吗？(Y或者y)";
        cin>>answer;
        if(answer=='Y'||answer=='y')
        {
			cout<<"请输入你要修改后的新数据：";//结点修改
			cin>>newdata;
			searchp->data=newdata;
            cout<<"修改成功!";
		}
		else
			cout<<"放弃修改!";
        cout<<endl;
        cout<<"当前工作指针已经指向本次查找结果结点!"<<endl;
        return success;
    }
    else
        cout<<endl<<"要查找的结点数据 "<<finddata<<" 不存在！"<<endl;
    return success;
}
returninfo btree::addchild()//增加儿子
{
    char  subchoice;
    char sondata;
    node *newnode;
    if(root==NULL)
        return underflow;
    else if(workinp->lchild!=NULL && workinp->rchild!=NULL  )
        return havetwosons;
	else
    {
        indenttravel(root);//缩格式显示二叉树
        cout<<"1.增加左儿子"<<endl;
        cout<<"2.增加右儿子"<<endl;
        cout<<"3.放弃本次操作"<<endl;
        cout<<"请选择：";
        cin>>subchoice;
        switch(subchoice)
        {
        case '1'://增加左儿子
            if(workinp->lchild!=NULL)
                return havesonl;
            else
            {
                cout<<"请输入左儿子的数据：";
                cin>>sondata;
                sondeep=workinp->deep+1;//产生目前结点的深度
                newnode=new node(sondata,sondeep);
                newnode->lchild=NULL;
                newnode->rchild=NULL;
                workinp->lchild=newnode;
                newnode->father=workinp;
                linkrear->next=newnode;//从后面添加
                linkrear=newnode;//尾指针后移
            }
            break;
        case '2'://增加右儿子
            if(workinp->rchild!=NULL)
                return havesonr;
            else
            {
                cout<<"请输入右儿子的数据：";
                cin>>sondata;
                sondeep=workinp->deep+1;//产生目前结点的深度
                newnode=new node(sondata,sondeep);
                newnode->lchild=NULL;
                newnode->rchild=NULL;
                workinp->rchild=newnode;
                newnode->father=workinp;
                linkrear->next=newnode;//从后面添加
                linkrear=newnode;//尾指针后移
            }
            break;
        case 3 :
            return quit;
            break;
        default:
            return fail;
            break;
        }
    }
    indenttravel(root);//缩格式显示二叉树
    return success;
}

returninfo btree::deletenode()      //删除结点，涉及到了单链表
{
    node *searchp,*followp,*usednode;
    if(root==NULL)
        return underflow;
    else if(workinp->lchild!=NULL || workinp->rchild!=NULL  )
        return haveason;
    cout<<"工作指针指向仅仅根或叶子结点： "<<workinp->data<<"  可以删除。请确认（Y/y）：";
    cin>>answer;
    if(answer!='Y' && answer!='y')
        return quit;
    usednode=workinp;				//用usednode管理被删结点
	if(usednode==root)				//仅有一个结点根时
	{	
		delete usednode;			//释放空间
		root=NULL;					//恢复根指针为空
		firstbracket=1;
		countall=0;					//递归函数内部统计结点个数
		btreecount=0;               //二叉树统计后的结点个数
		return success;
	}
	else
	{
		workinp=workinp->father;	//工作指针workinp回归其父亲结点
 		if(workinp->rchild==usednode)
			workinp->rchild=NULL;
		if(workinp->lchild==usednode)
			workinp->lchild=NULL;
    }
	searchp=root->next;				//启动搜索指针在单链表上寻找被删结点，仅有一个根上面已经处理
    followp=root;					//启动尾随指针后面跟进
	while (searchp!=usednode)
    {
        followp=searchp;			//尾随指针跟进
        searchp=searchp->next;		//搜索指针前移
    }
	if(usednode->next=NULL)			//被删结点为最后一个结点
		followp->next=NULL;
	else
		followp->next=usednode->next;//改链，此时searchp=usednode，即正好指向被删结点
    delete usednode;//释放空间
    return success;
}
returninfo btree::getinformation()  //获取二叉树结点和叶子信息
{
    int countnow,btreedeep;
	node *searchp;
    searchp=root;
    if(searchp==NULL)
        return underflow;
    gliststravel(root);//广义表显示二叉树
    cout<<endl;
    initfirstbracket();
    countnow=getcount();
    cout<<"结点个数为："<<countnow<<endl;
    btreedeep=0;
	searchp=root;
	while(searchp!=NULL)//此处使用了单链表
    {
        btreedeep=(searchp->deep > btreedeep) ? searchp->deep : btreedeep;
        searchp=searchp->next;
    }
    cout<<"深度为：    "<<btreedeep;
    
	if(root->next==NULL)
		cout<<endl<<"本二叉树只有一个结点,根: "<<root->data<<endl;
	else
	{
		cout<<endl<<"所有非叶子结点为：";
		searchp=root;
		while(searchp!=NULL)//此处使用了单链表
		{
			if(searchp->lchild!=NULL || searchp->rchild!=NULL)
				visit(searchp);
			searchp=searchp->next;
		}
		cout<<endl;


		searchp=root;
		cout<<"所有叶子结点为：  ";
		while(searchp!=NULL)//此处使用了单链表
		{
			if(searchp->lchild==NULL && searchp->rchild==NULL)
				visit(searchp);
			searchp=searchp->next;
		}
		cout<<endl;
    }
	
	cout<<"================"<<endl;
    cout<<"二叉树内建单链表，所有结点和深度为：";
    searchp=root;
    while(searchp!=NULL)//此处使用了单链表
    {
        cout<<searchp->data<<"("<<searchp->deep<<")  ";
        searchp=searchp->next;
    }
    cout<<endl;
	return success;
}
returninfo btree::gliststravel(node *searchp)    //以广义表表示法输出二叉树，递归，类似先根遍历
{
    if(firstbracket==1)
    {
        searchp=root;
        cout<<"以广义表表示法输出二叉树结果：";
    }
    if(searchp!=NULL)
    {
		firstbracket=0;    
		cout<<searchp->data;
        if(searchp->lchild!=NULL||searchp->rchild!=NULL)
        {
            cout<<"(";
            gliststravel(searchp->lchild);//递归处理左子树
            if(searchp->rchild!=NULL)
                cout<<",";
            gliststravel(searchp->rchild);//递归处理右子树
            cout<<")";
        }
    }
    return success;
}

returninfo btree::indenttravel(node *searchp)  //以缩格式形式输出二叉树，递归算法
{
    if(firstbracket==1)
    {
        searchp=root;
        cout<<endl<<endl<<"以缩格式形式输出二叉树结果："<<endl<<endl;

    }
    if(searchp!=NULL)
    {
        {
            firstbracket=0; 
			cout<<setw(searchp->deep*3)<<" "<<searchp->deep<<"⊙━>";//如何能显示左右呢
            visit(searchp);
            if(searchp==workinp)
                cout<<"  <==⊙此结点为当前工作指针位置!";
            cout<<endl;
            indenttravel(searchp->lchild);
            if(searchp->lchild==NULL)
                cout<<setw(searchp->deep*3+3)<<" "<<searchp->deep+1<<"⊙━>左儿子空 "<<endl;
            indenttravel(searchp->rchild);
            if(searchp->rchild==NULL)
                cout<<setw(searchp->deep*3+3)<<" "<<searchp->deep+1<<"⊙━>右儿子空 "<<endl;
        }
    }
    return success;
}
///三种递归遍历方法：先根、中根和后根
returninfo btree::preorder(node *searchp)	//先根递归遍历
{
    		
	if(firstbracket==1)						//处理显示第一个括号
    {
        searchp=root;
        if(searchp==NULL)
            return underflow;
		firstbracket=0;						//此后都不是第一个括号了		
		countnow=getcount();				//本函数中使用结点个数
        cout<<"递归先根遍历结果： (";
    }
    if(searchp!=NULL)
    {

		visit(searchp);
		countnow--;
        
        if(countnow!=0)
            cout<<",";
        else
            cout<<")"<<endl;
        preorder(searchp->lchild);
        preorder(searchp->rchild);
    }
    return success;
}
returninfo btree::inorder(node *searchp)	//中根递归遍历
{
    if(firstbracket==1)
    {
        searchp=root;
        if(searchp==NULL)
            return underflow;
        firstbracket=0;		
		countnow=getcount();				
        cout<<"递归中根遍历结果： (";
	}
    if(searchp!=NULL)
    {

		inorder(searchp->lchild);
        visit(searchp);
		countnow --;
		if(countnow!=0)
            cout<<",";
        else cout<<")"<<endl;
        inorder(searchp->rchild);
    }
    return success;
}
returninfo btree::postorder(node *searchp)	//后根递归遍历
{
    if(firstbracket==1)
    {
        searchp=root;
        if(searchp==NULL)
            return underflow;
        firstbracket=0;		
		countnow=getcount();				
        cout<<"递归后根遍历结果： (";
	}
    if(searchp!=NULL)
    {

		postorder(searchp->lchild);
        postorder(searchp->rchild);
        visit(searchp);
        countnow --;
        if(countnow!=0)
            cout<<",";
        else cout<<")"<<endl;
    }
    return success;
}
//三种非递归遍历方法：先根、中根和后根
returninfo btree::nrpreorder(node *searchp)//非递归先根遍历
{
    node *stack[Maxsize],*pnow;		//启用栈，pnow指向二叉树某个结点的地址
    int top;
    searchp=root;
    if(searchp==NULL)
        return underflow;
    top=0;							//0号地址启用存入第一个数据
    pnow=searchp;
    cout<<"非递归先根遍历结果：(";
	countnow=getcount();			
    while(!(pnow==NULL&&top==0))
    {
        while(pnow!=NULL)
        {
            visit(pnow);
			countnow--;
            if(countnow!=0)
                cout<<",";
            else
                cout<<")";
            if(top<Maxsize-1)//简单处理了一下栈的溢出问题
            {
                stack[top]=pnow;
                top++;
            }
            else
            {
                return overflow;
            }
            pnow=pnow->lchild;
        }
        if(top<=0) return success;
        else
        {
            top--;
            pnow=stack[top];
            pnow=pnow->rchild;
        }
    }
    cout<<endl;
    return success;
}
returninfo btree::nrinorder(node *searchp)//非递归中根遍历
{
    node *stack[Maxsize],*pnow;
    int top;
    searchp=root;
    if(searchp==NULL)
        return underflow;
    top=0;
    pnow=searchp;
    cout<<"非递归中根遍历结果：(";
	countnow=getcount();			
    while(!(pnow==NULL && top==0))
    {
        while(pnow!=NULL)
        {
            if(top<Maxsize-1)
            {
                stack[top]=pnow;
                top++;
            }
            else
            {
                return overflow;
            }
            pnow=pnow->lchild;
        }
        if(top<=0) return success;
        else
        {
            top--;
            pnow=stack[top];
            visit(pnow);
			countnow --;
			if(countnow!=0)
                cout<<",";
            else cout<<")";
			pnow=pnow->rchild;
        }
    }
    cout<<endl;
    return success;
}
returninfo btree::nrpostorder(node *searchp)//非递归后根遍历
{
    stackdata stack[Maxsize];//此处的栈不是仅仅存指针一个信息，而是多个信息
    node *pnow;
    int top,sign;
    searchp=root;
    if(searchp==NULL)
        return underflow;
    top=-1;
    pnow=searchp;
    cout<<"非递归后根遍历结果：(";
	countnow=getcount();	
    while(!(pnow==NULL&&top==-1))
    {
        if(pnow!=NULL)
        {
            if(top<Maxsize-1)
            {
                top++;
                stack[top].link=pnow;
                stack[top].flag=1;
                pnow=pnow->lchild;
            }
            else
                return overflow;
        }
        else
        {
            pnow=stack[top].link;
            sign=stack[top].flag;
            top--;
            if(sign==1)
            {
                top++;
                stack[top].link=pnow;
                stack[top].flag=2;
                pnow=pnow->rchild;
            }
            else
            {
                countnow --;
                visit(pnow);
                if(countnow!=0)
                    cout<<",";
                else
                    cout<<")";
                pnow=NULL;
            }
        }
    }
    cout<<endl;
    return success;
}
returninfo btree::levelorder(node *searchp)//层次遍历
{
	node *queue[Maxsize];				//注意：本队列操作没有考虑假溢出问题
	int front,rear;						//队头和队尾
    searchp=root;						//处理空二叉树
    if(searchp==NULL)
        return underflow;
	countnow=getcount();				//本函数中使用结点个数
	front=-1;							//队列指针初始化
    rear=0;
    queue[rear]=searchp;				//把根结点入队
	cout<<"层次遍历结果： (";
    while(front!=rear)
    {
        front++;
        visit(queue[front]);			//访问队首元素的数据
        countnow--;						//本次处理减少一个已经被访问的数据
    	if(countnow!=0)					//数据没有完输出逗号
            cout<<",";
        else
            cout<<")";					//数据结束时输出右括号
        if(queue[front]->lchild!=NULL)	//将队头数据的左儿子入队
        {
            rear++;
            queue[rear]=queue[front]->lchild;
        }
        if(queue[front]->rchild!=NULL)	//将队头数据的右儿子入队
        {
            rear++;
            queue[rear]=queue[front]->rchild;
        }
    }
    cout<<endl;
    return success;
}
//界面处理对象：界面库
class interfacebase
{
private:
    btree btreenow;			//数据结构对象的实例化
public:
    void showmenu(void);
    void processmenu(void);
};
void interfacebase::showmenu(void)
{
    cout<<"   二叉树链表存储功能演示  作者：heqinghqocsh         "<<endl;
    cout<<"=================================="<<endl;
    cout<<"1.第一种输入法：默认广义表		 "<<endl;
    cout<<"2.第二种输入法：键盘输入广义表    "<<endl;
    cout<<"3.第三种输入法：新建树根(逐个输入)"<<endl;
    cout<<"4.增加儿子数据                    "<<endl;
    cout<<"5.删除叶子结点或仅仅根			 "<<endl;
    cout<<"6.移动当前工作指针				 "<<endl;
	cout<<"7.查找结点并修改结点信息		     "<<endl;
    cout<<"8.用广义表和缩格法同时显示二叉树  "<<endl;
    cout<<"9.三种递归根式遍历				 "<<endl;
    cout<<"a.三种非递归根式遍历			     "<<endl;
    cout<<"s.层次遍历						 "<<endl;
    cout<<"d.查看树结点以及叶子信息		     "<<endl;
    cout<<"0.退出							 "<<endl;
    cout<<"=================================="<<endl;
}
void interfacebase::processmenu()
{
    char choice;				//用于用户选择菜单选项
    int  returnvalue;			//返回信息代码
    int  countnow;				//目前的实际结点数
    node *rootnow=NULL;			//指向根结点的为结点型变量
    cout<<"请输入选项：";
    cin>>choice;
    switch(choice)
    {
    case '1'://1.启用默认数据(广义表方式)
        cout<<"================"<<endl;
        returnvalue=btreenow.createbtree(1);
		if(returnvalue==fail)
            cout<<"已经取消建立二叉树!"<<endl;
		else
		if(returnvalue==success)
		{
			cout<<"当前广义表为: "<<endl;
			btreenow.showbtreedata();
			cout<<endl<<"二叉树建立成功!"<<endl;
        }
		cout<<"================"<<endl;
        break;
    case '2'://2.启用键盘输入(广义表方式)
        cout<<"================"<<endl;
        returnvalue=btreenow.createbtree(2);//嵌套括号式输入二叉树
		if(returnvalue==fail)
            cout<<"已经取消建立二叉树!"<<endl;
		else
		if(returnvalue==success)
			cout<<"二叉树建立成功!"<<endl;
        cout<<"================"<<endl;
        break;
    case '3'://3.新建树根(逐个数据输入二叉树)
        cout<<"================"<<endl;
        returnvalue=btreenow.createroot();//建立树根
        if(returnvalue==fail)
            cout<<"已经取消建立根!"<<endl;
		else
		if(returnvalue==success)
			cout<<"树根建立成功!"<<endl;
        cout<<"================"<<endl;
        break;
    case '4'://4.增加儿子数据
        cout<<"================"<<endl;
        returnvalue=btreenow.addchild();//增加儿子
        if(returnvalue==underflow)
            cout<<"注意：二叉树目前没有根!无法操作..."<<endl;
        if(returnvalue==havetwosons)
            cout<<"对不起，该结点同时有左儿子和右儿子!不能增加儿子!"<<endl;
        if(returnvalue==havesonl)
            cout<<"对不起，该结点有左儿子，不能增加儿子!"<<endl;
        if(returnvalue==havesonr)
            cout<<"对不起，该结点有右儿子，不能增加儿子!"<<endl;
        if(returnvalue==quit)
            cout<<"本次增加儿子操作已经放弃!"<<endl;
        if(returnvalue==fail)
            cout<<"对不起，范围输入错误，本次操作失败!"<<endl;
        if(returnvalue==success)
            cout<<"增加儿子成功!"<<endl;
        cout<<"================"<<endl;
        break;
    case '5'://5.删除数据结点
        cout<<"================"<<endl;
        cout<<"提示：仅能删除叶子结点，或仅有一个根的情况。"<<endl;
        cout<<"叶子结点删除成功后当前工作指针指向其父亲结点!"<<endl;
		cout<<"仅仅一个根删除成功后当前工作指针指向空!"<<endl;
        returnvalue=btreenow.deletenode();//删除结点
        if(returnvalue==underflow)
            cout<<"注意：二叉树目前为空!无法操作..."<<endl;
        if(returnvalue==haveason)
        {
            cout<<"对不起，当前工作指针所指结点至少有一个儿子，无法删除"<<endl;
            cout<<"请用6号功能移动当前工作指针或7号功能去查找某个叶子结点!"<<endl;
        }
        if(returnvalue==quit)
            cout<<"提示：删除结点操作已经放弃!"<<endl;
        if(returnvalue==success)
            cout<<"删除结点操作成功!"<<endl;
        cout<<"================"<<endl;
        break;
    case '6'://6.改变当前工作指针
        cout<<"================"<<endl;
        returnvalue=btreenow.changeworkinpp();//改变工作指针
        if(returnvalue==underflow)
            cout<<"注意：二叉树目前为空!无法操作..."<<endl;
        if(returnvalue==nolchild)
            cout<<"对不起，该结点没有左儿子，不能进行移动操作!"<<endl;
        if(returnvalue==norchild)
            cout<<"对不起，该结点没有右儿子，不能进行移动操作!"<<endl;
        if(returnvalue==nofather)
            cout<<"对不起，该结点没有父亲，不能进行移动操作!"<<endl;
        if(returnvalue==quit)
            cout<<"本次移动操作已经放弃!"<<endl;
        if(returnvalue==fail)
            cout<<"对不起，范围输入错误，本次操作失败!"<<endl;
        if(returnvalue==success)
            cout<<"当前工作指针指针移动成功!"<<endl;
        cout<<"================"<<endl;
        break;
	case '7'://12.查找结点
        cout<<"================"<<endl;
        returnvalue=btreenow.findnode();
        if(returnvalue==underflow)
            cout<<"注意：二叉树目前为空!无法操作..."<<endl;
        else
            cout<<"查找操作完成!..."<<endl;
        cout<<"================"<<endl;
        break;
    case '8'://7.显示二叉树(广义表和缩格法)
        cout<<"================"<<endl;
        countnow=btreenow.getcount();    //统计目前的结点个数
        if(countnow==0)
            cout<<"注意：二叉树目前为空!无法操作..."<<endl;
        else
        {
            btreenow.initfirstbracket();
			btreenow.gliststravel(rootnow);//广义表显示二叉树
            btreenow.initfirstbracket();
            btreenow.indenttravel(rootnow);//缩格式显示二叉树
        }
        cout<<"================"<<endl;
        break;
    case '9'://8.三种递归根式遍历
        cout<<"================"<<endl;
        btreenow.initfirstbracket();   //回归为第一个括号为真1
		returnvalue=btreenow.preorder(rootnow);  //递归先根遍历
        if(returnvalue==underflow)
            cout<<"注意：二叉树目前为空!无法操作..."<<endl;//同样的错误只显示一次，为简洁，成功不再提示
        btreenow.initfirstbracket();   
        returnvalue=btreenow.inorder(rootnow);	//递归中根遍历
        btreenow.initfirstbracket();
        returnvalue=btreenow.postorder(rootnow);//递归后根遍历
        cout<<"================"<<endl;
        break;
    case 'a'://9.三种非递归根式遍历
        cout<<"================"<<endl;
        returnvalue=btreenow.nrpreorder(rootnow);  //非递归先根遍历
        if(returnvalue==underflow)
            cout<<"注意：二叉树目前为空!无法操作..."<<endl;//同样的错误只显示一次，为简洁，成功不再提示
        if(returnvalue==overflow)
            cout<<"注意：栈空间不够!无法操作..."<<endl;
        returnvalue=btreenow.nrinorder(rootnow);	//非递归中根遍历
        if(returnvalue==overflow)
            cout<<"注意：栈空间不够!无法操作..."<<endl;
        returnvalue=btreenow.nrpostorder(rootnow);	//非递归后根遍历
        if(returnvalue==overflow)
            cout<<"注意：栈空间不够!无法操作..."<<endl;
        cout<<"================"<<endl;
        break;
    case 's'://10.层次遍历
        cout<<"================"<<endl;
        returnvalue=btreenow.levelorder(rootnow);//层次遍历
        if(returnvalue==underflow)
            cout<<"注意：二叉树目前为空!无法操作..."<<endl;
        else
            cout<<"层次遍历操作成功!..."<<endl;
        cout<<"================"<<endl;
        break;
    case 'd'://11.查看树结点以及叶子信息
        cout<<"================"<<endl;
        returnvalue=btreenow.getinformation();
        if(returnvalue==underflow)
            cout<<"注意：二叉树目前为空!无法操作..."<<endl;
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
    while (1)
    {
        interfacenow.showmenu();
        interfacenow.processmenu();
        system("pause");
        system("cls");
    }
    return 0;
}//主函数结束

