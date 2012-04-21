#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>

/*
 * 解法1: 对应函数Deal，在一个范围中随机产生一张牌，取出该张牌，然后缩小范围，如此继续下去。
 * 解法2: 对应函数DealEx，先产生54张随机牌，然后分别从2, 3, ......, 51张牌中产生牌发给3个人中的一个。
 */

/* 程序输出如下:
[********** Before Deal **********]
方块A, 方块2, 方块3, 方块4, 方块5, 方块6, 方块7, 方块8, 方块9, 方块10,
方块J, 方块Q, 方块K, 梅花A, 梅花2, 梅花3, 梅花4, 梅花5, 梅花6, 梅花7,
梅花8, 梅花9, 梅花10, 梅花J, 梅花Q, 梅花K, 红桃A, 红桃2, 红桃3, 红桃4,
红桃5, 红桃6, 红桃7, 红桃8, 红桃9, 红桃10, 红桃J, 红桃Q, 红桃K, 黑桃A,
黑桃2, 黑桃3, 黑桃4, 黑桃5, 黑桃6, 黑桃7, 黑桃8, 黑桃9, 黑桃10, 黑桃J,
黑桃Q, 黑桃K, 小王, 大王

[********** After Deal **********]
Person 1:
方块4, 黑桃3, 红桃5, 红桃J, 方块Q, 红桃7, 红桃K, 方块3, 梅花5, 黑桃9,
黑桃4, 红桃2, 黑桃5, 黑桃7, 黑桃2, 方块8, 小王
Person 2:
红桃8, 梅花4, 梅花J, 红桃3, 黑桃A, 黑桃K, 黑桃J, 梅花K, 梅花Q, 方块9,
梅花7, 黑桃10, 方块6, 方块A, 方块5, 梅花6, 梅花3
Person 3:
大王, 红桃9, 方块2, 红桃4, 红桃Q, 红桃10, 红桃6, 红桃A, 方块7, 梅花8,
梅花2, 梅花9, 方块K, 梅花10, 方块10, 黑桃6, 梅花A
Remain:
黑桃Q, 方块J, 黑桃8


[********** Before DealEx **********]
方块A, 方块2, 方块3, 方块4, 方块5, 方块6, 方块7, 方块8, 方块9, 方块10,
方块J, 方块Q, 方块K, 梅花A, 梅花2, 梅花3, 梅花4, 梅花5, 梅花6, 梅花7,
梅花8, 梅花9, 梅花10, 梅花J, 梅花Q, 梅花K, 红桃A, 红桃2, 红桃3, 红桃4,
红桃5, 红桃6, 红桃7, 红桃8, 红桃9, 红桃10, 红桃J, 红桃Q, 红桃K, 黑桃A,
黑桃2, 黑桃3, 黑桃4, 黑桃5, 黑桃6, 黑桃7, 黑桃8, 黑桃9, 黑桃10, 黑桃J,
黑桃Q, 黑桃K, 小王, 大王

[********** After DealEx **********]
Person 1:
黑桃8, 梅花3, 梅花6, 梅花A, 方块A, 方块6, 黑桃10, 梅花7, 方块9, 梅花Q,
梅花K, 黑桃J, 黑桃K, 黑桃A, 红桃3, 梅花J, 梅花4
Person 2:
方块J, 小王, 方块8, 黑桃2, 黑桃7, 方块5, 红桃2, 黑桃4, 黑桃9, 梅花5,
方块3, 红桃K, 红桃7, 方块Q, 红桃J, 红桃5, 黑桃3
Person 3:
黑桃Q, 黑桃6, 方块10, 梅花10, 方块K, 黑桃5, 梅花2, 梅花8, 方块7, 红桃A,
红桃6, 红桃10, 红桃Q, 红桃4, 方块2, 红桃9, 梅花9
Remain:
大王, 红桃8, 方块4
*/

#define POKER_NUM 54
#define REMAIN_POKER_NUM 3
#define EVERY_PERSON_POKER_NUM (POKER_NUM - REMAIN_POKER_NUM) / 3
#define PART_POKER_NUM 13
#define POKER_COLOR_NUM 4

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef enum 
{
	// 方块
	PT_DIAMONDS,
	// 梅花
	PT_CLUBS,
	// 红桃
	PT_HEARTS,
	// 黑桃
	PT_SPADES,
	// 小王
	PT_SMALLJOKER,
	// 大王
	PT_BIGJOKER
} PokerType;

typedef struct
{
	int nNum;
	PokerType pt;
} Poker;

typedef struct
{
	Poker p;
	// 标记该数的索引值是否已经随机产生过
	BOOL bFlag;
} PokerEx;

/*
 * 功能: 发牌。
         循环经过(nLength - nRemainLength)趟，每一趟的循环如下：
         随机产生一个[0, i - 1]范围内的数nPokerIndex，
		 如果nPokerIndex小于i - 1，就把pTempPoker[nPokerIndex]和pTempPoker[i - 1]交换，并把i减1；
         如果nPokerIndex等于i - 1，就把i减1。
 * 名称: Deal。
 * 参数: const Poker* pPoker，指向一个数组，该数组数据是输入数据。
 * 参数: int nLength，pPoker数组的长度。
 * 参数: Poker* pPoker1，指向存放第1个人牌的数组，该数组数据是输出数据。
 * 参数: Poker* pPoker2，指向存放第2个人牌的数组，该数组数据是输出数据。
 * 参数: Poker* pPoker3，指向存放第3个人牌的数组，该数组数据是输出数据。
 * 参数: int nEveryPersonLength，pPoker1或pPoker2或pPoker3数组的长度。
 * 参数: Poker* pPokerRemain，指向存放剩余未发牌的数组，该数组数据是输出数据。
 * 参数: int nRemainLength，pPokerRemain数组的长度。
 * 返回值: void。
 */
void Deal(const Poker* pPoker, int nLength, Poker* pPoker1, Poker* pPoker2, Poker* pPoker3, int nEveryPersonLength,
			Poker* pPokerRemain, int nRemainLength);
void OutputDealBefore(const Poker* pPoker, int nPokerNum);
void OutputDealAfter(const Poker* pPoker1, const Poker* pPoker2, const Poker* pPoker3, const Poker* pPokerRemain,
					 int nEveryPersonPokerNum, int nRemainPokerNum);

/*
 * 功能: 发牌。
         先随机产生54张牌放入pTempPokerEx中，
         然后随机产生一个[0, i - 1]范围内的数nPokerExIndex，
		 如果pTempPokerEx[nPokerExIndex]的标记位为TRUE，就把pTempPokerEx[i - 1]标记为TRUE，
		                 并把该pTempPokerEx[i - 1]牌发给3个人中的一个；
		 如果pTempPokerEx[nPokerExIndex]的标记位为FALSE，就把pTempPokerEx[nPokerExIndex]标记为TRUE，
		                 并把该pTempPokerEx[nPokerExIndex]牌发给3个人中的一个。
 * 名称: DealEx。
 * 参数: const Poker* pPoker，指向一个数组，该数组数据是输入数据。
 * 参数: int nLength，pPoker数组的长度。
 * 参数: Poker* pPoker1，指向存放第1个人牌的数组，该数组数据是输出数据。
 * 参数: Poker* pPoker2，指向存放第2个人牌的数组，该数组数据是输出数据。
 * 参数: Poker* pPoker3，指向存放第3个人牌的数组，该数组数据是输出数据。
 * 参数: int nEveryPersonLength，pPoker1或pPoker2或pPoker3数组的长度。
 * 参数: Poker* pPokerRemain，指向存放剩余未发牌的数组，该数组数据是输出数据。
 * 参数: int nRemainLength，pPokerRemain数组的长度。
 * 返回值: void。
 */
void DealEx(const Poker* pPoker, int nLength, Poker* pPoker1, Poker* pPoker2, Poker* pPoker3, int nEveryPersonLength,
		  Poker* pPokerRemain, int nRemainLength);
void OutputDealExBefore(const Poker* pPoker, int nPokerNum);
void OutputDealExAfter(const Poker* pPoker1, const Poker* pPoker2, const Poker* pPoker3, const Poker* pPokerRemain,
					 int nEveryPersonPokerNum, int nRemainPokerNum);

void Output(const Poker* pPoker, int nLength);

int main()
{
	Poker arrPoker[POKER_NUM] =
	{
		{1, PT_DIAMONDS}, {2, PT_DIAMONDS}, {3, PT_DIAMONDS}, {4, PT_DIAMONDS}, {5, PT_DIAMONDS}, {6, PT_DIAMONDS}, {7, PT_DIAMONDS},
		{8, PT_DIAMONDS}, {9, PT_DIAMONDS}, {10, PT_DIAMONDS}, {11, PT_DIAMONDS}, {12, PT_DIAMONDS}, {13, PT_DIAMONDS},
		{1, PT_CLUBS}, {2, PT_CLUBS}, {3, PT_CLUBS}, {4, PT_CLUBS}, {5, PT_CLUBS}, {6, PT_CLUBS}, {7, PT_CLUBS},
		{8, PT_CLUBS}, {9, PT_CLUBS}, {10, PT_CLUBS}, {11, PT_CLUBS}, {12, PT_CLUBS}, {13, PT_CLUBS},
		{1, PT_HEARTS}, {2, PT_HEARTS}, {3, PT_HEARTS}, {4, PT_HEARTS}, {5, PT_HEARTS}, {6, PT_HEARTS}, {7, PT_HEARTS},
		{8, PT_HEARTS}, {9, PT_HEARTS}, {10, PT_HEARTS}, {11, PT_HEARTS}, {12, PT_HEARTS}, {13, PT_HEARTS},
		{1, PT_SPADES}, {2, PT_SPADES}, {3, PT_SPADES}, {4, PT_SPADES}, {5, PT_SPADES}, {6, PT_SPADES}, {7, PT_SPADES},
		{8, PT_SPADES}, {9, PT_SPADES}, {10, PT_SPADES}, {11, PT_SPADES}, {12, PT_SPADES}, {13, PT_SPADES},
		{14, PT_SMALLJOKER}, {15, PT_BIGJOKER}
	};
	Poker arrPoker1[EVERY_PERSON_POKER_NUM] = {0};
	Poker arrPoker2[EVERY_PERSON_POKER_NUM] = {0};
	Poker arrPoker3[EVERY_PERSON_POKER_NUM] = {0};
	Poker arrPokerRemain[REMAIN_POKER_NUM] = {0};

	OutputDealBefore(arrPoker, POKER_NUM);
	Deal(arrPoker, POKER_NUM, arrPoker1, arrPoker2, arrPoker3, EVERY_PERSON_POKER_NUM, arrPokerRemain, REMAIN_POKER_NUM);
	OutputDealAfter(arrPoker1, arrPoker2, arrPoker3, arrPokerRemain, EVERY_PERSON_POKER_NUM, REMAIN_POKER_NUM);

	memset(arrPoker1, 0, sizeof(arrPoker1));
	memset(arrPoker2, 0, sizeof(arrPoker2));
	memset(arrPoker3, 0, sizeof(arrPoker3));
	memset(arrPokerRemain, 0, sizeof(arrPokerRemain));

	printf("\n\n");
	OutputDealExBefore(arrPoker, POKER_NUM);
	DealEx(arrPoker, POKER_NUM, arrPoker1, arrPoker2, arrPoker3, EVERY_PERSON_POKER_NUM, arrPokerRemain, REMAIN_POKER_NUM);
	OutputDealExAfter(arrPoker1, arrPoker2, arrPoker3, arrPokerRemain, EVERY_PERSON_POKER_NUM, REMAIN_POKER_NUM);

	return 0;
}

void Deal(const Poker* pPoker, int nLength, Poker* pPoker1, Poker* pPoker2, Poker* pPoker3, int nEveryPersonLength,
		  Poker* pPokerRemain, int nRemainLength)
{
	int i = 0;
	int j = 0;
	int k = 0;

	int nCount1 = 0;
	int nCount2 = 0;
	int nCount3 = 0;

	int nPokerIndex = 0;
	Poker pokerTemp = {0};
	Poker* pTempPoker = (Poker*)malloc(sizeof(Poker) * nLength);

	for (i = 0; i < nLength; ++i)
	{
		pTempPoker[i] = pPoker[i];
	}

	srand((unsigned int)time(NULL));
	for (i = nLength; i > nRemainLength; --i)
	{
		nPokerIndex = rand() % i;

		++k;
		if (k == 1)
		{
			pPoker1[nCount1++] = pTempPoker[nPokerIndex];
		}
		else if (k == 2)
		{
			pPoker2[nCount2++] = pTempPoker[nPokerIndex];
		}
		else
		{
			pPoker3[nCount3++] = pTempPoker[nPokerIndex];
			k = 0;
		}

		if (nPokerIndex != i - 1)
		{
			pokerTemp = pTempPoker[nPokerIndex];
			pTempPoker[nPokerIndex] = pTempPoker[i - 1];
			pTempPoker[i - 1] = pokerTemp;
		}
	}
	
	for (i = 0; i < nRemainLength; ++i)
	{
		pPokerRemain[i] = pTempPoker[i];
	}

	free(pTempPoker);
	pTempPoker = NULL;
}

void OutputDealBefore(const Poker* pPoker, int nPokerNum)
{
	printf("[********** Before Deal **********]\n");
	Output(pPoker, nPokerNum);
}

void OutputDealAfter(const Poker* pPoker1, const Poker* pPoker2, const Poker* pPoker3, const Poker* pPokerRemain,
					 int nEveryPersonPokerNum, int nRemainPokerNum)
{
	printf("\n[********** After Deal **********]\n");
	printf("Person 1:\n");
	Output(pPoker1, nEveryPersonPokerNum);
	printf("Person 2:\n");
	Output(pPoker2, nEveryPersonPokerNum);
	printf("Person 3:\n");
	Output(pPoker3, nEveryPersonPokerNum);
	printf("Remain:\n");
	Output(pPokerRemain, nRemainPokerNum);
}

void DealEx(const Poker* pPoker, int nLength, Poker* pPoker1, Poker* pPoker2, Poker* pPoker3, int nEveryPersonLength,
		  Poker* pPokerRemain, int nRemainLength)
{
	int i = 0;
	int j = 0;

	int nCount1 = 0;
	int nCount2 = 0;
	int nCount3 = 0;

	int nPokerExIndex = 0;
	PokerEx pokerExTemp = {0};
	PokerEx* pTempPokerEx = (PokerEx*)malloc(sizeof(PokerEx) * nLength);

	for (i = 0; i < nLength; ++i)
	{
		pTempPokerEx[i].p = pPoker[i];
		pTempPokerEx[i].bFlag = FALSE;
	}
	srand((unsigned int)time(NULL));
	for (i = nLength; i > 1; --i)
	{
		nPokerExIndex = rand() % i;
		if (nPokerExIndex != i - 1)
		{
			pokerExTemp = pTempPokerEx[nPokerExIndex];
			pTempPokerEx[nPokerExIndex] = pTempPokerEx[i - 1];
			pTempPokerEx[i - 1] = pokerExTemp;
		}
	}
	
	for (i = 2; i <= nLength - nRemainLength; ++i)
	{
		nPokerExIndex = rand() % i;
		if (pTempPokerEx[nPokerExIndex].bFlag)
		{
			// nPokerExIndex肯定不等于i - 1
			pTempPokerEx[i - 1].bFlag = TRUE;
			pokerExTemp = pTempPokerEx[i - 1];
		}
		else
		{
			pTempPokerEx[nPokerExIndex].bFlag = TRUE;
			pokerExTemp = pTempPokerEx[nPokerExIndex];
		}

		++j;
		if (j == 1)
		{
			pPoker1[nCount1++] = pokerExTemp.p;
		}
		else if (j == 2)
		{
			pPoker2[nCount2++] = pokerExTemp.p;
		}
		else
		{
			pPoker3[nCount3++] = pokerExTemp.p;
			j = 0;
		}
	}

	for (i = 0; i < nLength - nRemainLength; ++i)
	{
		if (!pTempPokerEx[i].bFlag)
		{
			pPoker3[nCount3] = pTempPokerEx[i].p;
			break;
		}
	}

	for (i = 0; i < nRemainLength; ++i)
	{
		pPokerRemain[i] = pTempPokerEx[nLength - nRemainLength + i].p;
	}

	free(pTempPokerEx);
	pTempPokerEx = NULL;
}

void OutputDealExBefore(const Poker* pPoker, int nPokerNum)
{
	printf("[********** Before DealEx **********]\n");
	Output(pPoker, nPokerNum);
}

void OutputDealExAfter(const Poker* pPoker1, const Poker* pPoker2, const Poker* pPoker3, const Poker* pPokerRemain,
					 int nEveryPersonPokerNum, int nRemainPokerNum)
{
	printf("\n[********** After DealEx **********]\n");
	printf("Person 1:\n");
	Output(pPoker1, nEveryPersonPokerNum);
	printf("Person 2:\n");
	Output(pPoker2, nEveryPersonPokerNum);
	printf("Person 3:\n");
	Output(pPoker3, nEveryPersonPokerNum);
	printf("Remain:\n");
	Output(pPokerRemain, nRemainPokerNum);
}

void Output(const Poker* pPoker, int nLength)
{
	const char* arrPokerNumber[PART_POKER_NUM] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	const char* arrPokerType[POKER_COLOR_NUM] = {"方块", "梅花", "红桃", "黑桃"};
	const char* pchSmallJoker = "小王";
	const char* pchBigJoker = "大王";
	int i = 0;
	int j = 0;
	int nShowForOneLine = 10;

	for (i = 0; i < nLength; ++i)
	{
		if (pPoker[i].nNum == 14)
		{
			printf("%s", pchSmallJoker);
		}
		else if (pPoker[i].nNum == 15)
		{
			printf("%s", pchBigJoker);
		}
		else
		{
			j = (pPoker[i].nNum - 1) % PART_POKER_NUM;
			printf("%s%s", arrPokerType[pPoker[i].pt], arrPokerNumber[j]);
		}

		if (i != nLength - 1)
		{
			printf(", ");
			if ((i + 1) % nShowForOneLine == 0)
			{
				printf("\n");
			}
		}
		else 
		{
			printf("\n");
		}
	}
}
