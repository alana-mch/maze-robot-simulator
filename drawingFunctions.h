#define TILE_SIZE 30
#define ITEM_SIZE  24
#define ROBOT_SIZE  15
#define EYE_SIZE  4
#define NORTH  0
#define EAST 1
#define SOUTH  2
#define WEST 3
#define EMPTY 0
#define MARKER 1
#define OBSTACLE 2
#define BORDER_WIDTH 5
#define WAIT_TIME 5
#define TURN_WAIT_TIME 100


void drawMarkers(int**, int , int);
void drawObstacle(int, int);
void drawBorder(int, int);
void drawGrid(int , int);
void drawBackground(int , int);
void drawArena(int , int);
void drawRobot(int , int , int);
void updateArena(int , int , int , int** , int , int);
