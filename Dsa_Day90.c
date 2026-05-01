/* Problem Statement
Given n boards of different lengths and k painters, each painter paints contiguous boards. Painting a unit length of board takes one unit of time.

Determine the minimum time required to paint all boards.

Input Format
n k
n space-separated integers representing board lengths

Output Format
Print the minimum time required to paint all boards.

Sample Input
4 2
10 20 30 40

Sample Output
60

Explanation
One painter paints boards of length 10, 20, and 30 (total 60), while the other paints board of length 40.
*/
#include <stdio.h>

// Function to check if boards can be painted
// within given time using k painters
int isPossible(int boards[], int n, int k, int maxTime) {
    int painters = 1;
    int timeSum = 0;

    for (int i = 0; i < n; i++) {
        if (timeSum + boards[i] <= maxTime) {
            timeSum += boards[i];
        } else {
            painters++;
            timeSum = boards[i];

            if (painters > k) {
                return 0; // Not possible
            }
        }
    }
    return 1; // Possible
}

int findMinTime(int boards[], int n, int k) {
    int low = 0, high = 0;
    int result = 0;

    // Find maximum board length and sum of boards
    for (int i = 0; i < n; i++) {
        if (boards[i] > low)
            low = boards[i];
        high += boards[i];
    }

    // Binary Search
    while (low <= high) {
        int mid = (low + high) / 2;

        if (isPossible(boards, n, k, mid)) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return result;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int boards[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &boards[i]);
    }

    printf("%d\n", findMinTime(boards, n, k));
    return 0;
}