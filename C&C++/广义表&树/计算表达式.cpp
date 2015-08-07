//计算表达式
#include<windows.h>
#include<iostream>
#include<iomanip>
#include<sstream>						//提供stringstream的功能
#include<assert.h>							
using namespace std;
enum returninfo {success,fail,overflow,underflow,nolchild,norchild,nofather,havesonl,havesonr,
                 haveason,havetwosons,range_error,quit
                };									//定义返回信息清单
#define expmaxsize 50								//定义数组长度
char defaultexp[]="12/6*(3*2+5)";					//默认表达式
bool startbuild;									//标志位：判断是否是第一次输入表达式
//栈对象//
template<class StackItemType>
class CStack
{
   private:
	   struct StackNode
	   {
	       StackItemType item;
		   StackNode* next;
	   };
	   StackNode* topPtr;
   public:
	   CStack();
	   CStack(const CStack &aStack);
	   ~CStack();
	   bool isEmpty() const;
	   void push(StackItemType newItem);
	   bool pop();
	   bool pop(StackItemType &stackTop);
	   bool getTop(StackItemType &stackTop) const;
		                                 
};
template<class StackItemType>
CStack<StackItemType>::CStack():topPtr(NULL)
{}
template<class StackItemType>
CStack<StackItemType>::CStack(const CStack &aStack)
{
   if(aStack.topPtr==NULL)
	   topPtr=NULL;
   else
   {
       topPtr=new StackNode;
	   assert(topPtr!=NULL);
	   topPtr->item=aStack.topPtr->item;
	   StackNode* newPtr=topPtr;
	   for(StackNode* origPtr=aStack.topPtr->next;origPtr!=NULL;origPtr=origPtr->next)
	   {
	       newPtr->next=new StackNode;
		   assert(newPtr->next!=NULL);
		   newPtr=newPtr->next;
		   newPtr->item=origPtr->item;
	   }
   }
}
template<class StackItemType>
CStack<StackItemType>::~CStack()
{
   while(!isEmpty())
	   pop();
}
template<class StackItemType>
bool CStack<StackItemType>::isEmpty()const
{
   return topPtr==NULL;
}
template<class StackItemType>
void CStack<StackItemType>::push(StackItemType newItem)
{
   StackNode* newPtr=new StackNode;
   assert(newPtr!=NULL);
   newPtr->item=newItem;
   newPtr->next=topPtr;
   topPtr=newPtr;
}
template<class StackItemType>
bool CStack<StackItemType>::pop()
{
   if(!isEmpty())
   {
      StackNode* temp=topPtr;
	  topPtr=topPtr->next;
	  temp->next=NULL;
	  delete temp;
	  temp=NULL;
	  return true;
   }
   else
	  return false;
}
template<class StackItemType>
bool CStack<StackItemType>::pop(StackItemType &stackTop)
{
   if(!isEmpty())
   {
      stackTop=topPtr->item;
	  StackNode* temp=topPtr;
	  topPtr=topPtr->next;
	  temp->next=NULL;
	  delete temp;
	  temp->next=NULL;
	  return true;
   }
   else
	  return false;
}
template<class StackItemType>
bool CStack<StackItemType>::getTop(StackItemType &stackTop)const
{
   if(!isEmpty())
   {
	   stackTop=topPtr->item;
	   return true;
   }
   else
	   return false;
}
//计算器对象//
class calculator
{
private:
    char answer;
    stringstream buff;							//用于输入字符串
	char infixexp[expmaxsize];					//存储表达式字符串中根形式
	char postfixexp[expmaxsize];				//存储表达式字符串后根形式
public:
    calculator() {};
    ~calculator() {};
	returninfo inputexp(int choice);			//构建数学表达式，或默认或键盘输入
	void showinfixexp();						//显示数学表达式
	void showpostfixexp();						//显示后缀表达式
	int  precedence(char op);					//返回运算符的优先级
	bool change();								//将中缀表达式转换为后缀表达式
	bool compute();								//计算后缀表达式postfixexp的值
};
returninfo calculator::inputexp(int choice)  //建立数学表达式
{
	if(startbuild==0)
        startbuild=1;
    else
    {
		cout<<"安全提示： 原数学表达式已经建立，操作将会将其破坏!"<<endl;
        cout<<"您确认继续进行此操作  (Y|y):";
        cin>>answer;
        if(answer=='Y'||answer=='y')
        {
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
            strcpy(infixexp,defaultexp);
        }
        else
        {
            cout<<"下面用键盘输入数学表达式的字符串形式 (注意用英文输入法)："<<endl;
            cout<<"范例：6.3*(1.2+2.5)-9*2"<<endl;
            cout<<"注意：输入时暂不支持负数，如：-9/3"<<endl;
            cout<<"请输入合法数学表达式的字符串形式："<<endl;
            cin>>infixexp;//字符数组
        }
    }
    buff << infixexp;					//输入字符数组
	return success;
}
void calculator::showinfixexp()
{
    cout<<infixexp<<endl;
}
void calculator::showpostfixexp()
{
    cout<<postfixexp<<endl;
}
int calculator::precedence(char op)//返回运算符的优先级
{
    switch(op)
	{
	   case '+':
	   case '-':
		   return 1;//加减同级为1
	   case '*':
	   case '/':
		   return 2;//乘除同级为2
	   case '@':
	   case '(':
	   default:
		   return 0;//其他为0
	}
}
bool calculator::change()//将中缀表达式转为后缀表达式
{
   CStack<char> charstack;//定义暂存运算符的栈，以便于按优先级将操作符放入postfixexp中
   charstack.push('@');   //放入@于栈底，并具有最低的优先级0
   int posi=0;               //扫描infixexp，指示postfixexp的待存字符的位置
   int posj=0;
   //依次扫描infixexp中缀表达式中的字符
   char charnow=infixexp[posi];
   while(charnow!='\0')//表达式没有结束时一直做
   {
       if(charnow==' ')        //对于空格不做任何处理
	       charnow=infixexp[++posi];
 	   else if(charnow=='(')   //对于'('，直接进栈
	   {
		   charstack.push(charnow);
		   charnow=infixexp[++posi];
	   }
	   else if(charnow==')')   //对于')'，使括号内的仍停留在栈中的运算符依次出栈并写入postfixexp
	   {
           char topitem;
		   if(!charstack.pop(topitem))
		   {
			   cout<<endl<<"在遇到右括号时栈已空!"<<endl;
			   return false;
		   }
		   while((topitem!='(')&&(topitem!='@'))
		   {
		       postfixexp[posj++]=topitem;
			   charstack.pop(topitem);
		   }
		   if(topitem=='@')
		   {
			   cout<<endl<<"表达式错误: 括号不匹配 !"<<endl;
			   return false;
		   }
		   charnow=infixexp[++posi];
	   }
	   //对于四则运算符，使暂存在栈顶的不低于charnow优先级的运算符出栈并写入postfixexp
	   else if((charnow=='+')||(charnow=='-')||(charnow=='*')||(charnow=='/'))
	   {
	       char topitem;
		   if(!charstack.getTop(topitem))
		   {
			   cout<<endl<<"当读取到操作符时读取栈顶时栈已空!"<<endl;
			   return false;
		   }
		   while(precedence(topitem)>=precedence(charnow))
		   {   //函数precedence()返回运算符的优先级
			   postfixexp[posj++]=topitem;
			   charstack.pop();
		       if(!charstack.getTop(topitem))
			   {
				   cout<<endl<<"当读取栈顶时栈已空!"<<endl;			   
				   return false;
			   }			   
		   }
		   charstack.push(charnow);
		   charnow=infixexp[++posi];
	   }
	   else//把数值中每一位放入postfixexp 
	   {
	       if((charnow<'0'||charnow>'9') && charnow!='.')//不是数字，也不是小数点
		   {
			   cout<<endl<<"表达式错误 :发现非法运算符或数字的符号!"<<endl;
			   return false;
		   }
		   else
		   {
		       while((charnow>='0'&&charnow<='9')||(charnow=='.'))
			   { 
			       postfixexp[posj++]=charnow;
				   charnow=infixexp[++posi];				   
			   }
		   }
		   postfixexp[posj++]=' ';//每个数字后面放个空格
	   }
   }
   //infixexp遍历完毕
   //把暂存于栈中的运算符依次退栈并写入postfixexp
   charstack.pop(charnow);
   while(charnow!='@')
   {
       if(charnow=='(')
	   {
		   cout<<endl<<"表达式错误: 括号不匹配 !"<<endl;
		   return false;
	   }
	   else
	   {
	       postfixexp[posj++]=charnow;
		   charstack.pop(charnow);
	   }
   }
   postfixexp[posj++]='\0';
   return true;
}
bool calculator::compute()//计算后缀表达式postfixexp的值
{
   CStack<double> doublestack;//用该栈存储操作数和中间结果
   double partinteger,partdecimal;  //用于保存浮点数，partinteger为整数部分，partdecimal为小数部分
   double topX,topY;          //保存每个操作符的两个操作数
   int posi=0;                   //用于遍历后缀表达式
   while(postfixexp[posi])
   {
       if(postfixexp[posi]==' ')//遇到空格不做处理
	   {
	       posi++;
		   continue;
	   }
	   switch(postfixexp[posi])
	   {
	       case '+'://做栈顶两个元素的加法，和赋给partinteger
			   if(!(doublestack.pop(topX) && doublestack.pop(topY)))
			   {
				   cout<<endl<<"表达式错误 !"<<endl;
				   return false;
			   }
			   partinteger=topX+topY;
			   posi++;
			   doublestack.push(partinteger);
			   break;
		   case '-'://做栈顶两个元素的减法，差赋给partinteger
			   if(!(doublestack.pop(topX) && doublestack.pop(topY)))
			   {
				   cout<<endl<<"表达式错误 !"<<endl;
				   return false;
			   }
			   partinteger=topY-topX;
			   posi++;
			   doublestack.push(partinteger);
			   break;
		   case '*'://做栈顶两个元素的乘法，积赋给partinteger
			   if(!(doublestack.pop(topX) && doublestack.pop(topY)))
			   {
				   cout<<endl<<"表达式错误 !"<<endl;
				   return false;
			   }
			   partinteger=topX*topY;
			   posi++;
			   doublestack.push(partinteger);
			   break;
		   case '/'://做栈顶两个元素的除法，商赋给partinteger
			   if(!(doublestack.pop(topX) && doublestack.pop(topY)))
			   {
				   cout<<endl<<"表达式错误 !"<<endl;
				   return false;
			   }
			   if(topX!=0.0)
				   partinteger=topY/topX;
			   else
			   {
			       cout<<endl<<"表达式错误 : 除数为0 !"<<endl;
				   return false;
			   }
			   posi++;
			   doublestack.push(partinteger);
			   break;
		   default:
			   //利用partinteger保存扫描到的整数部分的值
			   partinteger=0;										//基准为0
			   while(postfixexp[posi]>=48 && postfixexp[posi]<=57)	//测试字符是否为字符数字
			   {
			       partinteger=partinteger*10+postfixexp[posi]-48;  //字符数字转换成真正数字，并实现多位数
				   posi++;											//循环移动到下一个字符
			   }
			   //利用partdecimal保存扫描到的小数部分的值
			   if(postfixexp[posi]=='.')							//一旦遇到小数点，后面就是小数部分
			   {
			       partdecimal=0;									//基准为0
				   posi++;											//小数点后第一位
				   double tentimes=10.0;
				   while(postfixexp[posi]>=48 && postfixexp[posi]<=57)
				   {
				       partdecimal=partdecimal+(postfixexp[posi]-48)/tentimes;
					   posi++;
					   tentimes*=10;
				   }
				   partinteger+=partdecimal;	//把整数部分和小数部分合在一起			   			   
			   }
			   doublestack.push(partinteger);
	   }
   }
   if(doublestack.isEmpty())
   {
	   cout<<endl<<"表达式错误 !"<<endl;
	   return false;
   }
   doublestack.pop(partinteger);
   if(doublestack.isEmpty())
   {
	   cout<<endl<<"计算结果是："<<endl<<partinteger<<endl<<endl;
	   return true;
   }
   else
   {
	   cout<<endl<<"表达式错误 !"<<endl;
	   return false;
   }
}
//界面对象
class interfacebase
{
private:
    calculator calculatornow;			//数据结构对象的实例化
public:
    void showmenu(void);
    void processmenu(void);
};
void interfacebase::showmenu(void)
{
    cout<<"        计算表达式功能演示        "<<endl;
    cout<<"=================================="<<endl;
    cout<<"1.启用默认表达式                  "<<endl;
    cout<<"2.键盘输入                        "<<endl;
    cout<<"3.计算表达式                      "<<endl;
    cout<<"0.退出							 "<<endl;
    cout<<"=================================="<<endl;
}
void interfacebase::processmenu()
{
    char choice;				//用于用户选择菜单选项
    int  returnvalue;			//返回信息代码
    cout<<"请输入选项：";
    cin>>choice;
 	switch(choice)
    {
    case '1'://1.启用默认数据
        cout<<"================"<<endl;
        returnvalue=calculatornow.inputexp(1);
        if(returnvalue==fail)
            cout<<"已经取消建立表达式!"<<endl;
        else if(returnvalue==success)
        {
            cout<<"当前表达式字符串为: "<<endl;
            calculatornow.showinfixexp();
            cout<<"表达式建立成功!"<<endl;
        }
        cout<<"================"<<endl;
        break;
    case '2'://2.启用键盘输入
        cout<<"================"<<endl;
        returnvalue=calculatornow.inputexp(2);
        if(returnvalue==fail)
            cout<<"已经取消建立表达式!"<<endl;
        else if(returnvalue==success)
        {
            cout<<"当前表达式字符串为: "<<endl;
            calculatornow.showinfixexp();
            cout<<"表达式建立成功!"<<endl;
        }
        cout<<"================"<<endl;
        break;
     case '3'://3.计算表达式
        cout<<"================"<<endl;
		cout<<"当前表达式字符串为: "<<endl;
        calculatornow.showinfixexp();
		if(calculatornow.change()==1)
		{
			cout<<endl<<"对应的后缀表达式："<<endl;
			calculatornow.showpostfixexp();
			cout<<"计算表达式开始... "<<endl;
			calculatornow.compute();
		}
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
    startbuild=0;
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