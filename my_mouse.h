#ifndef MY_MOUSE_H
#define MY_MOUSE_H

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <stdbool.h>

    #define MAX_LINE 1024
    #define MAP_ERROR "MAP ERROR"
    #define PATH_ERROR "Error: invalid map filename or path\n"
    #define ERR_INVALID_ARGV "Error: invalid arguments\n"
    
    typedef struct MazeInfo {
        char **map;
        bool **visited;
        int lines, cols;
        int start, target;
        char enter_ch, exit_ch;
        char full_ch, empty_ch, path_ch;
        int size;
    } Maze;
    
    // Node
    typedef struct MinHeapNode {
        int x_pos; 
        int y_pos; 
        int cost;  
        struct MinHeapNode* parent; // Reference to the parent node
    } MinHeapNode;

    // Implementation binary heap / min heap 
    typedef struct MinHeap {
        struct MinHeapNode* array;  
        int capacity;           
        int size;              
    } MinHeap;

    /* MAZE HANDLING */ 
    void InitMazeMap(Maze* maze);
    void FreeMazeMap(Maze* maze); 
    Maze* GetMapInfo(char *path);
    Maze* StoreMap(char *path, Maze* maze); 
    void CheckMapValidity(Maze* maze);

    /* READLINE */
    char *get_line(int fd);
    void init_my_readline();

    /* A* ALGORITHM */
    int AStarAlgorithm(Maze* maze);
    void PrintSolution(Maze* maze, MinHeapNode* target_node); 

    /* BINARY HEAP IMPLEMENTATION */
    MinHeap* CreateMinHeap(int capacity);
    void FreeMinHeap(MinHeap* list);
    MinHeapNode* CreateNode(int x, int y, int cost, MinHeapNode* parent);
    void Swap(MinHeapNode *a, MinHeapNode *b);
    void InsertHelper(MinHeap* list, int index);
    void InsertNode(MinHeap* list, MinHeapNode* node);
    void MinHeapify(MinHeap* list, int index);
    MinHeapNode* ExtractMin(MinHeap* list);
    int HeuristicCalculation(int current_x, int current_y, int goal_x, int goal_y);
#endif