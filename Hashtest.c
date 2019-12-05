// Hashing ��� : Module-Division // Collision ó�� : Linked lists
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
	time_t mytime; // �����߻��� ����
	hash harr[LISTSIZE] = { 0, }; // �̹����� main�Լ��� ����ü �迭�� ���� �����ؼ� �����غ����� ��.

	for (i = 0; i < LISTSIZE; i++) { // hash structure initialization
		harr[i].topnode = NULL;
		harr[i].cnt = 0;
	}

	while (1) {
		time(&mytime);
		srand((unsigned int)mytime);
		for (i = 0; i < LEN; i++)
			input[i] = rand();
		printf("\n������ �Է� �迭\n{");
		for (i = 0; i < LEN; i++) {
			printf("%d, ", input[i]);
			hashin(harr, modulo(input[i]), input[i]); // Hashing ��� : Module-Division // Collision ó�� : Linked lists
		}
		printf("}\n");

		printf("HashedSearch(0)Exit(1)\n");
		scanf("%d", &menu);
		if (menu == 1)
			break;
		else if (menu == 0) {
			printf("� ������ ã���ϱ�?\n");
			scanf("%d", &target);
			printhash(harr, LISTSIZE);
			rst = finddata(harr, target);
			printf("���: %d (1 : Found / 0 : Not)\n", rst);
		}
		else
			printf("�ùٸ� ���� �Է��ϼ���\n");
	}
	for (i = 0; i < LISTSIZE; i++) // freeing
		myrecurfree(harr[i], harr[i].topnode);
	return 0;
}