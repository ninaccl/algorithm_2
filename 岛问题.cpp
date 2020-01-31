#include <iostream>

using namespace std;

void infect(int **m, int i, int j, int row, int col)
{
    if(i<0 || i>=row || j<0 || j>=col || *((int *)m+col*i+j)!=1)
        return;
    *((int *)m + i*col + j) = 2;
    infect(m, i + 1, j, row, col);
    infect(m, i - 1, j, row, col);
    infect(m, i, j + 1, row, col);
    infect(m, i, j - 1, row, col);
}

int countIslands(int **m, int row, int col)
{
    if(m == NULL || row == 0 || col == 0)
        return 0; 
    int res = 0;
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
        {
            if(*((int *)m+col*i+j) == 1)
            {
                res++;
                infect(m, i, j, row, col);
            }
        }
        return res;
}

int main(void) 
{
    int m1[][9] = {  { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
                    { 0, 1, 1, 1, 0, 1, 1, 1, 0 }, 
                    { 0, 1, 1, 1, 0, 0, 0, 1, 0 },
                    { 0, 1, 1, 0, 0, 0, 0, 0, 0 }, 
                    { 0, 0, 0, 0, 0, 1, 1, 0, 0 }, 
                    { 0, 0, 0, 0, 1, 1, 1, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, };
    cout<<countIslands((int **)m1,7,9)<<endl;

    int m2[][9] = {  { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
                    { 0, 1, 1, 1, 1, 1, 1, 1, 0 }, 
                    { 0, 1, 1, 1, 0, 0, 0, 1, 0 },
                    { 0, 1, 1, 0, 0, 0, 1, 1, 0 }, 
                    { 0, 0, 0, 0, 0, 1, 1, 0, 0 }, 
                    { 0, 0, 0, 0, 1, 1, 1, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, };
    cout<<countIslands((int **)m2,7,9)<<endl;
}
