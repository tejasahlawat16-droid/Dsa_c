/* Problem: Given n real numbers in [0,1), sort using bucket sort algorithm.
Distribute into buckets, sort each, concatenate.
*/
#include <stdio.h>
#include <stdlib.h>

/* Node for linked list (bucket) */
struct Node {
    float val;
    struct Node *next;
};

/* Insert element in sorted order (Insertion Sort for linked list) */
struct Node* insertSorted(struct Node* head, float value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = value;
    newNode->next = NULL;

    if (head == NULL || head->val >= value) {
        newNode->next = head;
        return newNode;
    }

    struct Node* curr = head;
    while (curr->next != NULL && curr->next->val < value) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}

int main() {
    int n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    float arr[n];
    printf("Enter %d real numbers in range [0,1):\n", n);
    for (i = 0; i < n; i++) {
        scanf("%f", &arr[i]);
    }

    /* Step 1: Create n empty buckets */
    struct Node* buckets[n];
    for (i = 0; i < n; i++) {
        buckets[i] = NULL;
    }

    /* Step 2: Distribute elements into buckets */
    for (i = 0; i < n; i++) {
        int index = n * arr[i];  // Bucket index
        buckets[index] = insertSorted(buckets[index], arr[i]);
    }

    /* Step 3: Concatenate buckets */
    int k = 0;
    for (i = 0; i < n; i++) {
        struct Node* curr = buckets[i];
        while (curr != NULL) {
            arr[k++] = curr->val;
            curr = curr->next;
        }
    }

    printf("Sorted array:\n");
    for (i = 0; i < n; i++) {
        printf("%.4f ", arr[i]);
    }

    return 0;
}