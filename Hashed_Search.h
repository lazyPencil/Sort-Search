#pragma once
#define LISTSIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	int data;
	struct node* nextnode;
}node;

typedef struct hash {
	node* topnode;
	int cnt;
}hash;

int modulo(int data) {
	return data % LISTSIZE;
}

// newdata를 갖는 newNode를 만든다.
// h1[addr]에 연결 ( case 1 : cnt=0 -> topnode에 newNode 연결 / case 2 : h1[addr].topnode->nextnode->...-> 에 newNode 연결
// count 1 증가
void hashin(hash h1[], int addr, int newdata) {
	node* nNew = NULL;
	node* nTemp = NULL;

	nNew = (node*)malloc(sizeof(node));
	if (!nNew) return;
	nNew->data = newdata;
	nNew->nextnode = NULL;
	if (h1[addr].cnt == 0)// 아무 데이터도 없을 때. topnode = NULL
		h1[addr].topnode = nNew;
	else {
		nTemp = h1[addr].topnode;
		while (nTemp->nextnode != NULL)
			nTemp = nTemp->nextnode;
		nTemp->nextnode = nNew;
	}
	h1[addr].cnt++;
}
// find의 mod가 address므로 h1[mod]로 가서 찾아본다. (data가 여러 개 일수도 있어서 반복해서 찾아본다.)
bool finddata(hash h1[], int find) {
	int mod = modulo(find);
	node* nTemp = h1[mod].topnode;
	while (nTemp) {
		if (nTemp->data == find) 
			return true;
		nTemp = nTemp->nextnode;
	}
	return false;
}

//address별로 data들을 출력
void printhash(hash h1[], int size) {
	int i;
	node* nTemp = NULL;
	for (i = 0; i < size; i++) {
		printf("arr[%d] >> ",i);
		nTemp = h1[i].topnode;
		while (nTemp) {
			printf("%d ", nTemp->data);
			nTemp = nTemp->nextnode;
		}
		puts("");
	}
}

//Linked list의 끝 노드에서부터 free하기 위한 recursion implementation
void myrecurfree(hash h1 , node* n1) {
	if (n1 == NULL)
		return;
	myrecurfree(h1 , n1->nextnode);
	free(n1);
	h1.cnt--;
}