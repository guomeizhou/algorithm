#include <stdio.h>
#include <malloc.h>
#include <assert.h>

/*
 * 由来: 快速排序是对冒泡排序的一种改进。
 * 平均时间复杂度: O(nlogn)。
 * 具有不稳定性。
 */

/* 程序输出如下:
[********** Before NoRecursionQuickSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After NoRecursionQuickSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef struct StackData
{
    int nLeft;
    int nRight;
} StackData;

typedef struct StackNode
{
    StackData data;
    struct StackNode* pNext;
} StackNode;

/*
 * 功能: 快速排序(非递归)。
 *       用栈来实现快速排序，每趟排序中都把待排序列中的第1个值作为中值。
 * 名称: NoRecursionQuickSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，数组的长度。
 * 返回值: void。
 */
void NoRecursionQuickSort(int* pData, int nLength);

/*
 * 功能: 入栈。
 * 名称: StackPush。
 * 参数: StackNode** ppStackTop，栈顶指针的地址。
 * 参数: const StackData* pData，入栈数据的地址。
 * 返回值: void。
 */
void StackPush(StackNode** ppStackTop, const StackData* pData);

/*
 * 功能: 出栈。
 * 名称: StackPop。
 * 参数: StackNode** ppStackTop，栈顶指针的地址。
 * 参数: StackData* pData，待排序的数组的开始下标位置。
 * 返回值: BOOL，返回TRUE表示成功，返回FALSE表示失败。
 */
BOOL StackPop(StackNode** ppStackTop, StackData* pData);

/*
 * 功能: 判断是否栈为空。
 * 名称: IsStackEmpty。
 * 参数: const StackNode* pStackTop，栈顶指针。
 * 返回值: BOOL，返回TRUE表示成功，返回FALSE表示失败。
 */
BOOL IsStackEmpty(const StackNode* pStackTop);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before NoRecursionQuickSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	NoRecursionQuickSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After NoRecursionQuickSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void NoRecursionQuickSort(int* pData, int nLength)
{
    int i = 0;
    int j = 0;
    int nLeft = 0;
    int nRight = 0;
    int nTemp = 0;
    int nTop = 0;
    StackNode* pStackTop = NULL;

    StackData data;
    data.nLeft = 0;
    data.nRight = nLength - 1;
    StackPush(&pStackTop, &data);

    while (!IsStackEmpty(pStackTop))
    {
        BOOL bPopSuccess = StackPop(&pStackTop, &data);
        if (!bPopSuccess)
        {
            break;
        }
        nLeft = data.nLeft;
        nRight = data.nRight;

        i = nLeft;
        j = nRight;
        if (nLeft < nRight)
        {
            // 把最左边的值作为中值。
            nTemp = pData[nLeft];
            while (i < j)
            {
                while (i < j && pData[j] > nTemp)
                {
                    --j;
                }
                if (i < j)
                {
                    pData[i] = pData[j];
                    ++i;
                }

                while (i < j && pData[i] < nTemp)
                {
                    ++i;
                }
                if (i < j)
                {
                    pData[j] = pData[i];
                    --j;
                }
                // 中值的下标位置是i；
                // 当前的结果是：
                //     [nLeft, i - 1]段的数据都小于或等于i位置的数据，i位置的数据小于或等于[i + 1, nRight]段的数据。
                pData[i] = nTemp;

                // 把[nLeft, i - 1]压入栈中，以后会取出来对该段数据进行排序
                data.nLeft = nLeft;
                data.nRight = i - 1;
                StackPush(&pStackTop, &data);

                // 把[i + 1, nRight]压入栈中，以后会取出来对该段数据进行排序
                data.nLeft = i + 1;
                data.nRight = nRight;
                StackPush(&pStackTop, &data);
            }
        }
    }

    assert(IsStackEmpty(pStackTop));
}

void StackPush(StackNode** ppStackTop, const StackData* pData)
{
    StackNode* pStackNode = (StackNode*)malloc(sizeof(StackNode));
    pStackNode->data = *pData;
    pStackNode->pNext = *ppStackTop;
    *ppStackTop = pStackNode;
}

BOOL StackPop(StackNode** ppStackTop, StackData* pData)
{
    if (ppStackTop != NULL && *ppStackTop != NULL)
    {
        StackNode* pPopStackNode = *ppStackTop;
        pData->nLeft = pPopStackNode->data.nLeft;
        pData->nRight = pPopStackNode->data.nRight;
        *ppStackTop = pPopStackNode->pNext;

		pPopStackNode->pNext = NULL;
        free(pPopStackNode);
        pPopStackNode = NULL;
        return TRUE;
    }
    return FALSE;
}

BOOL IsStackEmpty(const StackNode* pStackTop)
{
    if (pStackTop == NULL)
    {
        return TRUE;
    }
    return FALSE;
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