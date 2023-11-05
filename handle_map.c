#include "my_mouse.h"

void InitMazeMap(Maze* maze) 
{
    maze->map = malloc(sizeof(char *) * maze->size);
    maze->visited = malloc(maze->lines * sizeof(bool *));

    for (int i = 0; i < maze->lines; i++)
    {
        maze->map[i] = malloc(sizeof(char *) * maze->size);
        maze->visited[i] = malloc(maze->size * sizeof(bool));

        for (int j = 0; j < maze->cols; j++)
        {
            maze->visited[i][j] = false;
        }
    }
}

void FreeMazeMap(Maze* maze) 
{
    free(maze->map);
    free(maze->visited);
    free(maze);
}

Maze* GetMapInfo(char *path) 
{
    Maze* maze = malloc(sizeof(Maze));
    char* first_line = NULL;
    int index = 0, fd;

    if ((fd = open(path, O_RDONLY)) < 0) {
        write(2, PATH_ERROR, strlen(PATH_ERROR));
        exit(1); 
    }

    first_line = get_line(fd);

    // Lines
    while (first_line[index] >= '0' && first_line[index] <= '9') {
        maze->lines = maze->lines * 10 + (first_line[index] - '0');
        index++;
    }
    
    maze->lines = maze->lines + 1;
    index++;

    // Cols
    while (first_line[index] >= '0' && first_line[index] <= '9') {
        maze->cols = maze->cols * 10 + (first_line[index] - '0');
        index++;
    }
    
    // Store rest of information
    char rest_str[5];
    strncpy(rest_str, first_line + index, (strlen(first_line) - index));
    maze->full_ch = rest_str[0];
    maze->empty_ch = rest_str[1];
    maze->path_ch = rest_str[2];
    maze->enter_ch = rest_str[3];
    maze->exit_ch = rest_str[4];
    maze->size = maze->lines * maze->cols;

    free(first_line);
    close(fd);
    init_my_readline();
    return maze;
}

// Check map only contains indicated chars 
void CheckMapValidity(Maze* maze) 
{
    bool t_entry = false, t_exit = false;

    for (int x = 1; x < maze->lines; x++) {
        for (int y = 0; y < maze->cols; y++) {
            if (maze->map[x][y] == maze->enter_ch) {
                if (t_entry) {
                    write(2, MAP_ERROR, strlen(MAP_ERROR));
                    exit(1);
                } else {
                    t_entry = true;
                }
            } else if (maze->map[x][y] == maze->exit_ch) {
                if (t_exit) {
                    write(2, MAP_ERROR, strlen(MAP_ERROR));
                    exit(1);
                } else {
                    t_exit = true;
                }
            } else if (maze->map[x][y] == maze->empty_ch || maze->map[x][y] == maze->full_ch) {
                continue;
            } else {
                write(2, MAP_ERROR, strlen(MAP_ERROR));
                exit(1);
            }
        }
    }
}

Maze* StoreMap(char *path, Maze* maze) 
{
    char *map = NULL;
    int fd;

    if ((fd = open(path, O_RDONLY)) < 0) {
        write(2, PATH_ERROR, strlen(PATH_ERROR));
        exit(1);
    }

    for (int i = 0; i < maze->lines; i++)
    {
        map = get_line(fd);

        for (int j = 0; j < maze->cols; j++)
        {
            // Store map
            if(map[j] == maze->enter_ch) {
                maze->start = j;
            }
            if(map[j] == maze->exit_ch) {
                maze->target = j;
            } 

            maze->map[i][j] = map[j]; 
        }  
    }
    
    // Handle invalid map
    CheckMapValidity(maze);

    free(map);
    close(fd);
    return maze;   
}