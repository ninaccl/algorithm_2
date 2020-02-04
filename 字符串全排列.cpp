#include <string>
#include <iostream>
#include <set>

using namespace std;

void swap(string& str, int i, int j)
{
    char temp = str[j];
    str[j]=str[i];
    str[i]=temp;
}

void printAllPermutations1(string str, int i)
{
    if(i == str.length())
    {
        cout<<str<<endl;
        return;
    }
    for(int j=i;j<str.length();j++)
    {
        //分别跟每一位置交换
        swap(str,i,j);
        //全排列
        printAllPermutations1(str,i+1);
        //回溯
        swap(str,j,i);
    }
}

//不能出现重复的排列
void printAllPermutations2(string str,int i)
{
    if(i == str.length())
    {
        cout<<str<<endl;
        return;
    }
    set<char> a;
    for(int j=i;j<str.length();j++)
    {
        if(a.find(str[j]) != a.end())
            continue;
        a.insert(str[j]);
        swap(str,i,j);
        printAllPermutations2(str,i+1);
        //回溯
        swap(str,j,i);
    }
}

int main(void)
{
    string test = "acc";
    printAllPermutations1(test,0);
    cout<<"========"<<endl;
    printAllPermutations2(test,0);
}