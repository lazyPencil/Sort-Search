#pragma once
#include <stdlib.h>

void printarr(int* arr, int len) {
	int i;
	printf("{");
	for (i = 0; i < len; i++)
		printf("%d, ", arr[i]);
	printf("}\n");
}
//�������� sorted list�� ���� ���
//�߰����� ��, find�� ũ�� start=mid+1, find�� ������ end=mid-1.
//�پ�� �������� �ٽ� ����
//�ݺ��� Ż�� ���� : ���� ã�Ұų� or start > end (������ ���µ� ���� ��)
//return value : found index (�� ã���� -1)
int binarysearch(int* arr, int len, int find, void (*sort)(const int*, int*, int)) { // ã���� ã�� index, �� ã���� -1 // iteration style
	int start = 0, end = len - 1, mid, result;
	int* sorted = (int*)calloc(len, sizeof(int));
	if (sorted == NULL)
		return -1;
	sort(arr, sorted, len);
	printf("sorting��\n");
	printarr(sorted,len);
	while (1) {
		if (start > end) { // Not Found
			result = -1;
			break;
		}
		mid = (start + end) / 2;
		if (find < sorted[mid])
			end = mid - 1;
		else if (find > sorted[mid])
			start = mid + 1;
		else {// Found
			result = mid;
			break;
		}
	}
	free(sorted);
	return result;
}