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
[********** Before MergeSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After MergeSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 归并排序。
 *       该算法需要递归地进行，每一次递归的操作如下
 *       (1) 算出nLeft和nRight的平均值，
 *       (2) 分别对[nLeft, nMiddle]范围的数据和[nMiddle + 1, nRight]范围的数据进行归并排序，
 *       (3) 对有序的[nLeft, nMiddle]范围的数据和有序的[nMiddle + 1, nRight]范围的数据进行归并操作。
 * 名称: MergeSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLeft，待排序的数组的开始下标位置。
 * 参数: int nRight，待排序的数组的结束下标位置。
 * 返回值: void。
 */
void MergeSort(int* pData, int nLeft, int nRight);

/*
 * 功能: 归并操作。
 *       对有序的[nLeft, nMiddle]范围的数据和有序的[nMiddle + 1, nRight]范围的数据进行归并操作。
 * 名称: Merge。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLeft，待排序的数组的开始下标位置。
 * 参数: int nMiddle，待排序的数组的中间下标位置。
 * 参数: int nRight，待排序的数组的结束下标位置。
 * 返回值: void。
 */
void Merge(int* pData, int nLeft, int nMiddle, int nRight);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before MergeSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	MergeSort(arrData, 0, sizeof(arrData) / sizeof(int) - 1);

	printf("[********** After MergeSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void MergeSort(int* pData, int nLeft, int nRight)
{
	if (nLeft < nRight)
	{
		// 将[nLeft, nRight]范围平分成[nLeft, nMiddle]和[nMiddle + 1, nRight]两个范围
		int nMiddle = (nLeft + nRight) / 2;
		// 对[nLeft, nMiddle]范围的数据进行归并排序
		MergeSort(pData, nLeft, nMiddle);
		// 对[nMiddle + 1, nRight]范围的数据进行归并排序
		MergeSort(pData, nMiddle + 1, nRight);
		// 对有序的[nLeft, nMiddle]范围的数据和有序的[nMiddle + 1, nRight]范围的数据进行归并操作
		Merge(pData, nLeft, nMiddle, nRight);
	}
}

void Merge(int* pData, int nLeft, int nMiddle, int nRight)
{
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