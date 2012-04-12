#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * 取名原因: 将两个(或两个以上)有序序列合并成一个新的有序序列，即把待排序序列分为若干个子序列，
 *           每个子序列是有序的，然后再把有序子序列合并为整体有序序列，所以称作归并排序。
 * 平均时间复杂度: O(nlogn)。
 * 平均空间复杂度: O(n)。
 * 具有稳定性。
 * 归并排序是分治法(Divide and Conquer)的一个非常典型的应用。
 */

/*
 * 归并排序的关键点: 归并操作对临时空间的开销。
 * 该程序在每次进行归并操作时都开辟了新空间，这样开辟和释放太频繁，
 * 会造成大量的内存碎片，同时，开辟堆内存较栈内存而言速度慢。
 * 其它方法: 在排序前就开辟一块和待排序序列一样大小的新空间，每次进行归并操作都使用这块新空间。
 */

/* 程序输出如下:
[********** Before NoRecursionMergeSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After NoRecursionMergeSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 归并排序(非递归)。
 *       该算法采用自底向上，第1趟排序的单元是2^0个，第2趟排序的单元是2^1个，第n趟排序的单元是2^(n-1)个。
 * 名称: NoRecursionMergeSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 返回值: void。
 */
void NoRecursionMergeSort(int* pData, int nLength);

/*
 * 功能: 一趟归并排序。
 * 名称: MergePass。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nUnit，归并操作的单元长度。
 * 参数: int nLength，该整数数组的长度。
 * 返回值: void。
 */
void MergePass(int* pData, int nUnit, int nLength);

/*
 * 功能: 归并操作。
 *       对有序的[nLeft, nLeft + nUnit - 1]范围的数据和有序的[nLeft + nUnit, nRight]范围的数据进行归并操作。
 * 名称: Merge。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLeft，待排序的数组的开始下标位置。
 * 参数: int nRight，待排序的数组的结束下标位置。
 * 参数: int nUnit，归并操作的单元长度。
 * 返回值: void。
 */
void Merge(int* pData, int nLeft, int nRight, int nUnit);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before NoRecursionMergeSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	NoRecursionMergeSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After NoRecursionMergeSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void NoRecursionMergeSort(int* pData, int nLength)
{
	// i: 用来控制归并排序的趟数，需要进行logn趟排序。
	int i = 1;
	// 第1趟排序的单元是2^0个，第2趟排序的单元是2^1个，第n趟排序的单元是2^(n-1)个。
    for (; i < nLength; i *= 2)
	{
		// 做一趟归并排序。
		MergePass(pData, i, nLength);
	}
}

void MergePass(int* pData, int nUnit, int nLength)
{
	int nLeft = 0;
	int nRight = 0;
	for (; nLeft + nUnit < nLength; nLeft = nRight + 1)
	{
		// 每次循环向右增加nUnit*2长度。
		nRight = nLeft + nUnit * 2 - 1;
		if (nRight >= nLength)
		{
			nRight = nLength - 1;
		}
		Merge(pData, nLeft, nRight, nUnit);
	}
}

void Merge(int* pData, int nLeft, int nRight, int nUnit)
{
	// nMiddle: 左范围[nLeft, nMiddle]末尾的下标值
	int nMiddle = nLeft + nUnit - 1;
	// i: 用来控制遍历[nLeft, nMiddle]范围数据的次数。
	int i = nLeft;
	// j: 用来控制遍历[nMiddle + 1, nRight]范围数据的次数。
	int j = nMiddle + 1;
	// k: 用来控制复制数据到pTempData中的位置。
	int k = 0;
	// nLength: 待归并的序列的长度。
	int nLength = nRight - nLeft + 1;
	// pTempData: 临时数据块，用来存放归并后的有序序列。
	int* pTempData = (int*)malloc(sizeof(int) * nLength);
	memset(pTempData, 0, sizeof(int) * nLength);

	// 把有序的[nLeft, nMiddle]范围的数据和有序的[nMiddle + 1, nRight]范围的数据归并到pTempData中。
	while (i <= nMiddle && j <= nRight)
	{
		if (pData[i] > pData[j])
		{
			pTempData[k++] = pData[j++];
		}
		else
		{
			pTempData[k++] = pData[i++];
		}
	}
	while (i <= nMiddle)
	{
		pTempData[k++] = pData[i++];
	}
	while (j <= nRight)
	{
		pTempData[k++] = pData[j++];
	}
	
	// 把pTempData中的有序序列依次复制到pData的[nLeft, nRight]范围中。
	for (i = nLeft; i <= nRight; ++i)
	{
		pData[i] = pTempData[i - nLeft];
	}

	free(pTempData);
	pTempData = NULL;
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