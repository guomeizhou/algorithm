#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * 由来: 二路插入排序是对插入排序的一种改进，减少了数据移动的次数。
 * 平均时间复杂度: O(n^2)。
 * 具有稳定性。
 */

/*
 * 二路插入排序的关键点: 
 * (1) 新开辟了和待排序数据序列一样大小的空间；
 * (2) 把新开辟的空间用nFirst和nFinal分隔成左、中、右3部分；
 * (3) 利用取余后所得值的环的特性。
 */

/* 程序输出如下:
[********** Before TwoPathInsertSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After TwoPathInsertSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 二路插入排序。
 *       新开辟一个和pData指向空间一样大的空间pTempData，把pData指向的第1个数据放到pTempData指向的第1个数据，
 *       然后从pData的第2个数据开始，从左向右遍历pData中的数据，经过(nLength-1)趟，
 *       每趟的目的是为pData[i]在pTempData指向的空间中找位置并插入；
 *       找位置的方法是把pTempData中的空间用nFirst和nFinal分隔成3部分，
 *       nFirst用来表示有序序列第1个数据元素的位置，nFinal用来表示有序序列最后1个数据元素的位置，
 *       (1) 如果插入的数据pData[i]小于nFirst指向的数据，就把pData[i]插入到nFirst的左边，
 *       (2) 如果插入的数据pData[i]大于nFinal指向的数据，就把pData[i]插入到nFinal的右边，
 *       (3) 如果插入的数据pData[i]大于或等于nFirst指向的数据且小于或等于nFinal指向的数据，
 *           就从nFinal指向的位置开始向前移动，为pData[i]找位置并插入。
 *       结果是pTempData[nFirst%nLength]到pTempData[(nFirst+nLength-1)%nLength]间的数据是有序的，
 *       最后把该有序数据依次复制到pData指向的空间中。
 *       注意：该程序把pTempData指向的所有数据空间当作一个环来看待，比如pTempData[0]的左边的数据是pTempData[nLength-1]。
 * 名称: TwoPathInsertSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，数组的长度。
 * 返回值: void。
 */
void TwoPathInsertSort(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before TwoPathInsertSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	TwoPathInsertSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After TwoPathInsertSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void TwoPathInsertSort(int* pData, int nLength)
{
	// i: 用来控制排序的趟数，操作对象是pData。
	int i = 0;
	// j: 用来控制移动数据的次数，操作对象是pTempData。
	int j = 0;
	// nFirst: 表示有序序列第1个数据元素的位置，操作对象是pTempData。
	int nFirst = 0;
	// nFinal: 表示有序序列最后1个数据元素的位置，操作对象是pTempData。
	int nFinal = 0;
	// pTempData: 临时数据块。
	int* pTempData = (int*)malloc(sizeof(int) * nLength);
	memset(pTempData, 0, sizeof(int) * nLength);

	// pData中的第1个数据元素为pTempData中排好序的数据元素。
	pTempData[0] = pData[0];
	
	for (i = 1; i < nLength; ++i)
	{
		if (pData[i] < pTempData[nFirst])
		{
			nFirst = (nFirst - 1 + nLength) % nLength;
			pTempData[nFirst] = pData[i];
		}
		else if (pData[i] > pTempData[nFinal])
		{
			++nFinal;
			pTempData[nFinal] = pData[i];
		}
		else
		{
			j = nFinal;
			while (pData[i] < pTempData[j])
			{
				pTempData[(j + 1) % nLength] = pTempData[j];
				j = (j - 1 + nLength) % nLength;
			}
			pTempData[j + 1] = pData[i];
			// 因为插入了数据元素，所以增加1
			++nFinal;
		}
	}

	// 把[nFirst % nLength, (nFirst + nLength - 1) % nLength]间的有序数据依次复制到待排序数组中。
	for (i = 0; i < nLength; ++i)
	{
		pData[i] = pTempData[(nFirst + i) % nLength];
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