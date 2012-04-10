#include <stdio.h>

/*
 * 取名原因: 由于在排序过程中总是总是从未有序的数列中选择出最小的数放在最前面，所以称作选择排序。
 * 平均时间复杂度: O(n^2)。
 * 空间复杂度: O(1)。
 * 具有不稳定性。
 * 编程复杂度很低，很容易写出代码。
 */

/* 时间复杂度分析
 * 总的比较次数: (n-1)+(n-2)+...+1=n*(n-1)/2
 * 总的交换次数: [0, n-1]
 *
 * 最好情况: 已经有序，时间复杂度是O(n^2)，总的比较次数是n*(n-1)/2，总的交换次数是0；
 * 最坏情况: 逆序，时间复杂度是O(n^2)，总的比较次数是n*(n-1)/2，总的交换次数是n-1；
 */

/* 程序输出如下:
[********** Before SelectSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After SelectSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 选择排序。
 *       每一趟从待排序的数据元素中选出最小的一个元素，顺序放在已排好序的数列的最后，直到全部待排序的数据元素排完；
 *       需要排序多趟(nLength-1趟)，每一趟排序的结果是最小的数被放在最前面。
 * 名称: SelectSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 返回值: void。
 */
void SelectSort(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before SelectSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	SelectSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After SelectSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void SelectSort(int* pData, int nLength)
{
	// i: 用来控制排序的趟数。
	int i = 0;
	// j: 用来控制在未排序整数数组的一趟排序中，其后的数和第1个数比较的次数。
	int j = 0;
	// nTempPos: 记录在未排序整数数组中值最小的元素的下标位置。
	int nTempPos = 0;
	// nTemp: 临时变量，用作交换的中间变量。
	int nTempValue = 0;
	for (i = 0; i < nLength - 1; ++i)
	{
		nTempPos = i;
		for (j = i + 1; j < nLength; ++j)
		{
			if (pData[j] < pData[nTempPos])
			{
				nTempPos = j;
			}
		}
		if (nTempPos != i)
		{
			nTempValue = pData[i];
			pData[i] = pData[nTempPos];
			pData[nTempPos] = nTempValue;
		}
	}
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