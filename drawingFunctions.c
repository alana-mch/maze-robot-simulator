#include "graphics.h"
#include "drawingFunctions.h"
#include "robotFunctions.h"


void drawMarkers(int **arenaArray, int widthInTiles, int heightInTiles)
{
    //loops through every item in the array and if it is a marker it draws a marker on that tile
    foreground();
    setColour(red);
    for (int y = 0; y < heightInTiles; y++)
    {
        for (int x = 0; x < widthInTiles; x++)
        {
            if (arenaArray[y][x] == MARKER)
            {
                int difference = TILE_SIZE - ITEM_SIZE;
                fillOval(x*TILE_SIZE + difference/2 + BORDER_WIDTH, y*TILE_SIZE + difference/2 + BORDER_WIDTH, ITEM_SIZE, ITEM_SIZE);
            }
        }
    }
    
}

void drawObstacle(int x, int y)
{
    //draw rectangle on tile represented by x and y
    int difference = TILE_SIZE - ITEM_SIZE;
    fillRect(x*TILE_SIZE + difference/2 + BORDER_WIDTH, y*TILE_SIZE + difference/2 + BORDER_WIDTH, ITEM_SIZE, ITEM_SIZE);
}

void drawBorder(int width, int height)
{
    //draw outer larger square then smaller inner square of different colour to create the border
    setColour(orange);
    fillRect(0, 0, width + BORDER_WIDTH*2, height + BORDER_WIDTH*2);
    setColour(lightgray);
    fillRect(BORDER_WIDTH, BORDER_WIDTH, width, height);
}

void drawGrid(int width, int height)
{
    //for every width and every height that was randomly generated it draws a line to create the grid
    setColour(black);
    for (int w=0; w<width; w++)
    {
        drawLine(BORDER_WIDTH + TILE_SIZE*w, BORDER_WIDTH, BORDER_WIDTH + TILE_SIZE*w, height + BORDER_WIDTH);
    }
    for (int h=0; h<height; h++)
    {
        drawLine(BORDER_WIDTH, BORDER_WIDTH + h*TILE_SIZE , BORDER_WIDTH + width, BORDER_WIDTH + h*TILE_SIZE);
    }
}

void drawBackground(int width, int height)
{
    background();
    drawBorder(width, height);
    drawGrid(width, height);
}

void drawArena(int widthInTiles, int heightInTiles)
{
    //set the size of the window to the size of the grid and then draws the background
    int width = widthInTiles * TILE_SIZE;
    int height = heightInTiles * TILE_SIZE;
    
    setWindowSize(width + BORDER_WIDTH*2, height + BORDER_WIDTH*2);
    drawBackground(width, height);
    
}

void drawRobot(int x, int y, int direction)
{
    foreground();
    setColour(green);
    if (direction == NORTH)
    {
        fillOval(x + BORDER_WIDTH + TILE_SIZE/4, y + BORDER_WIDTH, TILE_SIZE/2, TILE_SIZE);
        setColour(blue);
        fillOval(x + TILE_SIZE/2 + BORDER_WIDTH - EYE_SIZE, y + BORDER_WIDTH + EYE_SIZE*2, EYE_SIZE, EYE_SIZE);
        fillOval((x+TILE_SIZE) - TILE_SIZE/2 + BORDER_WIDTH + EYE_SIZE/2, y + BORDER_WIDTH + EYE_SIZE*2, EYE_SIZE, EYE_SIZE);
    }
    if (direction == EAST)
    {
        fillOval(x + BORDER_WIDTH, y + BORDER_WIDTH + TILE_SIZE/4, TILE_SIZE, TILE_SIZE/2);
        setColour(blue);
        fillOval((x+TILE_SIZE) - EYE_SIZE*2 + BORDER_WIDTH, y + BORDER_WIDTH + TILE_SIZE/2 - EYE_SIZE, EYE_SIZE, EYE_SIZE);
        fillOval((x+TILE_SIZE) - EYE_SIZE*2 + BORDER_WIDTH, (y+TILE_SIZE) + BORDER_WIDTH - TILE_SIZE/2 + EYE_SIZE/2, EYE_SIZE, EYE_SIZE);
    }
    if (direction == SOUTH)
    {
        fillOval(x + BORDER_WIDTH + TILE_SIZE/4, y + BORDER_WIDTH , TILE_SIZE/2, TILE_SIZE);
        setColour(blue);
        fillOval(x + TILE_SIZE/2 + BORDER_WIDTH - EYE_SIZE, (y+TILE_SIZE) + BORDER_WIDTH - EYE_SIZE*2, EYE_SIZE, EYE_SIZE);
        fillOval((x+TILE_SIZE) - TILE_SIZE/2 + BORDER_WIDTH + EYE_SIZE/2, (y+TILE_SIZE) + BORDER_WIDTH - EYE_SIZE*2, EYE_SIZE, EYE_SIZE);
    }
    if (direction == WEST)
    {
        fillOval(x + BORDER_WIDTH , y + BORDER_WIDTH + TILE_SIZE/4, TILE_SIZE, TILE_SIZE/2);
        setColour(blue);
        fillOval(x + EYE_SIZE*2 + BORDER_WIDTH, y + BORDER_WIDTH + TILE_SIZE/2 - EYE_SIZE, EYE_SIZE, EYE_SIZE);
        fillOval(x + EYE_SIZE*2 + BORDER_WIDTH, (y+TILE_SIZE) + BORDER_WIDTH - TILE_SIZE/2 + EYE_SIZE/2, EYE_SIZE, EYE_SIZE);
    }
    
}

void updateArena(int Xposition, int Yposition, int direction, int **arenaArray, int widthInTiles, int heightInTiles)
{
    //clears foreground every time and replaces the markers and draws the robot in new position indicated by Xposition and Yposition
    clear();
    drawMarkers(arenaArray, widthInTiles, heightInTiles);
    drawRobot(Xposition, Yposition, direction);
    sleep(WAIT_TIME);
}

