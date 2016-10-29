#include <stdio.h>
#include <string.h>
/*
整理时间：2015-8-6  by：heqinghqocsh
*/
/*题目描述：
	定义字符串的左旋转操作：把字符串前面的若干个字符移动到字符串的尾部，
	如把字符串abcdef左旋转2位得到字符串cdefab。请实现字符串左旋转的函数，
	要求对长度为n的字符串操作的时间复杂度为O(n)，空间复杂度为O(1)。 				
*/

//暴力移位法(复杂度为O(m*n))
void violenceShift1(char * arr, int n)
{
    size_t tmpLen = strlen(arr);//注意此长度不包含结束符('/0')
    char tmpChar;
    int i, j;
    if (n >= 0)//当n大于0时，为左旋转（即将左边的n个字符移到末尾）
    {
		while(n--){
			tmpChar = *arr;//保存第一个字符
			for(i = 0; i < tmpLen; i++){
				*(arr + i) = *(arr + i + 1);
			}
			*(arr + tmpLen - 1) = tmpChar;
		}
    }
    else//当n小于0时，为右旋转（即将右边的n个字符移到开头）
    {
		while(n++){
			tmpChar = *(arr + tmpLen -1);//减一是因为字符串以‘/0’结尾要占一位
			for(i = tmpLen - 1; i > 0; i--){
				*(arr + i) = *(arr + i - 1);
			}
			*arr = tmpChar;
		}
    }
}
//指针移位法(复杂度为O(m+n))
void leftShift2(char * arr, int len, int n)
{
    int i;
    size_t tmpLen = len;
    int p0 = 0;
    int p1 = n;
    char tmpChar;
    while (p1 + n - 1 < tmpLen)//判断是否越界
    {
        tmpChar = *(arr + p0);
        *(arr + p0) = *(arr + p1);
        *(arr + p1) = tmpChar;
        p0++;
        p1++;
    }
    while (p1 < tmpLen)//当p1小于字符串的长度时要处理尾巴
    {
        tmpChar = *(arr + p1);
        for (i = p1; i > p0; i--)
        {
            *(arr + i) = *(arr + i - 1);
        }
        *(arr + p0) = tmpChar;
        p0++;
        p1++;
    }
}

//指针移位法,尾部处理用递归
void leftShift3(char * arr, int len, int n)
{
    size_t tmpLen = len;
    int p0 = 0;
    int p1 = n;
    char tmpChar;
    while (p1 + n - 1 < tmpLen)
    {
        tmpChar = *(arr + p0);
        *(arr + p0) = *(arr + p1);
        *(arr + p1) = tmpChar;
        p0++;
        p1++;
    }
    if (p1 < tmpLen)
    {
        leftShift2(arr + p0, len - p0, n);
    }
}

//指针移位法,递归
void leftShift4(char * arr, int len, int n)
{
    size_t tmpLen = len;
    int p0 = 0;
    int p1 = n;
    char tmpChar;
	int i;
    while (p1 < tmpLen)
    {
        tmpChar = *(arr + p0);
        *(arr + p0) = *(arr + p1);
        *(arr + p1) = tmpChar;
        p0++;
        p1++;
    }
    i = n - tmpLen%n;
    if (i != 0 && p0 != tmpLen - 1)//最后一个条件保证i=n(即tmplen%n=0)时的漏洞
    {
        leftShift4((arr + p0), n, i);
    }
}

//三步翻转法
/*
思路：将一个字符串分成两部分，X和Y两个部分，在字符串上定义反转的操作X^T，
即把X的所有字符反转（如，X="abc"，那么X^T="cba"），那么我们可以得到下面的结论：(X^TY^T)^T=YX。
显然我们这就可以转化为字符串的反转的问题了。ok,就拿abcdef 这个例子来说，若要让def翻转到abc的前头
，那么只要按下述3个步骤操作即可：
1、首先分为俩部分，X:abc，Y:def；
2、X->X^T，abc->cba， Y->Y^T，def->fed。
3、(X^TY^T)^T=YX，cbafed->defabc，即整个翻转。
*/
void myinvert(char * start, char * end)
{
    char tmpChar;
    while (start < end)
    {
        tmpChar = *start;
        *start = *end;
        *end = tmpChar;
        start++;
        end--;
    }
}
void leftShift5(char * arr, int len, int n)
{
    myinvert(arr, arr + n - 1);
    myinvert(arr + n, arr + len - 1);
    myinvert(arr, arr + len - 1);
}
int gcd(int m, int n)
{
    int r;
    while ((r = m % n))
    {
        m = n;
        n = r;
    }
    return n;
}
//分组循环移位法
void leftShift6(char * arr, int len, int n)
{
    int group = gcd(len, n);
    char tmpChar;
    int x = len / group;
    int i, j;
    for (i = 0; i < group; i++)
    {
        tmpChar = *(arr + i);
        for (j = 0; j < x - 1; j++)
        {
            *(arr + (i + (j * n)) % len) = *(arr + (i + (j * n) + n) % len);
        }
        *(arr + (i + (j * n)) % len) = tmpChar;
    }
}
int main()
{
    char str[50];
    sprintf(str, "abcdefghijk");
    printf("原始字符串为 :%s\t长度为为 :%d\n", str, strlen(str));
    printf("\n");
    violenceShift1(str, 2);
    printf("暴力移位法（左移2位） :%s\n", str);
    violenceShift1(str, -2);
    printf("暴力移位法（右移2位） :%s\n", str);
    violenceShift1(str, 3);
    printf("暴力移位法（左移3位） :%s\n", str);
    violenceShift1(str, strlen(str) - 3);
    printf("暴力移位法（右移3位） :%s\n", str);
    printf("\n");

    leftShift2(str, strlen(str), 3);
    printf("指针移位法（左移3位） :%s\n", str);
    leftShift2(str, strlen(str), strlen(str) - 3);
    printf("指针移位法（右移3位） :%s\n", str);
    leftShift2(str + 2, strlen(str) - 2, 2);
    printf("指针移位法（从第三位开始左移2位） :%s\n", str);
    leftShift2(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("指针移位法（从第三位开始右移2位） :%s\n", str);
    printf("\n");


    leftShift3(str, strlen(str), 3);
    printf("指针移位法（尾部用递归） :%s\n", str);
    leftShift3(str, strlen(str), strlen(str) - 3);
    printf("指针移位法（尾部用递归） :%s\n", str);
    leftShift3(str + 2, strlen(str) - 2, 2);
    printf("指针移位法（尾部用递归） :%s\n", str);
    leftShift3(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("指针移位法（尾部用递归） :%s\n", str);
    printf("\n");

    leftShift4(str, strlen(str), 3);
    printf("指针移位法（用递归） :%s\n", str);
    leftShift4(str, strlen(str), strlen(str) - 3);
    printf("指针移位法（用递归） :%s\n", str);
    leftShift4(str + 2, strlen(str) - 2, 2);
    printf("指针移位法（用递归） :%s\n", str);
    leftShift4(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("指针移位法（用递归） :%s\n", str);
    printf("\n");

    leftShift5(str, strlen(str), 3);
    printf("三步翻转法 :%s\n", str);
    leftShift5(str, strlen(str), strlen(str) - 3);
    printf("三步翻转法 :%s\n", str);
    leftShift5(str + 2, strlen(str) - 2, 2);
    printf("三步翻转法 :%s\n", str);
    leftShift5(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("三步翻转法 :%s\n", str);
    printf("\n");

    leftShift6(str, strlen(str), 3);
    printf("分组循环移位法 :%s\n", str);
    leftShift6(str, strlen(str), strlen(str) - 3);
    printf("分组循环移位法 :%s\n", str);
    leftShift6(str + 2, strlen(str) - 2, 2);
    printf("分组循环移位法 :%s\n", str);
    leftShift6(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("分组循环移位法 :%s\n", str);
    printf("\n");


    return 0;
}
