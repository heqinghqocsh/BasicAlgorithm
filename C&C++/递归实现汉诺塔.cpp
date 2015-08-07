//课题名称:递归实现汉诺塔（C版）.cpp
//功能：通过递归实现汉诺塔求解

#include<iostream.h>
#include<windows.h>


void move(char pillarsource,int num,char pillartarget);//移动时的提示信息
void hanoi(int num,char pillar01,char pillar02,char pillar03);//真正的通过递归开始移动
void startmove(void);//提示信息
int num;

/*……………………………………………………………………//
函 数 名:main
描    述:主函数
入口参数:无
出口参数:无
//……………………………………………………………………*/
void main(void)
{
	SetConsoleTitle("递归实现汉诺塔（C版）"); //设置标题
	system("color f0");
	cout<<"通过递归实现汉诺塔:"<<endl;
	startmove();
	cout<<"任务完成！！！"<<endl;
    system("pause"); 
}


/*……………………………………………………………………//
函 数 名:hanoi
描    述:真正的通过递归开始移动
入口参数:pillar01为初始柱, pillar02为辅助柱, pillar03为目标柱
出口参数:无
//……………………………………………………………………*/
void hanoi(int num,char pillar01,char pillar02,char pillar03)// pillar01为初始柱, pillar02为辅助柱, pillar03为目标柱
{
    if(num==1)
        move(pillar01,1,pillar03);//递归终止条件
    else
	{
		hanoi(num-1,pillar01,pillar03,pillar02);//递归调用
		move(pillar01,num,pillar03);
		hanoi(num-1,pillar02,pillar01,pillar03);//递归调用
	}
}

/*……………………………………………………………………//
函 数 名:move
描    述:移动时的提示信息
入口参数:pillarsource为初始柱, pillartarget为目标柱
出口参数:无
//……………………………………………………………………*/
void move(char pillarsource,int num,char pillartarget) // pillarsource为初始柱, pillartarget为目标柱
{
	cout<<"把 "<< num <<" 号盘 从第 "<< pillarsource<<" 号柱 移到 第 "<<pillartarget<<" 号柱"<<endl;
}

/*……………………………………………………………………//
函 数 名:startmove
描    述:提示信息
入口参数:无
出口参数:无
//……………………………………………………………………*/
void startmove(void)
{
	cout<<"请输入总盘数:";
	cin>>num;
	hanoi(num,'1','2','3');
}
