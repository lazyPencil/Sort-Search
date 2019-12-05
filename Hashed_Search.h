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

// newdata�� ���� newNode�� �����.
// h1[addr]�� ���� ( case 1 : cnt=0 -> topnode�� newNode ���� / case 2 : h1[addr].topnode->nextnode->...-> �� newNode ����
// count 1 ����
void hashin(hash h1[], int addr, int newdata) {
	node* nNew = NULL;
	node* nTemp = NULL;

	nNew = (node*)malloc(sizeof(node));
	if (!nNew) return;
	nNew->data = newdata;
	nNew->nextnode = NULL;
	if (h1[addr].cnt == 0)// �ƹ� �����͵� ���� ��. topnode = NULL
		h1[addr].topnode = nNew;
	else {
		nTemp = h1[addr].topnode;
		while (nTemp->nextnode != NULL)
			nTemp = nTemp->nextnode;
		nTemp->nextnode = nNew;
	}
	h1[addr].cnt++;
}
// find�� mod�� address�Ƿ� h1[mod]�� ���� ã�ƺ���. (data�� ���� �� �ϼ��� �־ �ݺ��ؼ� ã�ƺ���.)
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

//address���� data���� ���
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

//Linked list�� �� ��忡������ free�ϱ� ���� recursion implementation
void myrecurfree(hash h1 , node* n1) {
	if (n1 == NULL)
		return;
	myrecurfree(h1 , n1->nextnode);
	free(n1);
	h1.cnt--;
}