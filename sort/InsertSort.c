#include <stdio.h>

/*
 * 取名原因: 将一个数据插入到已经排好序的有序数据中，从而得到一个新的、个数加一的有序数据，所以称作插入排序。
 * 平均时间复杂度: O(n^2)。
 * 空间复杂度: O(1)。
 * 具有稳定性。
 * 编程复杂度很低，很容易写出代码。
 * 算法适用于少量数据的排序，因为存在大量的数据的移动(交换)。
 */

/* 时间复杂度分析
 * 总的比较次数: [3*(n-1), (n+1)*(n-1)]
 * 总的交换次数: [0, (n-1)*(n+2)/2]
 * 
 * 最好情况: 已经有序，时间复杂度是O(n)，总的比较次数是3*(n-1)，总的交换次数是0；
 * 最坏情况: 逆序，时间复杂度是O(n^2)，总的比较次数是(n+1)*(n-1)，总的交换次数是(n-1)*(n+2)/2；
 */

/* 程序输出如下:
[********** Before InsertSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After InsertSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 插入排序。
 *       将一个数据插入到已经排好序的有序数据中，从而得到一个新的、个数加一的有序数据；
 *       每一趟把有序数据的下一个元素插入到该有序数据中，该元素和有序数据中按从右向左的顺序得到的元素依次进行比较；
 *       需要排序多趟(nLength-1趟)，每一趟排序的结果是前面的排序数据个数加一且有序。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 返回值: void。
 */
void InsertSort(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before InsertSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	InsertSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After InsertSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void InsertSort(int* pData, int nLength)
{
	// i: 用来控制排序的趟数。
	int i = 1;
	// j: 用来控制在一趟排序中，当前要插入的数和其前面所有的数的比较次数。
	int j = 0;
	// 临时变量，用来保存当前要插入的数。
	int nTempValue = 0;
	for (; i < nLength; ++i)
	{
		nTempValue = pData[i];
		j = i - 1;
		while (j >= 0 && nTempValue < pData[j])
		{
			pData[j + 1] = pData[j];
			--j;
		}
		if (j + 1 != i)
		{
			pData[j + 1] = nTempValue;
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