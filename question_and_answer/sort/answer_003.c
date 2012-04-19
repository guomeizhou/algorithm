#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>

/*
 * 解法: 在一个范围中随机产生一张牌，取出该张牌，然后缩小范围，如此继续下去。
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
黑桃A, 黑桃2, 梅花3, 红桃9, 红桃J, 黑桃Q, 红桃3, 黑桃3, 梅花2, 大王,
方块8, 黑桃7, 梅花A, 梅花K, 方块5, 梅花4, 红桃7
Person 2:
小王, 红桃5, 梅花8, 黑桃K, 黑桃8, 方块10, 黑桃4, 方块7, 方块Q, 梅花10,
红桃10, 梅花Q, 红桃A, 黑桃5, 梅花7, 红桃Q, 红桃6
Person 3:
黑桃6, 黑桃10, 黑桃9, 方块4, 红桃8, 方块J, 方块2, 方块6, 方块A, 红桃4,
梅花J, 红桃K, 红桃2, 方块9, 梅花5, 方块K, 梅花6
Remain:
梅花9, 黑桃J, 方块3
*/

#define POKER_NUM 54
#define REMAIN_POKER_NUM 3
#define EVERY_PERSON_POKER_NUM (POKER_NUM - REMAIN_POKER_NUM) / 3
#define PART_POKER_NUM 13
#define POKER_COLOR_NUM 4

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

	printf("[********** Before Deal **********]\n");
	Output(arrPoker, POKER_NUM);
	Deal(arrPoker, POKER_NUM, arrPoker1, arrPoker2, arrPoker3, EVERY_PERSON_POKER_NUM, arrPokerRemain, REMAIN_POKER_NUM);

	printf("\n[********** After Deal **********]\n");
	printf("Person 1:\n");
	Output(arrPoker1, EVERY_PERSON_POKER_NUM);
	printf("Person 2:\n");
	Output(arrPoker2, EVERY_PERSON_POKER_NUM);
	printf("Person 3:\n");
	Output(arrPoker3, EVERY_PERSON_POKER_NUM);
	printf("Remain:\n");
	Output(arrPokerRemain, REMAIN_POKER_NUM);

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
