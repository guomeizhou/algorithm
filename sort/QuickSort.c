#include <stdio.h>

/*
 * 由来: 快速排序是对冒泡排序的一种改进。
 * 平均时间复杂度: O(nlogn)。
 * 平均空间复杂度: O(logn)。
 * 具有不稳定性。
 */

/* 时间复杂度分析
 * 最好情况: 每次通过中值划分后产生的区间大小都为n/2时，时间复杂度是O(nlogn)；
 * 最坏情况: 每次通过中值划分后产生的区间大小分别是n-1和1的时(即：已经有序和逆序)，时间复杂度是O(n^2)；
 */

/*
 * 快速排序的关键点：把待排序列中的哪个值作为中值。
 * 该程序把待排序列中的第1个值作为中值。
 * 其它选中值的方法: 
 * (1) 把待排序列中间位置的值作为中值；
 * (2) 比较待排序列开头、中间、结尾3个数据值，把大小处在中间的值作为中值(平衡快排)；
 * (3) 随机产生一个待排序列的索引值，把该索引值所对应的值作为中值(随机化快排)。
 */

/* 程序输出如下:
[********** Before QuickSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After QuickSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 快速排序。
 *       需要多趟排序；
 *       在一趟排序中，将要排序的数据分割成三部分，中间部分只有一个数据，
 *       左部分的所有数据都小于或等于中间部分的数据，中间部分的数据小于或等于右部分的所有数据，
 *       然后再按此方法分别对左部分数据和有部分数据继续进行快速排序，
 *       整个排序过程可以递归进行，最终使整个数据变得有序。
 * 名称: QuickSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLeft，待排序的数组的开始下标位置。
 * 参数: int nRight，待排序的数组的结束下标位置。
 * 返回值: void。
 */
void QuickSort(int* pData, int nLeft, int nRight);

/*
 * 功能: 把pData[nLeft]作为中值，在[nLeft, nRight]中为该中值找个位置，并把该中值放到该位置上，
 *       结果是该中值左边的数都小于或等于该中值，该中值右边的数都大于或等于该中值。
 * 名称: Partition。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLeft，待排序的数组的开始下标位置。
 * 参数: int nRight，待排序的数组的结束下标位置。
 * 返回值: int，返回中值在[nLeft, nRight]中的下标位置。
 */
int Partition(int* pData, int nLeft, int nRight);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before QuickSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	QuickSort(arrData, 0, sizeof(arrData) / sizeof(int) - 1);

	printf("[********** After QuickSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void QuickSort(int* pData, int nLeft, int nRight)
{
    // nPivotPos: 中值在[nLeft, nRight]中的下标位置。
    int nPivotPos = 0;
    if (nLeft < nRight)
    {
        nPivotPos = Partition(pData, nLeft, nRight);
        QuickSort(pData, nLeft, nPivotPos - 1);
        QuickSort(pData, nPivotPos + 1, nRight);
    }
}

int Partition(int* pData, int nLeft, int nRight)
{
    // 把最左边的值作为中值。
    int nPivotValue = pData[nLeft];
    // 找出中值的下标位置，把大于中值的值放到中值的左边，把小于中值的值放到中值的右边。
    while (nLeft < nRight)
    {
        while (nLeft < nRight && nPivotValue <= pData[nRight])
        {
            --nRight;
        }
        if (nLeft < nRight)
        {
            pData[nLeft] = pData[nRight];
            ++nLeft;
        }

        while (nLeft < nRight && pData[nLeft] <= nPivotValue)
        {
            ++nLeft;
        }
        if (nLeft < nRight)
        {
            pData[nRight] = pData[nLeft];
            --nRight;
        }
    }
    pData[nLeft] = nPivotValue;

    // 返回中值的下标位置。
    return nLeft;
}

void Output(const int* pData, int nLength)
{
	int i = 0;
	for (; i < nLength - 1; ++i)
	{
		printf("%d, ", pData[i]);
	}
	printf("%d\n", pData[i]);
}