#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * 定义: 计算出待排序序列中每个数据元素在最终有序序列中的位置，然后把待排序序列中每个数据元素放到最终位置，由这些元素组成的序列是有序的；
 *       计算数据元素pData[i]的最终位置的方法是统计待排序序列中比pData[i]小的数据元素的个数，如果有j个比它小，
 *       那么就把pData[i]放到有序序列的j+1的位置上；对于相同的数据元素值，我们会先存放待排序序列右边的数据元素，后存放左边的数据元素；
 *       由于使用了统计个数的方法，所以称作计数排序。
 * 平均时间复杂度: O(n)，n是待排数据的个数。
 * 具有稳定性。
 */

/*
 * 计数排序的关键点：怎样计算出待排序序列中每个数据元素在最终有序序列中的位置。
 * 由于计数排序是非比较类算法，且时间复杂度要求是线性的，
 * 所以，不能通过比较待排序序列中的值来获得每个数据元素在最终有序序列中的位置。
 */

/* 程序输出如下:
[********** Before CountingSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After CountingSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99

[********** Before CountingSortEx **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After CountingSortEx **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 计数排序。
 *       遍历待排序列pData，找出最小值nMin和最大值nMax，
 *       新开辟(nMax - nMin + 1)大小的内存空间pCounting，pCounting[i]对应nMin+i，
 *       遍历待排序列pData，在pCounting中对应的位置进行计数操作，例如对于pData[i]就把pCounting[pData[i] - nMin]加1，
 *       遍历pCounting中的数据，把pCounting[i]的值增加pCounting[i - 1]，
 *       新开辟nLength大小的内存空间pTempData，
 *       遍历待排序列pData，把pData[i]数据放到pTempData[k]中，结果是pTempData中的数据是有序的，
 *       把pTempData中的数据依次复制到pData中。 
 * 名称: CountingSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 返回值: void。
 */
void CountingSort(int* pData, int nLength);

/*
 * 功能: 计数排序(实现方案比CountingSort更好)。
 *       遍历待排序列pData，找出最小值nMin和最大值nMax，
 *       新开辟(nMax - nMin + 1)大小的内存空间pCounting，pCounting[i]对应nMin+i，
 *       遍历待排序列pData，在pCounting中对应的位置进行计数操作，例如对于pData[i]就把pCounting[pData[i] - nMin]加1，
 *       遍历pCounting中的数据，如果pCounting[i]大于0，就把(nMin + i)值放到pData中相应的位置。 
 * 名称: CountingSortEx。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 返回值: void。
 */
void CountingSortEx(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};
	int arrDataEx[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before CountingSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));
	CountingSort(arrData, sizeof(arrData) / sizeof(int));
	printf("[********** After CountingSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	printf("\n[********** Before CountingSortEx **********]\n");
	Output(arrDataEx, sizeof(arrDataEx) / sizeof(int));
	CountingSortEx(arrDataEx, sizeof(arrDataEx) / sizeof(int));
	printf("[********** After CountingSortEx **********]\n");
	Output(arrDataEx, sizeof(arrDataEx) / sizeof(int));

	return 0;
}

void CountingSort(int* pData, int nLength)
{
	int i = 0;
	int j = 0;
	// nMin: pData序列中元素值最小的值。
	int nMin = pData[0];
	// nMax: pData序列中元素值最大的值。
	int nMax = nMin;
	// nCount: 计数数组的大小。
	int nCount = 0;
	// pCounting: 计数数组指针。
	int* pCounting = NULL;
	// pTempData: 临时数组，用来存放排序后的结果。
	int* pTempData = NULL;
	int nTempPos = 0;

	for (i = 1; i < nLength; ++i)
	{
		if (pData[i] < nMin)
		{
			nMin = pData[i];
		}
		else if (pData[i] > nMax)
		{
			nMax = pData[i];
		}
	}
	nCount = nMax - nMin + 1;
	pCounting = (int*)malloc(sizeof(int) * nCount);
	memset(pCounting, 0, sizeof(int) * nCount);

	for (i = 0; i < nLength; ++i)
	{
		++pCounting[pData[i] - nMin];
	}

	for (i = 1; i < nCount; ++i)
	{
		pCounting[i] += pCounting[i - 1];
	}

	pTempData = (int*)malloc(sizeof(int) * nLength);
	memset(pTempData, 0, sizeof(int) * nLength);
	for (i = nLength - 1; i >= 0; --i)
	{
		nTempPos = pCounting[pData[i] - nMin];
		pTempData[nTempPos - 1] = pData[i];
		--pCounting[pData[i] - nMin];
	}

	for (i = 0; i < nLength; ++i)
	{
		pData[i] = pTempData[i];
	}

	free(pCounting);
	pCounting = NULL;
	free(pTempData);
	pTempData = NULL;
}

void CountingSortEx(int* pData, int nLength)
{
	int i = 0;
	int j = 0;
	// nMin: pData序列中元素值最小的值。
	int nMin = pData[0];
	// nMax: pData序列中元素值最大的值。
	int nMax = nMin;
	// nCount: 计数数组的大小。
	int nCount = 0;
	// pCounting: 计数数组指针。
	int* pCounting = NULL;

	for (i = 1; i < nLength; ++i)
	{
		if (pData[i] < nMin)
		{
			nMin = pData[i];
		}
		else if (pData[i] > nMax)
		{
			nMax = pData[i];
		}
	}
	nCount = nMax - nMin + 1;
	pCounting = (int*)malloc(sizeof(int) * nCount);
	memset(pCounting, 0, sizeof(int) * nCount);

	for (i = 0; i < nLength; ++i)
	{
		++pCounting[pData[i] - nMin];
	}

	for (i = 0; i < nCount; ++i)
	{
		while (pCounting[i] > 0)
		{
			pData[j++] = nMin + i;
			--pCounting[i];
		}
	}

	free(pCounting);
	pCounting = NULL;
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