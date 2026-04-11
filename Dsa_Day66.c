/* Problem: Detect cycle in directed graph using DFS and recursion stack.

Output:
- YES if cycle exists
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// Adjacency list node
struct Node {
    int data;
    struct Node* next;
};

// Graph structure
struct Graph {
    int V;
    struct Node* adj[MAX];
};

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Create graph
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    for (int i = 0; i < V; i++)
        graph->adj[i] = NULL;
    return graph;
}

// Add edge (directed)
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adj[src];
    graph->adj[src] = newNode;
}

// DFS utility function
bool dfsCycle(struct Graph* graph, int v, bool visited[], bool recStack[]) {
    if (!visited[v]) {
        visited[v] = true;
        recStack[v] = true;

        struct Node* temp = graph->adj[v];
        while (temp != NULL) {
            int adjNode = temp->data;

            if (!visited[adjNode] && dfsCycle(graph, adjNode, visited, recStack))
                return true;

            else if (recStack[adjNode])
                return true;

            temp = temp->next;
        }
    }

    recStack[v] = false;
    return false;
}

// Cycle detection function
bool isCyclic(struct Graph* graph) {
    bool visited[MAX] = {false};
    bool recStack[MAX] = {false};

    for (int i = 0; i < graph->V; i++) {
        if (dfsCycle(graph, i, visited, recStack))
            return true;
    }
    return false;
}

// Main function
int main() {
    int V = 4;
    struct Graph* graph = createGraph(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);  // Cycle here

    if (isCyclic(graph))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}