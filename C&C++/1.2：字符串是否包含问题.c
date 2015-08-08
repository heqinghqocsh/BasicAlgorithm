/*
题目描述：
假设这有一个各种字母组成的字符串A，和另外一个字符串B，字符串里B的字母数相对少一些。
什么方法能最快的查出所有小字符串B里的字母在大字符串A里都有？
*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>

//计数排序法,只针对大写字母（可根据要求改变）
void countSort(char *oldArr,char *newArr){
	int count[26] = {0};
	int i,index;
	int lenOld = strlen(oldArr);
	int pos;
	memset(newArr,0,lenOld);//将newArr全部赋值为0
	for(i=0;i<lenOld;i++){
		pos = *(oldArr + i) - 'A';
		count[pos]++;
	}
	for(i=0;i<25;i++){
		count[i + 1] += count[i];
	}
	for(i=0;i<lenOld;i++){
		index = *(oldArr + i) - 'A';
		pos = count[index];
//		while(newArr[pos - 1] != 0){
//			pos--;
//		}
		newArr[pos - 1] = *(oldArr + i);
		count[index]--;
	}
}

//bit法，利用二进制的与或非运算，区分大小写
int contain_bit(char *longStr,char *shortStr){
	unsigned long bitLong = 0,bitShort = 0;
	while(*longStr){
		bitLong |= (unsigned long)(1l << (*longStr++ & 0x3f));//取8位ASCII码中的后六位即可确定一个字母
	}
	while(*shortStr){
		bitShort |= (unsigned long)(1l << (*shortStr++ & 0x3f));//取8位ASCII码中的后六位即可确定一个字母
	}
	return !((bitLong ^ bitShort) & bitShort);//先做异或操作，判断出是谁拥有不同的字符串，再做与操作即可确定
}
//借助hashTable法
int contain_hashTable(char *longStr,char *shortStr){
	int hash[52] = {0};
	int num = 0;
	int i = 0;
	//扫描短字符串
	for(i = 0;i < strlen(shortStr);i++){
		int index = shortStr[i] - 'A';
		if(hash[index] == 0){
			hash[index] = 1;
			num++;
		}
	}
	//扫描长字符串
	for(i = 0;i < strlen(longStr);i++){
		int index = longStr[i] - 'A';
		if(hash[index] == 1){
			hash[index]  = 0;
			num--;
			if(num == 0){
				break;
			}
		}
	}
	if(num == 0){
		return 1;
	}else{
		return 0;
	}
}

//素数方法,不能处理大量字符串,因为使用的unsigned long溢出
int contain_prime(char * stra, char * strb)
{
    int primeNumber[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
                           61, 67, 71, 73, 79, 83, 89, 97, 101};
    unsigned long bigNumber = 1; //too small for use.
    while (*stra)
    {
        bigNumber *= primeNumber[*stra - 'A'];
        stra++;
    }
    while (*strb)
    {
        if (0 != (bigNumber % primeNumber[*strb - 'A']))
        {
            break;
        }
        strb++;
    }
    if (*strb)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int contain_countSort(char *longStr,char *shortStr){
	int lenLong = strlen(longStr);
	int lenShort = strlen(shortStr);
	int i,j;
	char *longTmp = (char *)malloc(sizeof(char)*lenLong);
	char *shortTmp = (char *)malloc(sizeof(char)*lenShort);
	countSort(longStr,longTmp);
	countSort(shortStr,shortTmp);
	printf("长字符串排序后：%s\n",longTmp);
	printf("短字符串排序后：%s\n",shortTmp);
	for(i = 0,j = 0;i < lenLong && j < lenShort;){
		if(longTmp[i] == shortTmp[j]){
			j++;
			while(longTmp[i] == longTmp[i + 1]){
				i++;
			}
		}else if(longTmp[i] > shortTmp[j]){
			return 0;
		}else{
			i++;
		}
	}
	if(j == lenShort){
		return 1;
	}else{
		return 0;
	}
}

int main(){
	char longStr[50];
	char shortStr[50];
	sprintf(longStr,"ABCDFEGADCBHKJIAXCBADIKJIMNMXYZ");
	sprintf(shortStr,"CBADIKJIMNML");
	printf("利用计数排序法比较：\n");
	if(contain_countSort(longStr,shortStr)){
		printf("包含\n");
	}else{
		printf("不包含\n");
	}
	printf("利用bit法：\n");
	if(contain_bit(longStr,shortStr)){
		printf("包含\n");
	}else{
		printf("不包含\n");
	}
	printf("借助hash表法：\n");
	if(contain_hashTable(longStr,shortStr)){
		printf("包含\n");
	}else{
		printf("不包含\n");
	}

	printf("分配素数法：\n");
	if(contain_prime(longStr,shortStr)){
		printf("包含\n");
	}else{
		printf("不包含\n");
	}

}