#include <stdio.h>

/*
 * 取名原因: 将一个数据插入到已经排好序的有序数据中，从而得到一个新的、个数加一的有序数据，
 *           由于在有序数据中查找插入数据位置时使用了二分查找，所以称作二分插入排序。
 * 平均时间复杂度: O(n^2)。
 * 空间复杂度: O(1)。
 * 具有稳定性。
 * 编程复杂度很低，很容易写出代码。
 * 算法适用于少量数据的排序，因为存在大量的数据的移动(交换)。
 */

/* 时间复杂度分析
 * 总的比较次数: (n-1)*(n+8)/2
 * 总的交换次数: [0, (n+2)*(n-1)/2]
 *
 * 最好情况: 已经有序，时间复杂度是O(n^2)，总的比较次数是(n-1)*(n+8)/2，总的交换次数是0；
 * 最坏情况: 逆序，时间复杂度是O(n^2)，总的比较次数是(n-1)*(n+8)/2，总的交换次数是(n+2)*(n-1)/2；
 */

/* 程序输出如下:
[********** Before BinaryInsertSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After BinaryInsertSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 二分插入排序(折半插入排序)。
 *       将一个数据插入到已经排好序的有序数据中，从而得到一个新的、个数加一的有序数据；
 *       每一趟把有序数据的下一个元素插入到该有序数据中，该元素和有序数据中按二分查找得到的元素依次进行比较；
 *       需要排序多趟(nLength-1趟)，每一趟排序的结果是前面的排序数据个数加一且有序。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 返回值: void。
 */
void BinaryInsertSort(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before BinaryInsertSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	BinaryInsertSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After BinaryInsertSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void BinaryInsertSort(int* pData, int nLength)
{
	// i: 用来控制排序的趟数。
	int i = 1;
	// j: 用来控制在一趟排序中，新数据元素插入位置后面的有序数据的移动次数。
	int j = 0;
	// 临时变量，用来保存当前要插入的数。
	int nTempValue = 0;

	int nLeft = 0;
	int nMiddle = 0;
	int nRight = 0;

	for (; i < nLength; ++i)
	{
		nTempValue = pData[i];

		// 按二分查找
		nLeft = 0;
		nRight = i - 1;
		while (nLeft <= nRight)
		{
			nMiddle = (nLeft + nRight) / 2;
			if (pData[nMiddle] <= nTempValue)
			{
				nLeft = nMiddle + 1;
			}
			else
			{
				nRight = nMiddle - 1;
			}
		}

		// nTempValue的插入位置是nLeft
		// 注意: 此时，nLeft = nRight + 1
		for (j = i; j > nLeft; --j)
		{
			pData[j] = pData[j - 1];
		}
		if (nLeft != i)
		{
			pData[nLeft] = nTempValue;
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