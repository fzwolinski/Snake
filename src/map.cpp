#include <stdio.h>
#include <windows.h>

#include "include/map.h"

void map::gotoxy(short x, short y)
{
  COORD coord = { x, y };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void map::init() {
  field = new std::string*[height];
  for (int i = 0; i < height; ++i) {
    field[i] = new std::string[width];
  }
}

map::~map() {
  for (int i = 0; i < height; ++i) {
    delete[] field[i];
  }
  delete[] field;
}

void map::create() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (i == 0 || i == (height - 1) || j == 0 || j == (width - 1)) {
        field[i][j] = "#";
      }
      else {
        field[i][j] = " ";
      }
    }
  }
}

void map::render() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      printf("%s", field[i][j].c_str());
      if (j == (width - 1)) {
        printf("\n");
      }
    }
  }
}

void map::update(int pos[], std::string dir) {
  if (dir == "left") {
    field[pos[0]][pos[1]] = " ";
    field[pos[0]][pos[1] - 1] = "@";

    gotoxy(pos[1], pos[0]);
    printf(" ");
    gotoxy(pos[1] - 1, pos[0]);
    printf("@");
    pos[1] = pos[1] - 1;
  }
  else if (dir == "up") {
    field[pos[0]][pos[1]] = " ";
    field[pos[0] - 1][pos[1]] = "@";

    gotoxy(pos[1], pos[0]);
    printf(" ");
    gotoxy(pos[1], pos[0] - 1);
    printf("@");
    pos[0] = pos[0] - 1;
  }
  else if (dir == "right") {
    field[pos[0]][pos[1]] = " ";
    field[pos[0]][pos[1] + 1] = "@";

    gotoxy(pos[1], pos[0]);
    printf(" ");
    gotoxy(pos[1] + 1, pos[0]);
    printf("@");
    pos[1] = pos[1] + 1;
  }
  else if (dir == "down") {
    field[pos[0]][pos[1]] = " ";
    field[pos[0] + 1][pos[1]] = "@";

    gotoxy(pos[1], pos[0]);
    printf(" ");
    gotoxy(pos[1], pos[0] + 1);
    printf("@");
    pos[0] = pos[0] + 1;
  }

  if (addSnakeSegment) {
    for (int i = 0; i < numOfSegments; i++) {
      field[snakeHeadPositionX[snakeHeadPositionX.size() - (i + 2)]][snakeHeadPositionY[snakeHeadPositionY.size() - (i + 2)]] = " ";
      gotoxy(snakeHeadPositionY[snakeHeadPositionY.size() - (i + 2)], snakeHeadPositionX[snakeHeadPositionX.size() - (i + 2)]);
      printf(" ");
    }
    for (int i = 0; i < numOfSegments; i++) {
      field[snakeHeadPositionX[snakeHeadPositionX.size() - (i + 1)]][snakeHeadPositionY[snakeHeadPositionY.size() - (i + 1)]] = "@";
      gotoxy(snakeHeadPositionY[snakeHeadPositionY.size() - (i + 1)], snakeHeadPositionX[snakeHeadPositionX.size() - (i + 1)]);
      printf("@");
    }
  }
}

void map::setFruit() {
  do {
    fruitPos[0] = rand() % (height - 2) + 1;
    fruitPos[1] = rand() % (width - 2) + 1;
  } while (field[fruitPos[0]][fruitPos[1]] != " ");
  field[fruitPos[0]][fruitPos[1]] = "&";

  gotoxy(fruitPos[1], fruitPos[0]);
  printf("&");
}