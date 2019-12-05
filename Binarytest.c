#define _CRT_SECURE_NO_WARNINGS
#define LEN 100

#include <stdio.h>
#include "Binary_Search.h"
#include <time.h> // time_t time(time_t *timeptr) , clock_t clock(void)
#include <stdlib.h> // void srand(unsinged int seed) , int rand(void)
#include <string.h> // strcpy()

void bubblesort(const int* src, int* dst, int len);

int main(void) {
	int menu,rst,target;
	//int input[LEN] = { 35, 52, 1, 77, 9, 20, 99, 65, 81, 12 }, i;
	int input[LEN] = { 0, }, i;
	time_t mytime;

	while (1) {
		time(&mytime);
		srand((unsigned int)mytime);
		for (i = 0; i < LEN; i++)
			input[i] = rand();
		printf("{");
		for (i = 0; i < LEN; i++)
			printf("%d, ", input[i]);
		printf("}\n");
		///////////////////////테스트를 위한 난수 입력
		printf("BinarySearch(0)Exit(1)\n");
		scanf("%d", &menu);
		if (menu == 1)
			break;
		else if (menu == 0) {
			printf("어떤 정수를 찾습니까?\n");
			scanf("%d", &target);
			rst = binarysearch(input,sizeof(input)/sizeof(input[0]),target, bubblesort); // 갯수 = 10개
			printf("결과 index(sorted array) : %d\n", rst);
		}
		else
			printf("올바른 값을 입력하세요\n");
	}
	return 0;
}

void bubblesort(const int* src, int* dst, int len) { // 오름차순으로 하겠다
	int i, j;
	int temp;
	for (i = 0; i < len; i++)
		dst[i] = src[i];
	for (i = 0; i < len-1; i++) {
		for (j = 0; j < len - i - 1; j++) {
			if (dst[j] > dst[j + 1]) {
				temp = dst[j];
				dst[j] = dst[j + 1];
				dst[j + 1] = temp;
			}
		}
	}
}