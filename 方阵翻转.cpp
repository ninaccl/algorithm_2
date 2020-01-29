//转圈打印矩阵
//【题目】
//方阵翻转:沿中心90度旋转
#include<stdio.h>
#include<stdlib.h>
using namespace std;
void rotateEdge(int** m,int tR,int tC,int dR,int dC,int colLength);

void rotate(int** m,int rowLength,int colLength)
{
    int tR=0;
    int tC=0;
    int dR=rowLength-1;
    int dC=colLength-1;
    while(tR<dR)
        rotateEdge(m,tR++,tC++,dR--,dC--,colLength);
}

void rotateEdge(int** m,int tR,int tC,int dR,int dC,int colLength)
{
    int times=dC-tC;
    int tmp=0;
    for(int i=0;i!=times;i++)
    {
        tmp=*((int *)m +colLength*tR+tC+i);
        *((int *)m +colLength*tR+tC+i)= *((int *)m +colLength*(dR-i)+tC);
        *((int *)m +colLength*(dR-i)+tC)=*((int *)m +colLength*dR+dC-i);
        *((int *)m +colLength*dR+dC-i)=*((int *)m +colLength*(tR+i)+dC);
        *((int *)m +colLength*(tR+i)+dC)=tmp;
    }
}

void printMatrix(int ** m,int rowLength,int colLength)
{
    for(int i=0;i<rowLength;i++)
        for(int j=0;j<colLength;j++)
        {
            printf("%d ",*((int*)m+i*colLength+j));
        }
}

int main(void)
{
	int m[4][4] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	int rowLength = 4;
	int colLength = 4;
	rotate((int **)m,rowLength,colLength);
    printMatrix((int **) m,rowLength,colLength);
	return 0;
}