/* Problem: Implement topological sorting using in-degree array and queue (Kahnâ€™s Algorithm).
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Adjacency list node
struct Node {
    int data;
    struct Node* next;
};

struct Node* adj[MAX];
int indegree[MAX];
int queue[MAX];
int front = 0, rear = -1;

// Create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Enqueue
void enqueue(int value) {
    queue[++rear] = value;
}

// Dequeue
int dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front > rear;
}

int main() {
    int V, E;
    int u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    // Initialize adjacency list and indegree
    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
        indegree[i] = 0;
    }

    printf("Enter edges (u v) where u -> v:\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);

        struct Node* newNode = createNode(v);
        newNode->next = adj[u];
        adj[u] = newNode;

        indegree[v]++;
    }

    // Add vertices with indegree 0 to queue
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            enqueue(i);
        }
    }

    int count = 0;
    printf("Topological Order:\n");

    while (!isEmpty()) {
        int current = dequeue();
        printf("%d ", current);
        count++;

        struct Node* temp = adj[current];
        while (temp != NULL) {
            indegree[temp->data]--;
            if (indegree[temp->data] == 0) {
                enqueue(temp->data);
            }
            temp = temp->next;
        }
    }

    if (count != V) {
        printf("\nCycle detected! Topological sort not possible.\n");
    }

    return 0;
}