#define _CRT_SECURE_NO_WARNINGS
#define LEN 100 // �����ϰ� ������ ���� LEN�� �۰� �ΰ� ��������
#include <stdio.h>
#include <time.h> // time(), clock()
#include <stdlib.h> // rand(), srand()
#include "Sorts.h"

int main(void) {
	int menu,i;
	//int example[LEN] = { 5,3,60,41,312,6001,21,99,85,85 };
	int example[LEN] = { 0, };
	time_t mytime;
	clock_t start, end;
	int sorted[LEN] = { 0, };
	int temparray[LEN] = { 0, };
	
	time(&mytime);
	srand((unsigned int)mytime);

	printf("ó�� �迭 = {");
	for (i = 0; i < LEN; i++) { // ó�� �迭 �����ֱ�
		example[i] = rand();
		printf("%d, ", example[i]);
	}
	printf("}\n\n");

	while (1) {
		for (i = 0; i < LEN; i++) // temparray initialization, recovery ( merge �� ���� �ٲ� �� ó������ �ǵ����� )
			temparray[i] = example[i];

		printf("Selection(0),Insertion(1),Bubble(2),Quick(3),Merge(4),Exit(5)\n");
		scanf("%d", &menu);
		if (menu == 5)
			break;
	
		switch (menu) {
		case 0:
			start = clock();
			selectionsort(example, sorted, LEN, compareint);
			end = clock();
			printarr(sorted, LEN);
			printf("selectionsort �ɸ� �ð� : %f [ms]\n", (double)end - start);
			break;
		case 1:
			start = clock();
			insertionsort(example,sorted, LEN, compareint);
			end = clock();
			printarr(sorted, LEN);
			printf("insertionsort �ɸ� �ð� : %f [ms]\n", (double)end - start);
			break;
		case 2:
			start = clock();
			bubblesort(example, sorted, LEN, compareint);
			end = clock();
			printarr(sorted, LEN);
			printf("bubblesort �ɸ� �ð� : %f [ms]\n", (double)end - start);
			break;
		case 3:
			for (i = 0; i < LEN; i++)
				sorted[i] = example[i];
			start = clock();
			quicksort(sorted, 0, LEN-1, compareint);
			end = clock();
			printarr(sorted, LEN);
			printf("quicksort �ɸ� �ð� : %f [ms]\n", (double)end - start);
			break;
		case 4:
			start = clock();
			mergesort(temparray, sorted, 0, LEN - 1, compareint); // ���� �迭�� �ջ��Ű�� �������� temparray�� ����
			end = clock();
			printarr(sorted, LEN);
			printf("mergesort �ɸ� �ð� : %f [ms]\n", (double)end - start);
			for (i = 0; i < LEN; i++) // recovery
				temparray[i] = example[i];
			break;
		}
		for (i = 0; i < LEN; i++) // recovery
			sorted[i] = 0;
	}
	return 0;
}