/* Problem Statement
Given an array of integers where each element represents the number of pages in a book, and m students, allocate books such that each student gets at least one book and the maximum number of pages assigned to a student is minimized.

Books must be allocated in contiguous order.

Input Format
n m
n space-separated integers representing pages in books

Output Format
Print the minimum possible value of the maximum pages assigned to any student.

Sample Input
4 2
12 34 67 90

Sample Output
113

Explanation
One optimal allocation is:
Student 1: 12 + 34 + 67 = 113
Student 2: 90
Maximum pages = 113 (minimum possible).
*/
#include <stdio.h>

// Function to check if allocation is possible
int isPossible(int books[], int n, int m, int maxPages) {
    int students = 1;
    int pagesSum = 0;

    for (int i = 0; i < n; i++) {
        if (books[i] > maxPages)
            return 0;   // single book exceeds limit

        if (pagesSum + books[i] <= maxPages) {
            pagesSum += books[i];
        } else {
            students++;
            pagesSum = books[i];
            if (students > m)
                return 0;
        }
    }
    return 1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int books[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &books[i]);
    }

    if (m > n) {
        printf("-1");   // Not enough books
        return 0;
    }

    int low = books[0], high = 0, ans = 0;

    for (int i = 0; i < n; i++) {
        if (books[i] > low)
            low = books[i];  // max book pages
        high += books[i];    // total pages
    }

    // Binary Search on answer
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (isPossible(books, n, m, mid)) {
            ans = mid;        // possible answer
            high = mid - 1;  // try minimizing
        } else {
            low = mid + 1;
        }
    }

    printf("%d", ans);
    return 0;
}