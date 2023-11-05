#include "my_mouse.h"

void PrintSolution(Maze* maze, MinHeapNode* target_node) 
{
    int steps = 0;

    while (target_node->parent != NULL) {
        int x = target_node->x_pos;
        int y = target_node->y_pos;
        // skip entrance 
        if (x == 1 && y == maze->start) continue;
        else {
            maze->map[x][y] = 'o';
            target_node = target_node->parent;
            steps++;
        }
    }

    for (int x = 0; x < maze->lines; x++) {
        for (int y = 0; y < maze->cols; y++) {
            printf("%c", maze->map[x][y]);  
        }
        printf("\n");
    }

    printf("%d STEPS!\n", steps);
}

// Calculate cost 
int HeuristicCalculation(int current_x, int current_y, int goal_x, int goal_y) 
{
    int dx = abs(current_x - goal_x);
    int dy = abs(current_y - goal_y);
  
    return dx + dy;
}

int AStarAlgorithm(Maze* maze) 
{    
    // Init priority queue 
    MinHeap* priority_queue = CreateMinHeap(maze->size);

    // Start node at the entrance of the maze
    MinHeapNode* root_node = CreateNode(1, maze->start, 0, NULL);
    maze->visited[root_node->x_pos][root_node->y_pos] = true;

    MinHeapNode* target_node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
  
    // Add starting node to list 
    InsertNode(priority_queue, root_node);
    
    // While the list is not empty
    while (priority_queue->size > 0) {

        // Pop the lowest priority node 
        MinHeapNode* current_node = ExtractMin(priority_queue);
        
        // Check if it is the goal 
        if (current_node->x_pos == maze->lines - 1 && current_node->y_pos == maze->target) {   
            target_node = current_node;  
            target_node = target_node->parent; 
            PrintSolution(maze, target_node);
            break;           
        }

        //  up> left> right> down
        int dx[] = {-1, 0, 0, 1};
        int dy[] = {0, -1, 1, 0};

        // Else expand node
        for (int i = 0; i < 4; i++) {

            int new_x = current_node->x_pos + dx[i];
            int new_y = current_node->y_pos + dy[i];
 
            // Check if the new position is within the maze boundaries
            if (new_x >= 1 && new_x < maze->lines && new_y >= 1 && new_y < maze->cols) {
                // Check if the new position is not an obstacle and hasn't been visited            
                if (maze->map[new_x][new_y] != '*' && maze->visited[new_x][new_y] == false) {

                    int g_value = current_node->cost + 1;
                    int h_value = HeuristicCalculation(new_x, new_y, maze->lines - 1, maze->target);
                    int f_value = g_value + h_value;

                    maze->visited[new_x][new_y] = true;
                    MinHeapNode* neighbor = CreateNode(new_x, new_y, f_value, current_node);
                    InsertNode(priority_queue, neighbor);
                } 
            }
        }
    }

    if (priority_queue->size <= 0) {
        write(2, MAP_ERROR, strlen(MAP_ERROR));
        exit(1);
    }

    FreeMinHeap(priority_queue);
    return 0;
}