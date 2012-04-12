#include <stdio.h>

/*
 * 取名原因: 将整个序列分割成若干小的子序列分别进行插入排序，每一趟排序分割成的子序列的长度在逐渐减小，直到减少到1，
 *           由于D.L. Shell设计和实现了该算法，所以称作希尔排序。
 * 平均时间复杂度: O(n^1.5)。
 * 平均空间复杂度: O(1)。
 * 具有不稳定性。
 * 希尔排序属于插入类排序，又被称作缩小增量法。
 */

/*
 * 希尔排序的关键点：使用怎样的增量序列。
 * 该程序使用的是增量序列{n/(2^1), n/(2^2), n/(2^3), n/(2^k), ..., 1}。
 * 其它的增量序列{n/(3^1), n/(3^2), n/(3^3), n/(3^k), ..., 1}。
 */

/* 程序输出如下:
[********** Before ShellSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After ShellSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * 功能: 希尔排序。
 *       从右向左使用增量序列{nLength/(2^1), nLength/(2^2), nLength/(2^3), nLength/(2^k), ..., 1}中的增量值，
 *       每一个增量值就需要进行一趟排序，最后一个增量值必须是1，用它来保证最终的序列有序；
 *       在一趟排序中，会从右向左取出[nIncrement, nLength-1]中的值i，并使用插入排序把pData[i]按从右向左的顺序插入到
 *       有序序列{..., i-nIncrement*k, ..., i-nIncrement*3, i-nIncrement*2, i-nIncrement}中。
 * 名称: ShellSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 返回值: void。
 */
void ShellSort(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before ShellSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	ShellSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After ShellSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void ShellSort(int* pData, int nLength)
{
	// i: 控制每趟循环中[nIncrement, nLength-1]的次数。
	int i = 0;
	// j: 从右向左表示下列值{..., i-nIncrement*k, ..., i-nIncrement*3, i-nIncrement*2, i-nIncrement}。
	int j = 0;
	// nTemp: 临时变量，用来存放要插入的变量值pData[i]。
	int nTemp = 0;
	// nIncrement: 增量。
	int nIncrement = nLength / 2;

	// nIncrement的倒数第二个值一定是1。
	for (; nIncrement > 0; nIncrement /= 2)
	{
		for (i = nIncrement; i < nLength; ++i)
		{
			// 使用插入排序，把pData[i]按从右向左的顺序插入到
			// 有序序列{..., i-nIncrement*k, ..., i-nIncrement*3, i-nIncrement*2, i-nIncrement}中。
			if (pData[i] < pData[i - nIncrement])
			{
				nTemp = pData[i];
				j = i - nIncrement;
				do
				{
					pData[j + nIncrement] = pData[j];
					j -= nIncrement;
				} while (j >= 0 && nTemp < pData[j]);
				if (j + nIncrement != i)
				{
					pData[j + nIncrement] = nTemp;
				}
			}
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