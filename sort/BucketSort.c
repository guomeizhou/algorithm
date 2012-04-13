#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * 定义: n个待排序序列元素值都处在[0, 1)区间中，
 *       将区间[0, 1)划分为m个大小相等的子区间(桶)，每个桶大小是1/m，
 *       即{[0, 1/m), [1/m, 2/m), [2/m, 3/m), ..., [k/m, (k+1)/m), ...}, 
 *       将n个待排序序列元素分配到这些桶中，然后对每个桶中的元素进行排序，
 *       最后按顺序依次连接每个桶中的数据，连接后的数据序列是有序的；
 *       由于使用到了桶，所以称作桶排序。
 * 平均时间复杂度: O(n+n*(logn-logm))，n是待排数据的个数，m是桶的个数。
 * 平均空间复杂度: O(n+m)。
 * 具有稳定性。
 * 对于同样的n，桶的个数m越多，其效率越高，最好的时间复杂度可以达到O(n)，
 * 当然，如果n和m非常大，空间代价无疑是昂贵的。
 */

/*
 * 桶排序的思想: 就是把区间[0, 1)划分成n个相同大小的桶，然后将n个输入数分布到各个桶中去，
 *               然后对各个桶中的数进行排序，最后按次序把各桶中的元素列出来即可。
 */

/*
 * 桶排序的关键点：怎样划分桶以及有多少个桶。
 * 该程序是按照待排序列中最长序列的位数来划分桶的，有多少位就有多少个桶。
 */

/* 程序输出如下:
[********** Before BucketSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After BucketSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 桶排序。
 *       先根据基数nRadix得到待排序序列的最大的位数nMaxDigit，即排序的趟数；
 *       然后进行nMaxDigit趟排序，每一趟所做的事如下
 *       (1) 从左向右遍历pData中的数据，把每个数据放入对应的桶中，总共有nMaxDigit个桶，桶的编号范围是[0, nMaxDigit-1]，
 *           把数据放入哪个桶中取决于当前排序是按哪一位排序，例如按百位排序的时候，如果pData[i]数据的百位是j，
             那么，就把该数据放入编号为j的桶中；
 *       (2) 把所有桶中的数据依次复制到pData中；
 *       (3) 改变排序的位。
 *       对于该程序，第1次排序是按个位排，第2次排序的位是按十位排，第3次排序的位按百位排，如此类推。
 * 名称: BucketSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 参数: int nRadix，基数，在该程序中指进制(例如十进制、十六进制等)。
 * 返回值: void。
 */
void BucketSort(int* pData, int nLength, int nRadix);

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

	printf("[********** Before BucketSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	BucketSort(arrData, sizeof(arrData) / sizeof(int), 10);

	printf("[********** After BucketSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void BucketSort(int* pData, int nLength, int nRadix)
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