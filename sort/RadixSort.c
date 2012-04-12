#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * 取名原因: 它是透过键值的部份资讯，将要排序的元素分配至某些“桶”中以达到排序的目的，所以称作基数排序。
 * 平均时间复杂度: O(d(n+r))，d是位数(决定排序趟数)，r是基数，n是待排数据的个数。
 * 平均空间复杂度: O(r+n)。
 * 具有稳定性。
 * 基数排序属于分配式排序(distribution sort)。
 * 在某些时候，基数排序的效率高于其它的比较性排序。
 */

/*
 * 基数排序的关键点：怎样得到待排数据中某一位的数值。
 * 该程序使用了除法和取余操作得到了待排数据中某一位的数值。
 *
 * 该程序是按个位、十位、百位等的顺序来排序的，称作LSD(Least significant digital)最低位优先方法；
 * 也可以按百位、十位、个位等的顺序来排序，称作MSD(Most significant digital)最高位优先方法。
 */

/* 程序输出如下:
[********** Before RadixSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After RadixSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 基数排序。
 *       先根据基数nRadix得到待排序序列的最大的位数nMaxDigit，即排序的趟数；
 *       然后进行nMaxDigit趟排序，每一趟所做的事如下
 *       (1) 从左向右遍历pData中的数据，把每个数据放入对应的桶中，总共有nMaxDigit个桶，桶的编号范围是[0, nMaxDigit-1]，
 *           把数据放入哪个桶中取决于当前排序是按哪一位排序，例如按百位排序的时候，如果pData[i]数据的百位是j，
             那么，就把该数据放入编号为j的桶中；
 *       (2) 把所有桶中的数据依次复制到pData中；
 *       (3) 改变排序的位。
 *       对于该程序，第1次排序是按个位排，第2次排序的位是按十位排，第3次排序的位按百位排，如此类推。
 * 名称: RadixSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 参数: int nRadix，基数，在该程序中指进制(例如十进制、十六进制等)。
 * 返回值: void。
 */
void RadixSort(int* pData, int nLength, int nRadix);

/*
 * 功能: 得到pData中位数最多的数据的位数值。
 * 名称: GetMaxDigit。
 * 参数: const int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 参数: int nRadix，基数，在该程序中指进制(例如十进制、十六进制等)。
 * 返回值: void。
 */
int GetMaxDigit(const int* pData, int nLength, int nRadix);

/*
 * 功能: 把ppRadixData中的数据依次复制到pData中。
 * 名称: CopyData。
 * 参数: int* pData，指向一个整数数组。
 * 参数: const int** ppRadixData，指向一个二维整数数组。
 * 参数: const int* pRadixDataCount，指向一个整数数组，pRadixDataCount[i]值记录ppRadixData[i]指向的数据的个数。
 * 参数: int nRadixDataCountLength，整数数组pRadixDataCount的长度。
 * 返回值: void。
 */
void CopyData(int* pData, const int** ppRadixData, const int* pRadixDataCount, int nRadixDataCountLength);

void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before RadixSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	RadixSort(arrData, sizeof(arrData) / sizeof(int), 10);

	printf("[********** After RadixSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void RadixSort(int* pData, int nLength, int nRadix)
{
	int i = 0;
	int j = 0;
	int nTempRadix = 1;
	int nMaxDigit = 0;
	int nTemp = 0;
	int nTempIndex = 0;
	int** ppRadixData = NULL;
	int* pRadixDataCount = NULL;

	ppRadixData = (int**)malloc(sizeof(int*) * nRadix);
	memset(ppRadixData, 0, sizeof(int) * nRadix);
	for (i = 0; i < nRadix; ++i)
	{
		ppRadixData[i] = (int*)malloc(sizeof(int) * nLength);
		memset(ppRadixData[i], 0, sizeof(int) * nLength);
	}
	pRadixDataCount = (int*)malloc(sizeof(int) * nRadix);
	memset(pRadixDataCount, 0, sizeof(int) * nRadix);

	nMaxDigit = GetMaxDigit(pData, nLength, nRadix);
	
	for (i = 0; i < nMaxDigit; ++i)
	{
		for (j = 0; j < nLength; ++j)
		{
			// 把pData[j]放入[0, nRadix - 1]范围中。
			nTemp = (pData[j] / nTempRadix) % nRadix;
			nTempIndex = pRadixDataCount[nTemp];
			ppRadixData[nTemp][nTempIndex] = pData[j];
			pRadixDataCount[nTemp] += 1;
		}

		// 把ppRadixData中的数据依次复制到pData中。
		CopyData(pData, ppRadixData, pRadixDataCount, nRadix);
		// 把pRadixDataCount中的数据清零
		memset(pRadixDataCount, 0, sizeof(int) * nRadix);

		nTempRadix *= nRadix;
	}

	for (i = 0; i < nRadix; ++i)
	{
		free(ppRadixData[i]);
		ppRadixData[i] = NULL;
	}
	free(ppRadixData);
	ppRadixData = NULL;
}

int GetMaxDigit(const int* pData, int nLength, int nRadix)
{
	// nDigit: pData中位数最多的数据的位数值
	int nDigit = 0;
	// nMaxData: pData指向的数据中绝对值最大的数
	int nMaxData = 0;
	int nTempData = 0;
	int i = 1;
	
	if (nLength < 1)
	{
		return -1;
	}

	// 得到pData指向的数据中绝对值最大的数
	nMaxData = pData[0];
	if (nMaxData < 0)
	{
		nMaxData = -nMaxData;
	}
	for (; i < nLength; ++i)
	{
		nTempData = pData[i];
		if (nTempData < 0)
		{
			nTempData = -nTempData;
		}
		if (nMaxData < nTempData)
		{
			nMaxData = nTempData;
		}
	}

	while (nMaxData > 0)
	{
		++nDigit;
		nMaxData /= nRadix;
	}

	return nDigit;
}

void CopyData(int* pData, const int** ppRadixData, const int* pRadixDataCount, int nRadixDataCountLength)
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (; i < nRadixDataCountLength; ++i)
	{
		for (j = 0; j < pRadixDataCount[i]; ++j)
		{
			pData[k] = ppRadixData[i][j];
			++k;
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