/* Problem: For each element, count how many smaller elements appear on right side.
Use merge sort technique or Fenwick Tree (BIT).
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Pair;

void merge(Pair *arr, int left, int mid, int right, int *count, Pair *temp) {
    int i = left, j = mid + 1, k = left;
    int rightCount = 0;

    while (i <= mid && j <= right) {
        if (arr[i].value <= arr[j].value) {
            count[arr[i].index] += rightCount;
            temp[k++] = arr[i++];
        } else {
            rightCount++;
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        count[arr[i].index] += rightCount;
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (int i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

void mergeSort(Pair *arr, int left, int right, int *count, Pair *temp) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, count, temp);
    mergeSort(arr, mid + 1, right, count, temp);
    merge(arr, left, mid, right, count, temp);
}

int main() {
    int nums[] = {5, 2, 6, 1};
    int n = sizeof(nums) / sizeof(nums[0]);

    Pair *arr = (Pair *)malloc(n * sizeof(Pair));
    Pair *temp = (Pair *)malloc(n * sizeof(Pair));
    int *count = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i].value = nums[i];
        arr[i].index = i;
    }

    mergeSort(arr, 0, n - 1, count, temp);

    printf("Output: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", count[i]);
    }

    free(arr);
    free(temp);
    free(count);

    return 0;
}