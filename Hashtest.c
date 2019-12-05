// Hashing 방법 : Module-Division // Collision 처리 : Linked lists
#define _CRT_SECURE_NO_WARNINGS
#define LEN 1000
#define LISTSIZE 10
#include <stdio.h>
#include <time.h> // time_t time(time_t *timeptr) , clock_t clock(void)
#include <stdlib.h> // void srand(unsinged int seed) , int rand(void)
#include "Hashed_Search.h"

int main(void) {
	int menu, target;
	bool rst;
	//int input[LEN] = { 35, 52, 1, 77, 9, 20, 99, 65, 81, 12 },i;
	int input[LEN] = { 0, }, i;
	time_t mytime; // 난수발생을 위함
	hash harr[LISTSIZE] = { 0, }; // 이번에는 main함수에 구조체 배열을 직접 선언해서 구현해보려고 함.

	for (i = 0; i < LISTSIZE; i++) { // hash structure initialization
		harr[i].topnode = NULL;
		harr[i].cnt = 0;
	}

	while (1) {
		time(&mytime);
		srand((unsigned int)mytime);
		for (i = 0; i < LEN; i++)
			input[i] = rand();
		printf("\n무작위 입력 배열\n{");
		for (i = 0; i < LEN; i++) {
			printf("%d, ", input[i]);
			hashin(harr, modulo(input[i]), input[i]); // Hashing 방법 : Module-Division // Collision 처리 : Linked lists
		}
		printf("}\n");

		printf("HashedSearch(0)Exit(1)\n");
		scanf("%d", &menu);
		if (menu == 1)
			break;
		else if (menu == 0) {
			printf("어떤 정수를 찾습니까?\n");
			scanf("%d", &target);
			printhash(harr, LISTSIZE);
			rst = finddata(harr, target);
			printf("결과: %d (1 : Found / 0 : Not)\n", rst);
		}
		else
			printf("올바른 값을 입력하세요\n");
	}
	for (i = 0; i < LISTSIZE; i++) // freeing
		myrecurfree(harr[i], harr[i].topnode);
	return 0;
}