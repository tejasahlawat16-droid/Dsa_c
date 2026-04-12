/* Problem: Given weighted graph with non-negative edges, compute shortest path from source using priority queue.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

// ---------- Adjacency List ----------
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct Node* adj[MAX];

// ---------- Min Heap ----------
struct MinHeapNode {
    int vertex;
    int dist;
};

struct MinHeap {
    int size;
    struct MinHeapNode heap[MAX];
};

struct MinHeap pq;

// ---------- Create adjacency node ----------
struct Node* createNode(int v, int w) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}

// ---------- Swap heap nodes ----------
void swap(struct MinHeapNode* a, struct MinHeapNode* b) {
    struct MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// ---------- Min Heap Functions ----------
void heapifyUp(int index) {
    while (index > 0 && pq.heap[(index - 1) / 2].dist > pq.heap[index].dist) {
        swap(&pq.heap[index], &pq.heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void heapifyDown(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq.size && pq.heap[left].dist < pq.heap[smallest].dist)
        smallest = left;

    if (right < pq.size && pq.heap[right].dist < pq.heap[smallest].dist)
        smallest = right;

    if (smallest != index) {
        swap(&pq.heap[index], &pq.heap[smallest]);
        heapifyDown(smallest);
    }
}

void push(int v, int dist) {
    pq.heap[pq.size].vertex = v;
    pq.heap[pq.size].dist = dist;
    heapifyUp(pq.size);
    pq.size++;
}

struct MinHeapNode pop() {
    struct MinHeapNode root = pq.heap[0];
    pq.heap[0] = pq.heap[pq.size - 1];
    pq.size--;
    heapifyDown(0);
    return root;
}

int isEmpty() {
    return pq.size == 0;
}

// ---------- Dijkstra ----------
void dijkstra(int V, int src) {
    int dist[MAX];
    int visited[MAX] = {0};

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;
    pq.size = 0;
    push(src, 0);

    while (!isEmpty()) {
        struct MinHeapNode minNode = pop();
        int u = minNode.vertex;

        if (visited[u])
            continue;

        visited[u] = 1;

        struct Node* temp = adj[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int w = temp->weight;

            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                push(v, dist[v]);
            }
            temp = temp->next;
        }
    }

    printf("\nShortest distances from source %d:\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("Vertex %d : INF\n", i);
        else
            printf("Vertex %d : %d\n", i, dist[i]);
    }
}

// ---------- Main ----------
int main() {
    int V, E, u, v, w, src;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    for (int i = 0; i < V; i++)
        adj[i] = NULL;

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &u, &v, &w);

        struct Node* newNode = createNode(v, w);
        newNode->next = adj[u];
        adj[u] = newNode;

        // For undirected graph, uncomment below
        // struct Node* newNode2 = createNode(u, w);
        // newNode2->next = adj[v];
        // adj[v] = newNode2;
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(V, src);

    return 0;
}