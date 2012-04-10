#include <stdio.h>

/*
 * 取名原因: 由于在排序过程中总是小数往前放，大数往后放，相当于气泡往上升，所以称作冒泡排序。
 * 平均时间复杂度: O(n^2)。
 * 空间复杂度: O(1)。
 * 具有稳定性。
 * 编程复杂度很低，很容易写出代码。
 */

/* 时间复杂度分析
 * 总的比较次数: [n-1, n*(n-1)/2]
 * 总的交换次数: [0, n*(n-1)/2]
 *
 * 最好情况: 已经有序，时间复杂度是O(n)，总的比较次数是n-1，总的交换次数是0；
 * 最坏情况: 逆序，时间复杂度是O(n^2)，总的比较次数是(n-1)+(n-2)+...+1=n*(n-1)/2，总的交换次数是(n-1)+(n-2)+...+1=n*(n-1)/2；
 */

/* 程序输出如下:
[********** Before BubbleSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After BubbleSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 冒泡排序。
 *       依次比较相邻的两个数，将小数放在前面，大数放在后面；
 *       需要排序多趟(nLength-1趟)，每一趟排序的结果是最大的数被放在了最后。
 * 名称: BubbleSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 返回值: void。
 */
void BubbleSort(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before BubbleSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	BubbleSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After BubbleSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void BubbleSort(int* pData, int nLength)
{
	// i: 用来控制排序的趟数。
	int i = 1;
	// j: 用来控制在一趟中相邻的数比较的次数。
	int j = 0;
	// nTemp: 临时变量，用作交换的中间变量。
	int nTemp = 0;
	// nFlag: 用来标记整数数组是否已经全部有序；为0表示全部有序，为1表示部分有序。
	int nFlag = 0;
	for (; i < nLength; ++i)
	{
		nFlag = 0;
		for (j = 0; j < nLength - i; ++j)
		{
			if (pData[j] > pData[j + 1])
			{
				nTemp = pData[j];
				pData[j] = pData[j + 1];
				pData[j + 1] = nTemp;
				nFlag = 1;
			}
		}
		if (nFlag == 0)
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