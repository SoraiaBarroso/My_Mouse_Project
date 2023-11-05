# Welcome to My Mouse
***

## Task
This project is about finding the shortest path between entering and leaving a labyrinth while avoiding obstacles. The map file is giving as an argument of the program. <br>

```
10x10* o12$
***1******$
*       **$
* *  **  *$
*        *$
** ** ** *$
*       **$
*      ***$
**       *$
*        *$
***2******$
```

The map consist on a serie of characters that conform the labyrinth, this characters are present in the first line of the file: <br> 

[ 10x10* o12 ], the first numbers represent the number of rows and columns while the rest of the characters refresent the 'full' ch, 'empty' ch, 'path' char, 'start' char and 'exit' char. 
A map with different chars than the ones presented in the first line is considered as an invalid map. <br> 

The task of the program is to go through this labyrinth to find the shortes path from the start char to the exit char and printing this path in the map as shown below:

```
10x10* o12
***1******
*  o    **
* *o **  *
* oo     *
**o** ** *
* oo    **
*  o   ***
** o     *
*  o     *
***2******
10 STEPS!
```
## Description
To solve this problem I decided to use A* algorithm which is a graph traversal and path search algorithm, it is a best-first search,  starting from a specific starting node of a graph, it aims to find a path to the given goal node having the smallest cost (least distance travelled, shortest time, etc.). It does this by maintaining a tree of paths originating at the start node and extending those paths one edge at a time until its termination criterion is satisfied. <br>

At each iteration of its main loop, A* needs to determine which of its paths to extend, it does so based on the cost, to calculate this cost I decided to use 'Manhattan distance' which is a ways of measuring the distance between two points in a multi-dimensional space, is useful when we want to calculate the distance between two points in a grid-like path. <br>

Typical implementations of A* use a priority queue to perform the repeated selection of minimum (estimated) cost nodes to expand, each element in a priority queue has an associated priority, high priority are served before elements with low priority. <br>
To implement a priority queue I decided to use a Heap data structure (min heap), which is a specialized tree-based data structure that satisfies the heap property.<br>

After implementing everything the algorithm finds the shortest path from the start point to the end point, to print out the path I linked every node to it's parent node, so when the target node is found I could go back to it's parent node until I reach the start point to give me the path.


## Installation
There's no intallation run 'make' and start the program with desired map as an argument:

```
./my_mouse <map>
```

## Usage
```
./my_mouse <map>
```
### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
