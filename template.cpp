#include "console.h"
#include <iostream>
#include <ctime>
#include <string>

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

int x, y, snakeLength, score, appleX, appleY;
int body_x[100], body_y[100];
int dir;
bool gameover;

void reset()
{
  x = BOARD_SIZE / 2;
  y = BOARD_SIZE / 2;
  snakeLength = 0;
  score = 0;
  dir = console::K_RIGHT;
  gameover = false;
  appleX = rand() % (BOARD_SIZE - 2) + 1;
  appleY = rand() % (BOARD_SIZE - 2) + 1;
}
void input()
{
  if (console::key(console::K_LEFT))
    dir = console::K_LEFT;
  if (console::key(console::K_RIGHT))
    dir = console::K_RIGHT;
  if (console::key(console::K_UP))
    dir = console::K_UP;
  if (console::key(console::K_DOWN))
    dir = console::K_DOWN;
  if (console::key(console::K_ESC))
    gameover = true;
}

void drawWalls()
{
  std::string strScore = std::to_string(score);
  console::draw(0, 0, WALL_LEFT_TOP_STRING);

  for (int X = 1; X < BOARD_SIZE - 1; X++)
  {
    console::draw(X, 0, WALL_HORIZONTAL_STRING);
  }
  console::draw(BOARD_SIZE - 1, 0, WALL_RIGHT_TOP_STRING);
  for (int Y = 1; Y < BOARD_SIZE - 1; Y++)
  {
    console::draw(0, Y, WALL_VERTICAL_STRING);
  }
  console::draw(0, BOARD_SIZE - 1, WALL_LEFT_BOTTOM_STRING);
  for (int X = 0; X < BOARD_SIZE - 1; X++)
  {
    console::draw(X, BOARD_SIZE - 1, WALL_HORIZONTAL_STRING);
  }
  console::draw(BOARD_SIZE - 1, BOARD_SIZE - 1, WALL_RIGHT_BOTTOM_STRING);
  for (int Y = 1; Y < BOARD_SIZE - 1; Y++)
  {
    console::draw(BOARD_SIZE - 1, Y, WALL_VERTICAL_STRING);
  }
  console::draw(BOARD_SIZE / 2 - 3, BOARD_SIZE, "SCORE: ");
  console::draw(BOARD_SIZE / 2 + 4, BOARD_SIZE, strScore);
}
void drawLogic()
{
  console::clear();
  drawWalls();

  for (int i = 0; i < BOARD_SIZE - 1; i++)
  {
    for (int j = 0; j < BOARD_SIZE - 1; j++)
    {
      if (i == y && j == x)
        console::draw(j, i, SNAKE_STRING);
      else if (i == appleY && j == appleX)
        std::cout << APPLE_STRING;
      else
      {
        bool print = false;
        for (int k = 0; k < snakeLength; k++)
        {
          if (body_x[k] == j && body_y[k] == i)
            console::draw(j, i, SNAKE_BODY_STRING);
          print = true;
        }
        if (!print)
          std::cout << " ";
      }
    }
  }
}

void play()
{
  int prevX = body_x[0];
  int prevY = body_y[0];
  int prev2X, prev2Y;
  body_x[0] = x;
  body_y[0] = y;
  for (int i = 1; i < snakeLength; i++)
  {
    prev2X = body_x[i];
    prev2Y = body_y[i];
    body_x[i] = prevX;
    body_y[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }

  switch (dir)
  {
  case console::K_LEFT:
    x--;
    break;
  case console::K_RIGHT:
    x++;
    break;
  case console::K_DOWN:
    y++;
    break;
  case console::K_UP:
    y--;
    break;
  }
  if (x < 0 || x > BOARD_SIZE || y < 0 || y > BOARD_SIZE)
    gameover = true;
  for (int i = 0; i < snakeLength; i++)
    if (body_x[i] == x && body_y[i] == y)
      gameover = true;
  if (x == appleX && y == appleY)
  {
    score += 10;
    appleX = rand() % (BOARD_SIZE - 2) + 1;
    appleY = rand() % (BOARD_SIZE - 2) + 1;
    snakeLength++;
  }
}
void sleep(int second)
{
  clock_t start_clk = clock();

  second--;
  while (true)
  {
    if ((clock() - start_clk) > second)
      break;
  }
}

void game()
{
  srand((unsigned int)time(NULL));
  // 콘솔 라이브러리를 초기화한다.
  console::init();
  reset();

  while (!gameover)
  {
    drawLogic();
    input();
    play();
    sleep(250);

    // 화면을 갱신하고 다음 프레임까지 대기한다.
    console::wait();
  }
}
