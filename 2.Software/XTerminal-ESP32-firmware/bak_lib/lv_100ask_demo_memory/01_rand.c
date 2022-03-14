#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_NUM 10
#define COUNT   10


// 生成m个小于n的不重复随机数的算法
static int* init_rand(int ayyr[], int count)
{
	int w, t;
	srand((unsigned)time(NULL));
	for (int i = 0; i < count; i++)
	    ayyr[i] = i + 1;
	for (int j = 0; j < count; j++)
	{
	    w = rand() % (count - j) + j;
	    t = ayyr[j];
	    ayyr[j] = ayyr[w];
	    ayyr[w] = t;
	}
}

#if 0
void main()
{
	int a1[COUNT] = {0};
	int a2[COUNT] = {0};

	init_rand(a1, COUNT);
	init_rand(a2, COUNT);

	for (int i = 0; i < COUNT; i++)
	    printf("%d ", a1[i]);
	printf("\n");
	for (int i = 0; i < COUNT; i++)
	    printf("%d ", a2[i]);
	printf("\n");
}
#endif

#if 0
void main()
{
	int w, t;
	int a[COUNT] = {0};
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX_NUM; i++)
	    a[i] = i + 1;
	for (int j = 0; j < COUNT; j++)
	{
	    w = rand() % (MAX_NUM - j) + j;
	    t = a[j];
	    a[j] = a[w];
	    a[w] = t;
	}
	for (int i = 0; i < COUNT; i++)
	    printf("%d ", a[i]);

}
#endif



