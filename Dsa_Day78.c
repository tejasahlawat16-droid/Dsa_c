/* Problem Statement
Given weighted undirected graph, compute total weight of Minimum Spanning Tree using Prim’s algorithm.

Input Format
n m
u v w
...

Output Format
Total weight of MST.

Sample Input
4 5
1 2 3
1 3 5
2 3 1
2 4 4
3 4 2

Sample Output
6

Explanation
One possible MST edges: (2-3), (3-4), (1-2)
*/
#include <stdio.h>
#include <limits.h>

#define MAX 100

int n;
int graph[MAX][MAX];
int selected[MAX];

int minKey(int key[]) {
    int min = INT_MAX, minIndex = -1;
    for (int v = 1; v <= n; v++) {
        if (!selected[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

int primMST() {
    int key[MAX];
    int parent[MAX];
    int totalWeight = 0;

    for (int i = 1; i <= n; i++) {
        key[i] = INT_MAX;
        selected[i] = 0;
    }

    key[1] = 0;
    parent[1] = -1;

    for (int count = 1; count < n; count++) {
        int u = minKey(key);
        selected[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (graph[u][v] &&
                !selected[v] &&
                graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        totalWeight += key[i];
    }

    return totalWeight;
}

int main() {
    int m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    printf("%d\n", primMST());
    return 0;
}