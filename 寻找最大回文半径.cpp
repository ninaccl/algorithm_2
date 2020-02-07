// Manacher算法
// 寻找最大回文数
// 回文半径数组 最右回文右边界R  回文右边界的最早中心c（第一次到达该边界时的中心）

// 可能性1 当前位置i不在回文右边界里面，暴力扩
// 可能性2 当前位置i在回文右边界里面，i关于回文中心c的对称点i'的回文半径在回文边界L，R里面，i位置的回文半径和i‘一样
// 可能性3 当前位置i在回文右边界里面，i关于回文中心c的对称点i'的回文半径不在回文边界L，R里面，i位置的回文半径为i到R
// 可能性4 当前位置i在回文右边界里面，i关于回文中心c的对称点i'的回文半径与回文边界L重合，i位置的回文半径
//        从i到R不用验证，从R右边的位置开始继续比对

#include <string>
#include <iostream>

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

int maxLcpsLength(string str) 
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
        maxres = max(maxres, pArr[i]);
    }
    delete []pArr;
    return maxres/2;
}

using namespace std;

int main(void)
{
    string str1 = "abc1234321ab";
    string str = "12";
    cout<<maxLcpsLength(str1)<<endl;
    return 0;
}