// 2016 408统考题，把一个set划分为两个子集，使得两子集的尺寸差距最小二两子集各自的元素和的差距最大
//思路就是类似快速排序，找到一个分割点，刚好等于和特别小的那个子集的尺寸。
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void swap(int * arr, int i, int j)
{
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
}
void printarr(int * arr, int len)
{
        for (int i = 0; i < len; ++i)
        {
                printf("%d ", arr[i]);
        }
        printf("\n");

}
int func(int * arr, int n)
{
        int n1 = n / 2;
        int n2 = n - n1;
        int pivot = arr[n-1];
        int low = 0;
        int high = n-1;

        for (;;)
        {
                // 一趟快速排序
                int i = low;
                int j = high;

                while (i < j)
                {
                        while (i<j && arr[i] <= pivot)
                        {
                                i++;
                        }
                        swap(arr, i, j);
                        while (i<j && arr[j] >= pivot)
                        {
                                j--;
                        }
                        swap(arr, i, j);
                }
                //arr[i] = arr[pivot];
                printf("pivot=%d, i:%d, j:%d, n1:%d\n", pivot, i, j, n1);
                printarr(arr, n);
                if (n1 == i)
                {
                        return 0;
                }
                else if (n1 > i)
                {
                        n1 = n1 - i;
                        low = i+1;
                        pivot = arr[high];
                }
                else // n1 < pivot
                {
                        high = i-1;
                        pivot = arr[high];
                }

        }
        return 0;
}

int main()
{
        int arr[] = { 1,4,3,6,2,7,5};
        int len = sizeof(arr)/sizeof(int);
        func(arr, len);
        return 0;

}
