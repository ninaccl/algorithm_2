#include<string>
#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;
bool myCompare(string a,string b)
{
    return (a+b).compare(b+a)<=0;
}

string lowerString(vector<string> strs)
{
    if(strs.size()==0)
        return "";
    sort(strs.begin(),strs.end(),myCompare);
    string res;
    for(int i=0;i<strs.size();i++)
        res+=strs[i];
    return res;
}

int main(void)
{
    vector<string> strs = {"jibw", "ji", "jp", "bw", "jibw"};
    vector<string> strs2 = {"b", "ba", "cd", "bc", "jibw"};
    cout<<lowerString(strs2)<<endl;
    return 0;
}