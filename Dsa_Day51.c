/* Problem Statement:
Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Search Tree.

Input Format:
- First line contains integer N
- Second line contains N space-separated integers
- Third line contains two node values

Output Format:
- Print the LCA value

Example:
Input:
7
6 2 8 0 4 7 9
2 8

Output:
6
*/
#include <stdio.h>
#include <stdlib.h>

// Definition of Tree Node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Create new node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Insert into BST
struct TreeNode* insert(struct TreeNode* root, int val) {
    if (root == NULL)
        return newNode(val);

    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);

    return root;
}

// Find LCA in BST
int lowestCommonAncestor(struct TreeNode* root, int p, int q) {
    while (root != NULL) {
        if (p < root->val && q < root->val)
            root = root->left;
        else if (p > root->val && q > root->val)
            root = root->right;
        else
            return root->val;
    }
    return -1;
}

int main() {
    int N;
    scanf("%d", &N);

    struct TreeNode* root = NULL;
    int value;

    // Read BST nodes
    for (int i = 0; i < N; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    int p, q;
    scanf("%d %d", &p, &q);

    // Find and print LCA
    int lca = lowestCommonAncestor(root, p, q);
    printf("%d\n", lca);

    return 0;
}