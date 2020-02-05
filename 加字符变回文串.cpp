// Manacher算法扩展题目
// 给定一个字符串str1,只能往str1的后面添加字符变成str2,要求str2
// 整体都是回文串且最短。
// 举例:
// str1 = ABC12321, 返回ABC12321CBA

//解决方法：需找到最后一位的最大半径，之后对前面进行拷贝

#include <iostream>
#include <string>

using namespace std;

string manacherString(string str) 
{
	string res;
	int index = 0;
	for (int i = 0; i < str.length(); i++) 
    {
        res += "#";
        res += str[i];
	}
    res+="#";
	return res;
}

string shortestEnd(string str)
{
    if (str.empty()) 
		return 0;
	string strmodified = manacherString(str);
    int len = strmodified.length();
	int* pArr = new int[len];
	int mid = -1;
	int pR = -1;
	int maxres = 0;
    for (int i = 0; i < len; i++) 
    {
        pArr[i] = pR > i ? min(pArr[2 * mid - i], pR - i) : 1;
        while (i + pArr[i] < len && i - pArr[i] > -1) {
            if (strmodified[i + pArr[i]] == strmodified[i - pArr[i]])
                pArr[i]++;
            else 
                break;
        }
        if (i + pArr[i] > pR) 
        {
            pR = i + pArr[i];
            mid = i;
        }
        if(pR == len-1)
            break;
    }
    string res = str;
    for(int i = (mid - pArr[mid])/2; i>=0 ; i--)
        res += str[i];
    delete []pArr;
    return res;
}

int main(void)
{
    string str1 = "ABC12321";
    string str = "45535";
    cout<<shortestEnd(str)<<endl;
    return 0;
}