/* Problem Statement:
Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Tree.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 represents NULL)
- Third line contains two node values

Output Format:
- Print the LCA value

Example:
Input:
7
1 2 3 4 5 6 7
4 5

Output:
2
*/
#include <stdio.h>
#include <stdlib.h>

/* Definition of tree node */
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

/* Create new node */
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

/* Queue for level-order construction */
struct Queue {
    int front, rear;
    struct Node* arr[100];
};

/* Queue functions */
void initQueue(struct Queue* q) {
    q->front = q->rear = 0;
}

void enqueue(struct Queue* q, struct Node* node) {
    q->arr[q->rear++] = node;
}

struct Node* dequeue(struct Queue* q) {
    return q->arr[q->front++];
}

int isEmpty(struct Queue* q) {
    return q->front == q->rear;
}

/* Build tree using level order */
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1)
        return NULL;

    struct Node* root = newNode(arr[0]);
    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    int i = 1;
    while (i < n && !isEmpty(&q)) {
        struct Node* current = dequeue(&q);

        if (arr[i] != -1) {
            current->left = newNode(arr[i]);
            enqueue(&q, current->left);
        }
        i++;

        if (i < n && arr[i] != -1) {
            current->right = newNode(arr[i]);
            enqueue(&q, current->right);
        }
        i++;
    }
    return root;
}

/* LCA function */
struct Node* LCA(struct Node* root, int n1, int n2) {
    if (root == NULL)
        return NULL;

    if (root->data == n1 || root->data == n2)
        return root;

    struct Node* leftLCA = LCA(root->left, n1, n2);
    struct Node* rightLCA = LCA(root->right, n1, n2);

    if (leftLCA && rightLCA)
        return root;

    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int n1, n2;
    scanf("%d %d", &n1, &n2);

    struct Node* root = buildTree(arr, n);

    struct Node* lca = LCA(root, n1, n2);

    if (lca != NULL)
        printf("%d\n", lca->data);
    else
        printf("-1\n");

    return 0;
}