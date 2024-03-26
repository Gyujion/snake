#include "console.h"
#include <ctime>

#define BOARD_SIZE 20
#define MOVE_DELAY 15
#define WALL_VERTICAL_STRING "┃"
#define WALL_HORIZONTAL_STRING "━"
#define WALL_RIGHT_TOP_STRING "┓"
#define WALL_LEFT_TOP_STRING "┏"
#define WALL_RIGHT_BOTTOM_STRING "┛"
#define WALL_LEFT_BOTTOM_STRING "┗"
#define SNAKE_STRING "■"
#define SNAKE_BODY_STRING "■"
#define APPLE_STRING "●"

int x = BOARD_SIZE/2;
int y = BOARD_SIZE/2;

void handleInput() {
  if (console::key(console::K_LEFT)) {
    x--;
  }
  if (console::key(console::K_RIGHT)) {
    x++;
  }
  if (console::key(console::K_UP)) {
    y--;
  }
  if (console::key(console::K_DOWN)) {
    y++;
  }
}

void restrictInScreen() {
  // x, y 위치를 화면의 최대 크기에서 벗어나지 않게 한다.
  if (x <= 1)
    x = 1;
  if (x >= BOARD_SIZE-1)
    x = BOARD_SIZE - 2;
  if (y <= 1)
    y = 1;
  if (y >= BOARD_SIZE-1)
    y = BOARD_SIZE - 2;
}

void drawSnake() {
  console::draw(x, y, SNAKE_STRING);
}
void snakeTail()
{
  console::draw(x,y,SNAKE_BODY_STRING);
}

void drawApple()
{
  srand((unsigned int)time(NULL));
}

void drawWalls()
{ 
  console::draw(0,0,WALL_LEFT_TOP_STRING);

  for(int X=1;X<BOARD_SIZE-1;X++)
  {
    console::draw(X,0,WALL_HORIZONTAL_STRING);
  }
  console::draw(BOARD_SIZE-1,0,WALL_RIGHT_TOP_STRING);
  for(int Y=1;Y<BOARD_SIZE-1;Y++)
  {
    console::draw(0,Y,WALL_VERTICAL_STRING);
  }
  console::draw(0,BOARD_SIZE-1,WALL_LEFT_BOTTOM_STRING);
  for(int X=1;X<BOARD_SIZE-1;X++)
  {
    console::draw(X,BOARD_SIZE-1,WALL_HORIZONTAL_STRING);
  }
  console::draw(BOARD_SIZE-1,BOARD_SIZE-1,WALL_RIGHT_BOTTOM_STRING);
  for(int Y =1;Y<BOARD_SIZE-1;Y++)
  {
    console::draw(BOARD_SIZE-1,Y,WALL_VERTICAL_STRING);
  }
}

void game() {
  // 콘솔 라이브러리를 초기화한다.
  console::init();

  while (true) {
    if(console::key(console::K_ESC)==true)
      break;
    
    // 화면을 지운다.
    console::clear();

    drawWalls();
    handleInput();
    restrictInScreen();
    drawSnake();

    // 화면을 갱신하고 다음 프레임까지 대기한다.
    console::wait();
  }
}
