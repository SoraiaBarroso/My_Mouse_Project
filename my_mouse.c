#include "my_mouse.h"

int main(int argc, char* argv[]) 
{
    Maze* maze;

    if (argc < 2) {
        write(2, ERR_INVALID_ARGV, strlen(ERR_INVALID_ARGV));
        exit(1);
    } else {         
        char *path = argv[1];
        
        // Get map size
        maze = GetMapInfo(path);

        InitMazeMap(maze);

        // Copy map
        maze = StoreMap(path, maze);
        
        // Run A* algorithm
        AStarAlgorithm(maze); 

        FreeMazeMap(maze);
    }

    return 0;
}