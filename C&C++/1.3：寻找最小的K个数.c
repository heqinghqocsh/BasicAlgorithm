/*
题目描述：输入n个数，寻找其中最小的k个数
*/
#include<stdio.h>
#include<stdlib.h>

#define MAX_NUM 100000  //产生的随机数的个数最大值
#define K 10            //寻找最小的数
#define NUM 20          //从data.txt 中读取num个数组

/*
函数功能：产生随机数，然后写到data.txt文件中
*/
void random_num(){
	long num = 0;
	long i = 1;
	FILE *fp;
	fp = fopen("data.txt","w");
	if(fp == NULL){
		printf("文件打开失败!\n");
		return ;
	}
	printf("请输入需要产生的随机数的个数（<=%d）\n",MAX_NUM);
	scanf("%ld",&num);
	if(num > MAX_NUM){
		printf("输入的个数过大!");
		return;
	}
	srand((unsigned)time(NULL));
	for(i = 1;i <= num;i++){
		long temp = rand() % 100000;
		fprintf(fp,"%ld ",temp);
	}
	fclose(fp);
}

/*
打印前k个数
*/
void print_K(long a[],int k){
	int i = 1;
	printf("数组的前k个数为：\n");
	for(i = 1;i <= k;i++){
		printf("%ld  ",a[i]);
	}
	printf("\n");
}


/*
交换两个数
*/
void swap(long *a,long *b){
	long tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
快速排序中的分治方法----随机主元
*/
int partition_rand(long a[],int first,int last){
	int pivot = first + rand() % (last - first + 1);
	long key;
	swap(&a[first],&a[last]);

	key = a[first];
	while(first < last){
		while(first < last && a[last] >= key){
			last--;
		}
		swap(&a[first],&a[last]);
		while(first < last && a[first] <= key){
			first++;
		}
		swap(&a[first],&a[last]);
	}
	return first;
}

/*
快速排序中分治方法-----固定主元
*/
int partition(long a[],int first,int last){
	long key = a[first];
	while(first < last){
		while(first < last && a[last] >= key){
			last--;
		}
		swap(&a[first],&a[last]);
		while(first < last && a[first] <= key){
			first++;
		}
		swap(&a[first],&a[last]);
	}
	return first;
}

/*
快速排序算法----随机主元
*/
void quick_sort_rand(long a[],int first,int last){
	if(first < last){
		int pivot = partition_rand(a,first,last);
		quick_sort_rand(a,first,pivot - 1);
		quick_sort_rand(a,pivot + 1,last);
	}
}

/*
快速排序算法----固定主元
*/
void quick_sort(long a[],int first,int last){
	if(first < last){
		int pivot = partition(a,first,last);
		quick_sort(a,first,pivot - 1);
		quick_sort(a,pivot + 1,last);
	}
}

/*
程序运行前的初始化
*/

long* init(){
	long a[NUM + 1];
	int i = 1;
	FILE *fp = NULL;
	random_num();//产生随机数
	
	fp = fopen("data.txt","r");
	if(fp == NULL){
		printf("无法打开文件data.txt!\n");
		return;
	}
	while((fscanf(fp,"%ld",&a[i])) != EOF && (i <= NUM)){
		i++;
	}
	printf("从data.txt文件中读取的%d个数是：\n",NUM);
	for(i = 1;i <= NUM;i++){
		if(i % 11 == 0){
			printf("\n");
		}
		printf("%ld ",a[i]);
	}
	printf("\n\n");
	fclose(fp);
	return a;
}

void main(){
	int first = 1;
	int last = NUM;
	long b[NUM + 1];
	long *a = init();
	memcpy(b,a,sizeof(a));
//	quick_sort_rand(b,first,last);
//	printf("通过快速排序（随机主元）找到的最小的 %d 个数为：\n",K);
//	print_K(b,K);

	quick_sort(b,first,last);
	printf("通过快速排序（固定主元）找到的最小的 %d 个数为：\n",K);
	print_K(b,K);
	


}