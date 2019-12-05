#pragma once
#include <stdlib.h>

void printarr(int* arr, int len) {
	int i;
	printf("{");
	for (i = 0; i < len; i++)
		printf("%d, ", arr[i]);
	printf("}\n");
}
//오름차순 sorted list에 대한 방법
//중간값과 비교, find가 크면 start=mid+1, find가 작으면 end=mid-1.
//줄어든 범위에서 다시 수행
//반복문 탈출 조건 : 값을 찾았거나 or start > end (끝까지 갔는데 없을 때)
//return value : found index (못 찾으면 -1)
int binarysearch(int* arr, int len, int find, void (*sort)(const int*, int*, int)) { // 찾으면 찾은 index, 못 찾으면 -1 // iteration style
	int start = 0, end = len - 1, mid, result;
	int* sorted = (int*)calloc(len, sizeof(int));
	if (sorted == NULL)
		return -1;
	sort(arr, sorted, len);
	printf("sorting후\n");
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