/* Problem: Sort array of non-negative integers using counting sort.
Find max, build freq array, compute prefix sums, build output.
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d non-negative integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Step 1: Find maximum element
    int max = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    // Step 2: Create frequency array
    int *count = (int *)calloc(max + 1, sizeof(int));
    for (i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // Step 3: Compute prefix sums
    for (i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Step 4: Build output array (stable sort)
    int *output = (int *)malloc(n * sizeof(int));
    for (i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Step 5: Copy output back to original array
    for (i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    printf("Sorted array:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    // Free allocated memory
    free(count);
    free(output);

    return 0;
}