#include "my_mouse.h"

// Create priority queue
MinHeap* CreateMinHeap(int capacity)
{
    MinHeap* priority_queue = (MinHeap*)malloc(sizeof(MinHeap));
    priority_queue->array = (MinHeapNode*)malloc(sizeof(MinHeapNode) * capacity); // sizeo of struct node * capacity
    priority_queue->capacity = capacity;
    priority_queue->size = 0;
    return priority_queue;
}

void FreeMinHeap(MinHeap* list) 
{
    free(list->array);
    free(list);
}

// Create node
MinHeapNode* CreateNode(int x, int y, int cost, MinHeapNode* parent) 
{
    MinHeapNode* new_node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    new_node->x_pos = x;
    new_node->y_pos = y;
    new_node->cost = cost;
    new_node->parent = parent;
    return new_node;
}

// Swap helper
void Swap(MinHeapNode *a, MinHeapNode *b) 
{
    MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Swap nodes by cost
void InsertHelper(MinHeap* list, int index)
{
    int parent = (index - 1) / 2;

    // Swapping by cost
    if (index > 0 && list->array[parent].cost > list->array[index].cost) {
        Swap(&list->array[parent], &list->array[index]); 
        InsertHelper(list, parent);
    }  
}

// Add node to list
void InsertNode(MinHeap* list, MinHeapNode* node) 
{
    if (list->size >= list->capacity) {
        printf("ERROR: HEAP OVER\n");
        exit(1);
    } else {    
        list->array[list->size] = *node;
        InsertHelper(list, list->size);
        list->size++;
    } 
}

// Main function in building a heap
void MinHeapify(MinHeap* list, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;

    if (left < list->size && list->array[left].cost < list->array[min].cost) {
        min = left;
    }
    if (right < list->size && list->array[right].cost < list->array[min].cost) {
        min = right;
    }
    if (min != index)
    {
        Swap(&list->array[index], &list->array[min]);
        MinHeapify(list, min);
    }
}

// Extract node with lowest cost 
MinHeapNode* ExtractMin(MinHeap* list) 
{
    MinHeapNode* delete_item = (MinHeapNode*)malloc(sizeof(MinHeapNode));
 
    if (list->size == 0) {
        printf("List is empty.\n");
        exit(1);
    }    

    *delete_item = list->array[0];

    // Replace the deleted node with the last node
    list->array[0] = list->array[list->size - 1];
    list->size--;
 
    // Call minheapify to maintain the heap property
    MinHeapify(list, 0);
    return delete_item;
}