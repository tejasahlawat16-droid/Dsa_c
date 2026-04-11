/* Problem: Print topological ordering of a Directed Acyclic Graph (DAG) using DFS.
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

// Stack structure
int stack[MAX];
int top = -1;

// Push to stack
void push(int v) {
    stack[++top] = v;
}

// Pop from stack
int pop() {
    return stack[top--];
}

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

// Add directed edge
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adj[src];
    graph->adj[src] = newNode;
}

// DFS utility function
void topoDFS(struct Graph* graph, int v, bool visited[]) {
    visited[v] = true;

    struct Node* temp = graph->adj[v];
    while (temp != NULL) {
        if (!visited[temp->data])
            topoDFS(graph, temp->data, visited);
        temp = temp->next;
    }

    push(v);
}

// Topological Sort
void topologicalSort(struct Graph* graph) {
    bool visited[MAX] = {false};

    for (int i = 0; i < graph->V; i++) {
        if (!visited[i])
            topoDFS(graph, i, visited);
    }

    printf("Topological Order: ");
    while (top != -1)
        printf("%d ", pop());
    printf("\n");
}

// Main function
int main() {
    int V = 6;
    struct Graph* graph = createGraph(V);

    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    topologicalSort(graph);

    return 0;
}