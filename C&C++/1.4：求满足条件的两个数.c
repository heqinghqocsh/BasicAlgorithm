/*
题目：
输入一个数组和一个数字，在数组中查找两个数，使得它们的和正好是输入的那个数字。
*/
//代码一  
//O（N）  
Pair findSum(int *s,int n,int x)     
{     
    //sort(s,s+n);   如果数组非有序的，那就事先排好序O（N*logN）     
      
    int *begin=s;     
    int *end=s+n-1;     
      
    while(begin<end)    //俩头夹逼，或称两个指针两端扫描法，很经典的方法，O（N）    
    {     
        if(*begin+*end>x)     
        {     
            --end;     
        }     
        else if(*begin+*end<x)     
        {     
            ++begin;     
        }     
        else    
        {     
            return Pair(*begin,*end);     
        }     
    }     
      
    return Pair(-1,-1);     
}     
  
//或者如下编写，  
//代码二  
//copyright@ zhedahht && yansha  
//July、updated，2011.05.14。  
bool find_num(int data[], unsigned int length, int sum, int& first_num, int& second_num)  
{     
    if(length < 1)  
        return true;  
      
    int begin = 0;  
    int end = length - 1;  
      
    while(end > begin)  
    {  
        long current_sum = data[begin] + data[end];  
          
        if(current_sum == sum)  
        {  
            first_num = data[begin];  
            second_num = data[end];  
            return true;  
        }  
        else if(current_sum > sum)  
            end--;  
        else  
            begin++;  
    }  
    return false;  
}  