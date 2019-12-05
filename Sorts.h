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
			if (compare(&dst[i], &dst[left]) > 0) {// unsorted left 값이 sorted[i] 보다 작을 때 반복을 멈추고 그 자리로 left 값을 보내기
				rem = dst[left];
				break;
			}
		}
		if (i != left) {// i==left )) left는 가만 있으면 됨
			for (j = left-1; j > i-1; j--) { // i!=left )) [i]~[left-1] 값을 한칸 우측으로 밀기. 오른쪽부터 시작하면 알아서 [left]가 [i]로 찾아감
				temp = dst[j];
				dst[j] = dst[j + 1];
				dst[j + 1] = temp;
			}
		}
		left++;
	}
}

void bubblesort(const int* src, int* dst, int len, int (*compare) (void*, void*) ){ // 오름차순으로 하겠다
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

int partition(int src[], int left, int right, int (*compare) (void*, void*)) { // quicksort 에 필요한 subfunction
	int pivotval, temp, low, high;

	pivotval = src[left]; // 첫 값을 pivot으로 하고 분할한 뒤 중간에 넣기로 함.
	low = left;
	high = right + 1;

	do {
		do {
			low++;
		} while (low <= right && compare(&src[low], &pivotval) < 0); // 왼쪽에는 pivotval보다 작은 값만

		do {
			high--;
		} while (high >= left + 1 && compare(&src[high], &pivotval) >= 0); // 오른쪽에는 같거나 큰 값만

		if (low < high) {
			temp = src[low];
			src[low] = src[high];
			src[high] = temp;
		}
	} while (low < high);

	temp = src[left];
	src[left] = src[high];
	src[high] = temp;

	return high; // 교차했으므로 high 위치 값과 left 위치 값을 스왑하고 high 위치가 pivot의 위치가 된다.
}

void quicksort(int* src, int left, int right, int (*compare) (void*, void*)) {
	int pivotidx;

	if (left < right) { // left==right 면 데이터가 1개, left>right 면 데이터가 0개라서 Partition이 불가하므로 조건문 달기
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
	//Important! Divide한 후 Conquer를 dst에 해주는데 src는 여전히 그대로라서 compare시 문제 발생하므로 Conquer하면서 계속 src를 Update 필요
	for (i = left; i < right + 1; i++)
		src[i] = dst[i];
	//printf("merge되고 있습니다 src를 보여드리겠습니다 = {");
	//for (i = left; i < right + 1; i++)
	//	printf("%d, ", src[i]);
	//printf("}\n\n");
}

void mergesort(int* src, int* dst, int left, int right, int (*compare) (void*, void*)) { // 원래 배열이 변한다. dst는 merge에서 사용
	int mid = (left + right) / 2;
	if (left < right) { // left = right 면 리스트 개수가 1개니까 Divide가 멈춘다. left > right면 리스트 개수 = 0개 (그럴 일 없음)
		mergesort(src, dst, left, mid, compare);
		mergesort(src, dst, mid + 1, right, compare);
		//이제 Conquer? Merge?할 차례
		merge(src, dst, left, mid, right, compare);
	}
}

void printarr(int* arr, int len) {
	int i;
	printf("sorting후 배열 = {");
	for(i=0;i<len;i++)
		printf("%d, ", arr[i]);
	printf("}\n\n");
}