/* Problem: Build a graph with n vertices and m edges using adjacency matrix representation.
The graph may be directed or undirected.

Input:
- n (vertices)
- m (edges)
- m pairs (u, v)

Output:
- n x n adjacency matrix
*/
#include <stdio.h>

int main() {
    int n, m;
    int i, j;

    // Read number of vertices and edges
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &m);

    int adj[n][n];

    // Initialize adjacency matrix with 0
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }

    int u, v;
    int isDirected;

    // Ask graph type
    printf("Enter 1 for Directed graph, 0 for Undirected graph: ");
    scanf("%d", &isDirected);

    // Read edges
    printf("Enter the edges (u v):\n");
    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);

        adj[u][v] = 1;   // edge u -> v

        if (!isDirected) {
            adj[v][u] = 1; // edge v -> u for undirected graph
        }
    }

    // Print adjacency matrix
    printf("\nAdjacency Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    return 0;
}