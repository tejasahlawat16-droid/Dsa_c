/* Problem Statement
Given n stalls located at different positions along a straight line and k cows, place the cows in the stalls such that the minimum distance between any two cows is maximized.

This is an optimization problem where binary search on the answer is required.

Input Format
n k
n space-separated integers representing stall positions

Output Format
Print the maximum possible minimum distance between any two cows.

Sample Input
5 3
1 2 8 4 9

Sample Output
3

Explanation
Cows can be placed at positions 1, 4, and 8. The minimum distance between any two cows is 3, which is the maximum possible.
*/
#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Check if cows can be placed with at least 'dist' minimum distance
int canPlaceCows(int stalls[], int n, int k, int dist) {
    int cowsPlaced = 1;           // place first cow at first stall
    int lastPos = stalls[0];

    for (int i = 1; i < n; i++) {
        if (stalls[i] - lastPos >= dist) {
            cowsPlaced++;
            lastPos = stalls[i];
        }
        if (cowsPlaced == k)
            return 1;             // possible
    }
    return 0;                     // not possible
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int stalls[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &stalls[i]);
    }

    // Sort stall positions
    qsort(stalls, n, sizeof(int), compare);

    int low = 0;
    int high = stalls[n - 1] - stalls[0];
    int ans = 0;

    // Binary Search on answer
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (canPlaceCows(stalls, n, k, mid)) {
            ans = mid;        // possible answer
            low = mid + 1;   // try for larger distance
        } else {
            high = mid - 1;
        }
    }

    printf("%d", ans);
    return 0;
}