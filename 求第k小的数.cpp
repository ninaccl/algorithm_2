// BFPRT算法 可参见左神进阶第二章 O(N)
// int bfprt(arr, k)
// 1)分组，每五个一组 O(1)
// 2)组内排序 O(N)
// 3)中位数拿出组成N/5大小的数组 O(N)
// 4)递归调用BFPRT bfprt(new_arr, new_arr.length/2)-> 求中位数的中位数 会有至少3N/10的数比这个数大（小） T(N/5)
// 5)用上一步的返回值划分原数组，小于放左边，大于放右边 O(N)
// 6)命中直接返回，没命中看左边或者右边 T(7N/10)


#include<iostream>
#include<algorithm>
using namespace std;

int InsertSort(int  array[], int left, int right);                 //插入排序，返回中位数下标
int GetPivotIndex(int  array[], int left, int right);              //返回中位数的中位数下标
int Partition(int array[], int left, int right, int pivot_index);  //利用中位数的中位数的下标进行划分，返回分界线下标
int BFPRT(int array[], int left, int right, const int & k);        //求第k小，返回其位置的下标

int main()
{
    int k = 5;
    int array[10] = { 1,1,2,3,1,5,-1,7,8,-10 };

    cout << "原数组：";
    for (int i = 0; i < 10; i++)
        cout << array[i] << " ";
    cout << endl;

    cout << "第" << k << "小值为：" << array[BFPRT(array, 0, 9, k)] << endl;

    cout << "变换后的数组：";
    for (int i = 0; i < 10; i++)
        cout << array[i] << " ";
    cout << endl;

    return 0;
}

/* 插入排序，返回中位数下标 */
int InsertSort(int array[], int left, int right)
{
    int temp;
    int j;
    for (int i = left + 1; i <= right; i++)
    {
        temp = array[i];
        j = i - 1;
        while (j >= left && array[j] > temp)
            array[j + 1] = array[j--];
        array[j + 1] = temp;
    }

    return ((right - left) >> 1) + left;
}

/* 返回中位数的中位数下标 */
int GetPivotIndex(int array[], int left, int right)
{
    if (right - left < 5)
        return InsertSort(array, left, right);

    int sub_right = left - 1;
    for (int i = left; i + 4 <= right; i += 5)
    {
        int index = InsertSort(array, i, i + 4);  //找到五个元素的中位数的下标
        swap(array[++sub_right], array[index]);   //依次放在左侧
    }

    return BFPRT(array, left, sub_right, ((sub_right - left + 1) >> 1) + 1);
}

/* 利用中位数的中位数的下标进行划分，返回分界线下标 */
int Partition(int array[], int left, int right, int pivot_index)
{
    swap(array[pivot_index], array[right]);  //把基准放置于末尾

    int divide_index = left;  //跟踪划分的分界线
    for (int i = left; i < right; i++)
    {
        if (array[i] < array[right])
            swap(array[divide_index++], array[i]);  //比基准小的都放在左侧
    }

    swap(array[divide_index], array[right]);  //最后把基准换回来
    return divide_index;
}

int BFPRT(int array[], int left, int right, const int & k)
{
    int pivot_index = GetPivotIndex(array, left, right);            //得到中位数的中位数下标
    int divide_index = Partition(array, left, right, pivot_index);  //进行划分，返回划分边界
    int num = divide_index - left + 1;
    if (num == k)
        return divide_index;
    else if (num > k)
        return BFPRT(array, left, divide_index - 1, k);
    else
        return BFPRT(array, divide_index + 1, right, k - num);
}
