#include <stdio.h>

/*
 * 取名原因: 因为是按照堆结构来设计的算法，所以称作堆排序。
 * 平均时间复杂度: O(nlogn)。
 * 平均空间复杂度: O(1)。
 * 具有不稳定性。
 * 堆: 长度为n的序列{K1, K2, ..., Kn}如果满足以下条件，就叫做堆；
 *     当1 <= i <= n是，Ki >= K(i*2) 且 Ki >= K(i*2+1)，这是大根堆，换成<=就是小根堆，
       Ki相当于完全二叉树中的非叶子结点，k(i*2)相当于左孩子，k(i*2+1)相当于右孩子，
 *     即：若孩子结点存在，则父亲结点的值要大于或等于左、右孩子的值。
 * 堆的高度: O(logn)。
 */

/*
 * 堆排序的特点: 
 * 堆排序的最坏时间复杂度为O(nlogn)，堆序的平均性能较接近于最坏性能。
 * 堆排序不适宜于记录数较少的文件，因为构造初始堆所需的比较次数较多。
 */

/* 程序输出如下:
[********** Before HeapSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After HeapSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 堆排序。
 *       首先把[0, nLength - 1]间的数据构造成堆；
 *       然后经过nLength - 1趟排序，最终使[0, nLength - 1]间的数据有序；
 *       每一趟的排序是这样的，先把[0, i]堆中的pData[0]和pData[i]进行交换，
 *       这样i位置的数据在[0, i]范围的数据中就是最大的了，因为交换前是大根堆，
 *       这时由于pData[0]的值的变化，现在可能不是大根堆了，
 *       所有需要为pData[0]在[0, i - 1]中找位置，使[0, i - 1]间的数据还是大根堆。
 * 名称: HeapSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 返回值: void。
 */
void HeapSort(int* pData, int nLength);

/*
 * 功能: 堆调整。
 *       为pData[nPos]值在[0, nLength - 1]中找位置。
 * 名称: HeapAdjust。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，调整的数据的长度。
 * 返回值: void。
 */
void HeapAdjust(int* pData, int nPos, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before HeapSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	HeapSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After HeapSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void HeapSort(int* pData, int nLength)
{
	int nTemp = 0;
	int i = nLength / 2 - 1;

	// 该for循环结果使[0, nLength-1]中的数据成为了堆。
	for (; i >= 0; --i)
	{
		// 为pData[i]值找位置。
		HeapAdjust(pData, i, nLength);
	}

	// 每趟循环把[0, i]中的最大值pData[0]和末尾的pData[i]值进行交换。
	for (i = nLength - 1; i > 0; --i)
	{
		// 交换pData[0]和pData[i]的值
		nTemp = pData[i];
		pData[i] = pData[0];
		pData[0] = nTemp;

		// 由于pData[0]值改变了，所以需要调整，使[0, i-1]中的数据成为堆
		HeapAdjust(pData, 0, i);
	}
}

void HeapAdjust(int* pData, int nPos, int nLength)
{
	int nTemp = pData[nPos];
	int nChild = 0;

	// 为pData[nPos]值找位置i。
	// 该位置必须满足以下三个条件中的一个:
	// (1) i * 2 >= nLength，即i是叶子结点；
	// (2) i * 2 < nLength 且 i * 2 + 1 >= nLength 且 pData[i] >= pData[i * 2]，即i只有左孩子结点；
	// (3) i * 2 + 1 < nLength 且 pData[i] >= pData[i * 2] 且 pData[i] >= pData[i * 2 + 1]，即i有左、右孩子结点。
	for (; nPos * 2 + 1 < nLength; nPos = nChild)
	{
		// 左孩子
		nChild = nPos * 2 + 1;
		if (nChild + 1 < nLength)
		{
			if (pData[nChild] < pData[nChild + 1])
			{
				// 右孩子
				++nChild;
			}
		}
		if (nTemp < pData[nChild])
		{
			pData[nPos] = pData[nChild];
			pData[nChild] = nTemp;
		}
		else
		{
			break;
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