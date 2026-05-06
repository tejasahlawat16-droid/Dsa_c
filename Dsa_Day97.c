/* Problem: Given meeting intervals, find minimum number of rooms required.
Sort by start time and use min-heap on end times.
*/
#include <stdio.h>
#include <stdlib.h>

// Structure for meeting interval
struct Meeting {
    int start;
    int end;
};

// Compare function for sorting by start time
int compare(const void *a, const void *b)
{
    struct Meeting *m1 = (struct Meeting *)a;
    struct Meeting *m2 = (struct Meeting *)b;
    return m1->start - m2->start;
}

// Min-Heap structure
struct MinHeap {
    int *arr;
    int size;
};

// Swap function
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up
void heapifyUp(struct MinHeap *heap, int i)
{
    while (i > 0 && heap->arr[(i - 1) / 2] > heap->arr[i])
    {
        swap(&heap->arr[(i - 1) / 2], &heap->arr[i]);
        i = (i - 1) / 2;
    }
}

// Heapify down
void heapifyDown(struct MinHeap *heap, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->arr[left] < heap->arr[smallest])
        smallest = left;

    if (right < heap->size && heap->arr[right] < heap->arr[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(&heap->arr[i], &heap->arr[smallest]);
        heapifyDown(heap, smallest);
    }
}

// Insert into min-heap
void insertHeap(struct MinHeap *heap, int value)
{
    heap->arr[heap->size] = value;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}

// Remove minimum element from heap
int extractMin(struct MinHeap *heap)
{
    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return root;
}

// Get minimum element
int getMin(struct MinHeap *heap)
{
    return heap->arr[0];
}

// Function to find minimum rooms required
int minMeetingRooms(struct Meeting meetings[], int n)
{
    if (n == 0)
        return 0;

    // Sort meetings by start time
    qsort(meetings, n, sizeof(struct Meeting), compare);

    // Create min-heap
    struct MinHeap heap;
    heap.arr = (int *)malloc(n * sizeof(int));
    heap.size = 0;

    // Add end time of first meeting
    insertHeap(&heap, meetings[0].end);

    for (int i = 1; i < n; i++)
    {
        // If room is free, reuse it
        if (meetings[i].start >= getMin(&heap))
            extractMin(&heap);

        // Add current meeting end time
        insertHeap(&heap, meetings[i].end);
    }

    return heap.size;
}

int main()
{
    int n;
    printf("Enter number of meetings: ");
    scanf("%d", &n);

    struct Meeting meetings[n];

    printf("Enter start and end times:\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d", &meetings[i].start, &meetings[i].end);

    printf("Minimum number of rooms required: %d\n",
           minMeetingRooms(meetings, n));

    return 0;
}