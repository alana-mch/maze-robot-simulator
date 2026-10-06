# maze-robot-simulator
A C‑based simulation of a robot navigating a randomly generated grid, collecting markers, avoiding obstacles, and returning home using classic search algorithms. The program outputs drawing commands that are visualised using drawapp-4.5.jar.

## Features
### Grid Generation
Creates a grid with a random width and height between 8 and 20 tiles.  
Draws a border around the grid.
Randomly places:
- Markers (circles)
- Obstacles (squares)

### Depth‑First Search (DFS) Exploration
Robot performs DFS to visit every reachable tile.  
Moves physically to each tile in DFS order.  
Collects markers automatically when visiting a tile containing one.

### Breadth‑First Search (BFS) Return Path  
After all tiles are visited and markers collected, the robot uses BFS to compute the shortest path back to the top‑left corner.  
Robot follows the BFS path step‑by‑step to return home.

## Requirements
gcc (GNU C Compiler)  
Java Runtime Environment (to run drawapp)  
drawapp-4.5.jar (external visualisation tool)  
Standard C libraries only (no external dependencies)

## Compile
gcc -o Robot SourceCode.c graphics.c drawingFunctions.c

## Run
./Robot | java -jar drawapp-4.5.jar
