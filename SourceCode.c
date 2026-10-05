#include <stdlib.h>
#include <time.h>
#include "graphics.h"
#include "drawingFunctions.h"



const int MAX_NUMBER_OF_ITEMS = 20;
const int MIN_NUMBER_OF_ITEMS = 1;
const int MAX_SCREEN_SIZE = 20;
const int MIN_SCREEN_SIZE = 8;
const int MAX_QUEUE_SIZE = 50;
const int MAX_PATH_SIZE = 40;



int getRandomNumber(int min, int max)
{
    int number = rand() % (max - min + 1) + min;
    return number;
}


//ARRAYS



int** allocateArray(int widthInTiles, int heightInTiles)
{
    //Allocates space for a 2d array which is an array of rows
    int **arenaArray = malloc(heightInTiles * sizeof(int * ));
    for(int count = 0; count < heightInTiles; count++)
    {
        arenaArray[count] = malloc(widthInTiles * sizeof(int));
    }
    return arenaArray;
}

void fillArray(int **arenaArray, int widthInTiles, int heightInTiles, int value)
{
    //fills every space with a value
    for (int y = 0; y < heightInTiles; y++)
    {
        for (int x = 0; x < widthInTiles; x++)
        {
            arenaArray[y][x] = value;
        }
    }
}

int ** setUpArray(int widthInTiles, int heightInTiles, int value)
{
    //allocates space for an array and fills it
    int **array = allocateArray(widthInTiles, heightInTiles);
    fillArray(array, widthInTiles, heightInTiles, value);
    return array;
}



//ARENA SET UP

void makeObstacles(int **arenaArray, int widthInTiles, int heightInTiles)
{
    //generates a random number of obstacles in random positions that arent corneres and sets that position in the array to indicate an obstacle and draws the obstacle
    setColour(gray);
    for (int obstacles = 0; obstacles < getRandomNumber(MIN_NUMBER_OF_ITEMS, MAX_NUMBER_OF_ITEMS); obstacles++)
    {
        int x = getRandomNumber(0, widthInTiles-1);
        int y = getRandomNumber(0, heightInTiles-1);
        while ((arenaArray[y][x] != EMPTY) && ((x == 0 && y == 0) || (x == 0 && y == heightInTiles) || (x == widthInTiles && y == 0) || (x == widthInTiles && y == heightInTiles)))
        {
            int x = getRandomNumber(0, widthInTiles-1);
            int y = getRandomNumber(0, heightInTiles-1);
        }
        arenaArray[y][x] = OBSTACLE;
        drawObstacle(x,y);
    }
}

void makeMarkers(int **arenaArray, int widthInTiles, int heightInTiles)
{
    //for a random number of markers sets the markers to a random position and indicates that position in the arena array is a marker
    for (int markers = 0; markers < getRandomNumber(MIN_NUMBER_OF_ITEMS, MAX_NUMBER_OF_ITEMS); markers++)
    {
        int x = getRandomNumber(0, widthInTiles-1);
        int y = getRandomNumber(0, heightInTiles-1);
        while (arenaArray[y][x] != EMPTY)
        {
            x = getRandomNumber(0, widthInTiles-1);
            y = getRandomNumber(0, heightInTiles-1);
        }
        arenaArray[y][x] = MARKER;
    }
}

void createArena(int **arenaArray, int widthInTiles, int heightInTiles)
{
    //fills the arena array initially and fills with markers and obstacles
    fillArray(arenaArray, widthInTiles, heightInTiles, EMPTY);
    makeObstacles(arenaArray, widthInTiles, heightInTiles);
    makeMarkers(arenaArray, widthInTiles, heightInTiles);
    drawMarkers(arenaArray, widthInTiles, heightInTiles);
}



//ROBOT IMPLEMENTATION

struct robot
{
    int x;
    int y;
    int direction;
    int markersCarrying;
};

void moveRobotUp(struct robot robot, int **arenaArray, int widthInTiles, int heightInTiles)
{
    //if robot direction is north moving forward will decrease the robots y position
    int Xposition = robot.x*TILE_SIZE;
    int Yposition = robot.y*TILE_SIZE;
    for (int count = 0; count < TILE_SIZE; count++)
    {
        Yposition--;
        updateArena(Xposition, Yposition, robot.direction, arenaArray, widthInTiles, heightInTiles);
    }
}

void moveRobotDown(struct robot robot, int **arenaArray, int widthInTiles, int heightInTiles)
{
    //if robot direction is south moving forward will increase the robots y position
    int Xposition = robot.x*TILE_SIZE;
    int Yposition = robot.y*TILE_SIZE;
    for (int count = 0; count < TILE_SIZE; count++)
    {
        Yposition++;
        updateArena(Xposition, Yposition, robot.direction, arenaArray, widthInTiles, heightInTiles);
    }
}

void moveRobotLeft(struct robot robot, int **arenaArray, int widthInTiles, int heightInTiles)
//if robot direction is west moving forward will decrease the robots x position
{
    int Xposition = robot.x*TILE_SIZE;
    int Yposition = robot.y*TILE_SIZE;
    for (int count = 0; count < TILE_SIZE; count++)
    {
        Xposition--;
        updateArena(Xposition, Yposition, robot.direction, arenaArray, widthInTiles, heightInTiles);
    }
}

void moveRobotRight(struct robot robot, int **arenaArray, int widthInTiles, int heightInTiles)
//if robot direction is east moving forward will increase the robots x position
{
    int Xposition = robot.x*TILE_SIZE;
    int Yposition = robot.y*TILE_SIZE;
    for (int count = 0; count < TILE_SIZE; count++)
    {
        Xposition++;
        updateArena(Xposition, Yposition, robot.direction, arenaArray, widthInTiles, heightInTiles);
    }
}

int canMoveForward(int x, int y, int direction, int **arenaArray, int widthInTiles, int heightInTiles)
//depending on direction passed in it checks the tile next to it to see if it is an obstacle or if the current tile is next to the border the direction faces to
{
    if (direction == NORTH && y != 0 && arenaArray[y-1][x] != OBSTACLE)return 1;
    if (direction == EAST && x != (widthInTiles-1) && arenaArray[y][x+1] != OBSTACLE)return 1;
    if (direction == SOUTH && y != (heightInTiles-1) && arenaArray[y+1][x] != OBSTACLE)return 1;
    if (direction == WEST && x != 0 && arenaArray[y][x-1] != OBSTACLE)return 1; 
    return 0;
}

struct robot forward(struct robot robot, int **arenaArray, int widthInTiles, int heightInTiles)
{
    //calls which direction to move the robot for forward
    if (robot.direction == NORTH)
    {
        moveRobotUp(robot, arenaArray, widthInTiles, heightInTiles);
        robot.y--;
    }
    if (robot.direction == EAST)
    {
        moveRobotRight(robot, arenaArray, widthInTiles, heightInTiles);
        robot.x++;
    }
    if (robot.direction == SOUTH)
    {
        moveRobotDown(robot, arenaArray, widthInTiles, heightInTiles);
        robot.y++;
    }
    if (robot.direction == WEST)
    {
        moveRobotLeft(robot, arenaArray, widthInTiles, heightInTiles);
        robot.x--;
    }
    return robot; 
}

struct robot left(struct robot robot, int **arenaArray, int widthInTiles, int heightInTiles)
{
    //turns robot left and updates drawing
    int Xposition = robot.x*TILE_SIZE;
    int Yposition = robot.y*TILE_SIZE;
    if (robot.direction == NORTH)
    {
        robot.direction = WEST;
    }
    else
    {
        robot.direction--;
    }
    updateArena(Xposition, Yposition, robot.direction, arenaArray, widthInTiles, heightInTiles); 
    sleep(TURN_WAIT_TIME);
    return robot;
}

struct robot right(struct robot robot, int **arenaArray, int widthInTiles, int heightInTiles)
{
    //turnsrobot right and updates the drawing
    int Xposition = robot.x*TILE_SIZE;
    int Yposition = robot.y*TILE_SIZE;
    robot.direction = (robot.direction+1) % 4;
    updateArena(Xposition, Yposition, robot.direction, arenaArray, widthInTiles, heightInTiles);
    sleep(TURN_WAIT_TIME);
    return robot;
}

struct robot turnToNewDirection(struct robot robot, int newDirection, int **arenaArray, int widthInTiles, int heightInTiles)
{
    //turns robot right until it faces the direction passed in as newDirection
    while (robot.direction != newDirection)
    {
        robot = right(robot, arenaArray, widthInTiles, heightInTiles);
    }
    return robot;
}

struct robot backtrack(struct robot robot, int direction, int **arenaArray, int widthInTiles, int heightInTiles)
{
    //used in depth first search to return down the path it has fully explored
    robot = left(robot, arenaArray, widthInTiles, heightInTiles);
    robot = left(robot, arenaArray, widthInTiles, heightInTiles);
    robot = forward(robot, arenaArray, widthInTiles, heightInTiles);
    robot = turnToNewDirection(robot, direction, arenaArray, widthInTiles, heightInTiles);
    return robot;
}


//MARKERS


void pickUpMarker(struct robot robot, int **arenaArray, int widthInTiles, int heightInTiles)
{
    //checks if the robot is on a marker and increases markersCarrying and sets the tile to empty
    int Xposition = robot.x * TILE_SIZE;
    int Yposition = robot.y * TILE_SIZE;
    robot.markersCarrying++;
    arenaArray[robot.y][robot.x] = EMPTY;
    updateArena(Xposition, Yposition, robot.direction, arenaArray, widthInTiles, heightInTiles);
}

void dropMarker(struct robot robot, int **arenaArray, int widthInTiles, int heightInTiles)
{
    //called once robot has visited every tile and gone to a corner and drops all the markers and updates the arena to show they are dropped there
    int Xposition = robot.x * TILE_SIZE;
    int Yposition = robot.y * TILE_SIZE;
    robot.markersCarrying = 0;
    arenaArray[robot.y][robot.x] = MARKER;
    updateArena(Xposition, Yposition, robot.direction, arenaArray, widthInTiles, heightInTiles);
}

int markerCount(struct robot robot)
{
    return robot.markersCarrying;
}



//ARENA EXPLORATION


int checkNeighbourNotVisited(int x, int y, int direction, int **visited, int widthInTiles, int heightInTiles)
{
    //checks if the neighbour currently being checked has already been visited
    if (direction == NORTH && y != 0 && visited[y-1][x] != 1)return 1;
    if (direction == EAST && x != (widthInTiles-1) && visited[y][x+1] != 1)return 1;
    if (direction == SOUTH && y != (heightInTiles-1) && visited[y+1][x] != 1)return 1;
    if (direction == WEST && x != 0 && visited[y][x-1] != 1)return 1; 
    return 0;
}

struct robot depthFirstSearch(struct robot robot, int **arenaArray, int **visited, int widthInTiles, int heightInTiles)
//called to traverse the whole grid to ensure all markers are picked up
{
    //visits start tile
    int currentX = robot.x;
    int currentY = robot.y;
    int currentDirection = robot.direction;
    visited[currentY][currentX] = 1;
    
    //for each direction/ each neighbour
    for (int direction = 0; direction < 4; direction++)
    {
        int newDirection = (currentDirection + direction) % 4;
        //if that neighbour is accesible(not obstacle or boundary) and not visited then go to that neighbour 
        if (canMoveForward(robot.x, robot.y, newDirection, arenaArray, widthInTiles, heightInTiles) == 1 && checkNeighbourNotVisited(robot.x, robot.y, newDirection, visited, widthInTiles, heightInTiles) == 1 )
        {
            robot = turnToNewDirection(robot, newDirection, arenaArray, widthInTiles, heightInTiles);
            robot = forward(robot, arenaArray, widthInTiles, heightInTiles);
            //if it is a marker pick up the marker
            if (arenaArray[robot.y][robot.x] == MARKER)
            {
                pickUpMarker(robot, arenaArray, widthInTiles, heightInTiles);
            }

            //recursively checks neighbours for every tile
            depthFirstSearch(robot, arenaArray, visited, widthInTiles, heightInTiles);

            //goes back to previous tile and checks its next neighbour
            robot = backtrack(robot, direction, arenaArray, widthInTiles, heightInTiles);
        }
    }
    return robot;
    
    
}

struct robot followPath(struct robot robot, int *pathX, int *pathY, int pathLength, int **arenaArray, int widthInTiles, int heightInTiles)
{
    //draws the robot following the path generated by the breadth first search 
    robot.x = pathX[pathLength-1];
    robot.y = pathY[pathLength-1];
    for(int position = pathLength-1; position >= 0 ; position--)
    {
        if (pathX[position] > robot.x)
        {
            robot = turnToNewDirection(robot, EAST, arenaArray, widthInTiles, heightInTiles);
            robot = forward(robot, arenaArray, widthInTiles, heightInTiles);
        }
        else if (pathX[position] < robot.x)
        {
            robot = turnToNewDirection(robot, WEST, arenaArray, widthInTiles, heightInTiles);
            robot = forward(robot, arenaArray, widthInTiles, heightInTiles);
        }
        else if (pathY[position] > robot.y)
        {
            robot = turnToNewDirection(robot, SOUTH, arenaArray, widthInTiles, heightInTiles);
            robot = forward(robot, arenaArray, widthInTiles, heightInTiles);
        }
        else if (pathY[position] < robot.y)
        {
            robot = turnToNewDirection(robot, NORTH, arenaArray, widthInTiles, heightInTiles);
            robot = forward(robot, arenaArray, widthInTiles, heightInTiles);
        }
    }
    //drops marker once end of path has reached which is a corner
    dropMarker(robot, arenaArray, widthInTiles, heightInTiles);
    return robot;
}

struct robot breadthFirstSearch(struct robot robot, int startX, int startY, int targetX, int targetY, int **arenaArray, int widthInTiles, int heightInTiles)
{
    //make visited list and list of parent nodes x and y coordinates
    int **visited = setUpArray(widthInTiles, heightInTiles, 0);
    int **parentX = setUpArray(widthInTiles, heightInTiles, -1);
    int **parentY = setUpArray(widthInTiles, heightInTiles, -1);

    //set up array that will keep nodes for the path
    int pathX[MAX_PATH_SIZE];
    int pathY[MAX_PATH_SIZE];

    //set up the queue for x and y
    int queueX[MAX_QUEUE_SIZE];
    int queueY[MAX_QUEUE_SIZE];
    int head = 0;
    int tail = 0;
    queueX[tail] = startX;
    queueY[tail] = startY;
    tail++;

    //visit first node
    visited[startY][startX] = 1;

    //while there are still tiles in the queue
    while(head<tail)
    {
        int x = queueX[head];
        int y = queueY[head];
        head++;

        //if current tile is the target tile then add the tile to the path and then go through all the parents and add them to the path
        if (x == targetX && y == targetY)
        {
            int len = 0;
            while (x != -1 && y != -1) 
            {
                pathX[len] = x;
                pathY[len] = y;
                int tempX = parentX[y][x];
                int tempY = parentY[y][x];
                x = tempX;
                y = tempY;
                len++;
            }
            robot = followPath(robot, pathX, pathY, len, arenaArray, widthInTiles, heightInTiles);
            return robot;
        }

        //for each direction if the neighbour is an available space and has not been visited add the neighbour to visited, the current x and y is the neighbours parent node and add the neighbour to the queue
        for (int direction = 0; direction < 4; direction++)
        {
            if (canMoveForward(x, y, direction, arenaArray, widthInTiles, heightInTiles) == 1 && checkNeighbourNotVisited(x, y, direction, visited, widthInTiles, heightInTiles) == 1 )
            {
                int nx=x;
                int ny=y;
                if (direction == NORTH)ny = y-1;
                if (direction == EAST)nx = x+1;
                if (direction == SOUTH)ny = y+1;
                if (direction == WEST)nx = x-1;
           
                visited[ny][nx] = 1;
                parentX[ny][nx] = x;
                parentY[ny][nx] = y;
                queueX[tail] = nx;
                queueY[tail] = ny;
                tail++;
            }
        }
    }
    return robot;
}



//MAIN PROGRAM

struct robot setUpRobot(int **arenaArray, int widthInTiles, int heightInTiles)
{
    //makes robot with a random start position and direction and initial markers carrying is 0 and then draws the robot
    struct robot robot;

    robot.x = getRandomNumber(0, widthInTiles-1);
    robot.y = getRandomNumber(0, heightInTiles-1);
    while (arenaArray[robot.y][robot.x] != EMPTY)
    {
        robot.x = getRandomNumber(0, widthInTiles-1);
        robot.y = getRandomNumber(0, heightInTiles-1);
    }

    robot.direction = rand() % 4;
    robot.markersCarrying = 0;

    foreground();
    drawRobot(robot.x*TILE_SIZE, robot.y*TILE_SIZE, robot.direction);
    return robot;
}

int ** setUpArena(int widthInTiles, int heightInTiles)
{
    //allocates memory for arena array and draws background then create arena adds obstacles and markers
    int **arenaArray = allocateArray(widthInTiles, heightInTiles);
    drawArena(widthInTiles, heightInTiles);
    createArena(arenaArray, widthInTiles, heightInTiles);
    return arenaArray;
}

int main(void)
{
    //sets start point for random function based on time so that the random numbers generated are different everytime the program is run
    srand(time(NULL));

    //sets arena size, makes arena array and sets up robot
    int widthInTiles = getRandomNumber(MIN_SCREEN_SIZE, MAX_SCREEN_SIZE);
    int heightInTiles = getRandomNumber(MIN_SCREEN_SIZE, MAX_SCREEN_SIZE);
    
    int **arenaArray = setUpArena(widthInTiles, heightInTiles);
    struct robot robot = setUpRobot(arenaArray, widthInTiles, heightInTiles);

    //make visited array for the depth first search which will make the robot visit all the tiles
    int **visited = setUpArray(widthInTiles, heightInTiles, 0);
    robot = depthFirstSearch(robot, arenaArray, visited, widthInTiles, heightInTiles);
    
    //once robot has visited all tiles, calls breadth first search to find a path to closest corner
    if (robot.x > widthInTiles/2 && robot.y > heightInTiles/2)
    {
        robot = breadthFirstSearch(robot, robot.x, robot.y, widthInTiles-1, heightInTiles-1, arenaArray, widthInTiles, heightInTiles);
    }
    else if (robot.x > widthInTiles/2 && robot.y < heightInTiles/2)
    {
        robot = breadthFirstSearch(robot, robot.x, robot.y, widthInTiles -1, 0, arenaArray, widthInTiles, heightInTiles);
    }
    else if (robot.x < widthInTiles/2 && robot.y > heightInTiles/2)
    {
        robot = breadthFirstSearch(robot, robot.x, robot.y, 0, heightInTiles-1, arenaArray, widthInTiles, heightInTiles);
    }
    else
    {
        robot = breadthFirstSearch(robot, robot.x, robot.y, 0, 0, arenaArray, widthInTiles, heightInTiles);
    }
       
    
    return 0;
}