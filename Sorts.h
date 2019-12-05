#pragma once
#include <stdio.h>

int compareint(void* dataptr1, void* dataptr2) {
	return *(int*)dataptr1 - *(int*)dataptr2;
}

void selectionsort(const int* src, int* dst, int len, int (*compare) (void*, void*)) {
	int start = 0, end = len - 1, i, minidx = 0, temp;
	for (i = 0; i < len; i++)
		dst[i] = src[i];
	while (start < end) {
		for (i = start; i <= end; i++) {
			if (compare(&dst[i], &dst[minidx]) < 0)
				minidx = i;
		}
		temp = dst[start];
		dst[start] = dst[minidx];
		dst[minidx] = temp;
		start++;
		minidx = start;
	}
}

void insertionsort(const int* src, int* dst, int len, int (*compare) (void*, void*)) {
	int i, j, left = 1, right = len-1, rem, temp;

	for (i = 0; i < len; i++)
		dst[i] = src[i];
	while (left <= right) {
		for (i = 0; i < left; i++) {
			if (compare(&dst[i], &dst[left]) > 0) {// unsorted left ���� sorted[i] ���� ���� �� �ݺ��� ���߰� �� �ڸ��� left ���� ������
				rem = dst[left];
				break;
			}
		}
		if (i != left) {// i==left )) left�� ���� ������ ��
			for (j = left-1; j > i-1; j--) { // i!=left )) [i]~[left-1] ���� ��ĭ �������� �б�. �����ʺ��� �����ϸ� �˾Ƽ� [left]�� [i]�� ã�ư�
				temp = dst[j];
				dst[j] = dst[j + 1];
				dst[j + 1] = temp;
			}
		}
		left++;
	}
}

void bubblesort(const int* src, int* dst, int len, int (*compare) (void*, void*) ){ // ������������ �ϰڴ�
	int i, j, temp;

	for (i = 0; i < len; i++)
		dst[i] = src[i];
	for (i = 0; i < len - 1; i++) {
		for (j = 0; j < len - i - 1; j++) {
			if (compare(&dst[j],&dst[j+1]) > 0 ) {
				temp = dst[j];
				dst[j] = dst[j + 1];
				dst[j + 1] = temp;
			}
		}
	}
}

int partition(int src[], int left, int right, int (*compare) (void*, void*)) { // quicksort �� �ʿ��� subfunction
	int pivotval, temp, low, high;

	pivotval = src[left]; // ù ���� pivot���� �ϰ� ������ �� �߰��� �ֱ�� ��.
	low = left;
	high = right + 1;

	do {
		do {
			low++;
		} while (low <= right && compare(&src[low], &pivotval) < 0); // ���ʿ��� pivotval���� ���� ����

		do {
			high--;
		} while (high >= left + 1 && compare(&src[high], &pivotval) >= 0); // �����ʿ��� ���ų� ū ����

		if (low < high) {
			temp = src[low];
			src[low] = src[high];
			src[high] = temp;
		}
	} while (low < high);

	temp = src[left];
	src[left] = src[high];
	src[high] = temp;

	return high; // ���������Ƿ� high ��ġ ���� left ��ġ ���� �����ϰ� high ��ġ�� pivot�� ��ġ�� �ȴ�.
}

void quicksort(int* src, int left, int right, int (*compare) (void*, void*)) {
	int pivotidx;

	if (left < right) { // left==right �� �����Ͱ� 1��, left>right �� �����Ͱ� 0���� Partition�� �Ұ��ϹǷ� ���ǹ� �ޱ�
		pivotidx = partition(src, left, right, compare);
		
		quicksort(src, left, pivotidx - 1, compare);
		quicksort(src, pivotidx + 1, right, compare);
	}
}

void merge(int* src, int* dst, int left, int mid, int right, int (*compare) (void*, void*)) {
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i!=mid+1 && j!=right+1) {
		if (compare(&src[i], &src[j]) < 0) {
			dst[k++] = src[i++];
		}
		else {
			dst[k++] = src[j++];
		}
	}
	if (i == mid + 1) {
		for (; j < right + 1; j++)
			dst[k++] = src[j];
	}
	else {
		for (; i < mid + 1; i++)
			dst[k++] = src[i];
	}
	//Important! Divide�� �� Conquer�� dst�� ���ִµ� src�� ������ �״�ζ� compare�� ���� �߻��ϹǷ� Conquer�ϸ鼭 ��� src�� Update �ʿ�
	for (i = left; i < right + 1; i++)
		src[i] = dst[i];
	//printf("merge�ǰ� �ֽ��ϴ� src�� �����帮�ڽ��ϴ� = {");
	//for (i = left; i < right + 1; i++)
	//	printf("%d, ", src[i]);
	//printf("}\n\n");
}

void mergesort(int* src, int* dst, int left, int right, int (*compare) (void*, void*)) { // ���� �迭�� ���Ѵ�. dst�� merge���� ���
	int mid = (left + right) / 2;
	if (left < right) { // left = right �� ����Ʈ ������ 1���ϱ� Divide�� �����. left > right�� ����Ʈ ���� = 0�� (�׷� �� ����)
		mergesort(src, dst, left, mid, compare);
		mergesort(src, dst, mid + 1, right, compare);
		//���� Conquer? Merge?�� ����
		merge(src, dst, left, mid, right, compare);
	}
}

void printarr(int* arr, int len) {
	int i;
	printf("sorting�� �迭 = {");
	for(i=0;i<len;i++)
		printf("%d, ", arr[i]);
	printf("}\n\n");
}