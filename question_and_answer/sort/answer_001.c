#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>

#define MIN_NUM 100
#define MAN_NUM 900
#define DATA_LENGTH 5000000

/*
 * 解法: 使用桶排序。
         创建(MAN_NUM - MIN_NUM + 1)个桶，桶编号的从MIN_NUM到MAN_NUM，将每个考生的分数score放入桶score中，
 *       然后根据桶号的大小依次将桶中分数输出，即可以得到一个有序的序列。
 */

typedef struct DataNode
{
	int nData;
	struct DataNode* pNext;
} DataNode;

/*
 * 功能: 初始化nLength个数据。
 * 名称: InitData。
 * 参数: int** ppData，指向一个整数数组的指针。
 * 参数: int nLength，该整数数组的长度。
 * 参数: int nMin。
 * 参数: int nMax。
 * 返回值: void。
 */
void InitData(int** ppData, int nLength, int nMin, int nMax);

/*
 * 功能: 释放*ppData指向的空间。
 * 名称: DestoryData。
 * 参数: int** ppData，指向一个整数数组的指针。
 * 返回值: void。
 */
void DestoryData(int** ppData);

/*
 * 功能: 桶排序。
 * 名称: BucketSort。
 * 参数: int* pData，指向一个整数数组。
 * 参数: int nLength，该整数数组的长度。
 * 参数: int nMin。
 * 参数: int nMax。
 * 返回值: void。
 */
void BucketSort(int* pData, int nLength, int nMin, int nMax);
void Output(const int* pData, int nLength);

int main()
{
	int* pData = NULL;
	int nLength = DATA_LENGTH;
	int nMin = MIN_NUM;
	int nMax = MAN_NUM;

	InitData(&pData, nLength, nMin, nMax);

	Output(pData, nLength);
	BucketSort(pData, nLength, nMin, nMax);
	Output(pData, nLength);

	DestoryData(&pData);

	return 0;
}

void InitData(int** ppData, int nLength, int nMin, int nMax)
{
	int i = 0;
	int nData = 0;
	int nRange = nMax - nMin + 1;

	*ppData = (int*)malloc(sizeof(int) * nLength);

	srand((unsigned int)time(NULL));
	for (; i < nLength; ++i)
	{
		// rand()返回值的范围是[0x0, 0x7fff]，Ox7fff就是32767。
		nData = rand() % nRange;
		nData += nMin;
		(*ppData)[i] = nData;
	}
}

void DestoryData(int** ppData)
{
	if (ppData != NULL && *ppData != NULL)
	{
		free(*ppData);
		*ppData = NULL;
	}
}

void BucketSort(int* pData, int nLength, int nMin, int nMax)
{
	int i = 0;
	int j = 0;
	// nBucketNum: 桶的数量。
	int nBucketNum = nMax - nMin + 1;
	DataNode* pDataNode = NULL;
	DataNode* pNextDataNode = NULL;
	DataNode* pPreviousDataNode = NULL;
	// ppBucket: 指向所有的桶。
	DataNode** ppBucket = NULL;

	ppBucket = (DataNode**)malloc(sizeof(DataNode*) * nBucketNum);
	for (i = 0; i < nBucketNum; ++i)
	{
		ppBucket[i] = NULL;
	}

	// 把pData[i]放到桶ppBucket中。
	for (i = 0; i < nLength; ++i)
	{
		pDataNode = (DataNode*)malloc(sizeof(DataNode));
		pDataNode->nData = pData[i];
		pDataNode->pNext = NULL;

		pNextDataNode = ppBucket[pData[i] - nMin];
		if (pNextDataNode == NULL)
		{
			ppBucket[pData[i] - nMin] = pDataNode;
		}
		else
		{
			do
			{
				if (pDataNode->nData >= pNextDataNode->nData)
				{
					pPreviousDataNode = pNextDataNode;
					pNextDataNode = pNextDataNode->pNext;
				}
				else
				{
					pPreviousDataNode = pNextDataNode;
					break;
				}
			} while (pNextDataNode != NULL);
			pDataNode->pNext = pPreviousDataNode->pNext;
			pPreviousDataNode->pNext = pDataNode;
		}
	}

	// 把桶ppBucket中的有序序列复制到pData中。
	for (i = 0; i < nBucketNum; ++i)
	{
		pNextDataNode = ppBucket[i];
		while (pNextDataNode != NULL)
		{
			pData[j++] = pNextDataNode->nData;
			pNextDataNode = pNextDataNode->pNext;
		}
	}

	// 销毁堆内存。
	for (i = 0; i < nBucketNum; ++i)
	{
		pNextDataNode = ppBucket[i];
		while (pNextDataNode != NULL)
		{
			pDataNode = pNextDataNode;
			pNextDataNode = pNextDataNode->pNext;
			free(pDataNode);
			pDataNode = NULL;
		}
		ppBucket[i] = NULL;
	}
	free(ppBucket);
	ppBucket = NULL;
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