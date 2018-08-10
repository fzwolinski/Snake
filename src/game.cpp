#include <time.h>
#include <windows.h>
#include <stdio.h>

#include "include/game.h"

void game::hidecursor()
{
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = FALSE;
  SetConsoleCursorInfo(consoleHandle, &info);
}

game::game() {

  paramsSelection();

  m.init();
  m.addSnakeSegment = false;
  m.numOfSegments = 0;
  m.create();

  points = 0;

  srand((unsigned int)time(NULL));

  pos[0] = rand() % (m.height - 2) + 1;
  pos[1] = rand() % (m.width - 2) + 1;
  m.field[pos[0]][pos[1]] = "@";

  hidecursor();

  system("cls");
  m.render();
  m.setFruit();
  
  run();
}

void game::paramsSelection() {
  bool validParams = false;
  while (!validParams) {
    system("cls");

    printf("Map\nwidth (10 - 100): ");
    scanf_s("%i", &m.width);

    printf("height (7 - 20): ");
    scanf_s("%i", &m.height);

    printf("\nMode\n(t) traditional\n(i) improved version\n");
    scanf_s(" %c", &mode);

    if (m.width >= 10 && m.width <= 100 && m.height >= 7 && m.height <= 20 && (mode == 't' || mode == 'i')) {
      validParams = true;
    }
    else {
      printf("---Invalid parameters---\n\n");
      system("pause");
    }
  }
}

void game::run() {
  double i = 0;
  for (;;) {
    m.snakeHeadPositionX.push_back(pos[0]);
    m.snakeHeadPositionY.push_back(pos[1]);

    checkKeyboardInput();
    m.update(pos, dir);
    checkCollision();

    Sleep(100 - i);
    i = ((i < 60) && (mode == 'i')) ? i + 0.10 : i;
    showScore();
  }
}

void game::checkKeyboardInput() {
  if (GetAsyncKeyState(VK_LEFT) && dir != "right") {
    dir = "left";
  }
  else if (GetAsyncKeyState(VK_UP) && dir != "down") {
    dir = "up";
  }
  else if (GetAsyncKeyState(VK_RIGHT) && dir != "left") {
    dir = "right";
  }
  else if (GetAsyncKeyState(VK_DOWN) && dir != "up") {
    dir = "down";
  }
}

void game::checkCollision() {
  int n = 0;

  for (int i = 0; i < m.height; i++) {
    for (int j = 0; j < m.width; j++) {
      if (m.field[i][j] == "@") n++;
    }
  }

  if (n < m.numOfSegments + 1) {
    end();
  }

  if (mode == 't' && (pos[0] == 0 || pos[0] == (m.height - 1) || pos[1] == 0 || pos[1] == (m.width - 1))) {
    end();
  }

  if (mode == 'i') {
    if (pos[1] == 0) {
      pos[1] = m.width - 1;
      dir = "left";
      m.update(pos, dir);
      m.field[pos[0]][0] = "#";
      m.field[pos[0]][m.width - 1] = "#";

      m.gotoxy(0, pos[0]);
      printf("#");
      m.gotoxy(m.width - 1, pos[0]);
      printf("#");
    }
    else if (pos[1] == m.width - 1) {
      pos[1] = 0;
      dir = "right";
      m.update(pos, dir);
      m.field[pos[0]][0] = "#";
      m.field[pos[0]][m.width - 1] = "#";

      m.gotoxy(0, pos[0]);
      printf("#");
      m.gotoxy(m.width - 1, pos[0]);
      printf("#");
    }
    else if (pos[0] == 0) {
      pos[0] = m.height - 1;
      dir = "up";
      m.update(pos, dir);
      m.field[0][pos[1]] = "#";
      m.field[m.height - 1][pos[1]] = "#";

      m.gotoxy(pos[1], 0);
      printf("#");
      m.gotoxy(pos[1], m.height - 1);
      printf("#");
    }
    else if (pos[0] == m.height - 1) {
      pos[0] = 0;
      dir = "down";
      m.update(pos, dir);
      m.field[0][pos[1]] = "#";
      m.field[m.height - 1][pos[1]] = "#";
      
      m.gotoxy(pos[1], 0);
      printf("#");
      m.gotoxy(pos[1], m.height - 1);
      printf("#");
    }
  }

  if (pos[0] == m.fruitPos[0] && pos[1] == m.fruitPos[1]) {
    extendSnake();
    addPoint();
    m.setFruit();
  }
}

void game::addPoint() {
  points += 1;
}

void game::extendSnake() {
  m.numOfSegments++;
  m.addSnakeSegment = true;
}

void game::showScore() {
  m.gotoxy(0, m.height + 2);
  printf("Score: %i pts\n\n", points);
}

void game::end() {
  system("cls");
  printf("--- You lost ---\n");
  printf("Score: %i pts\n\n\n", points);
  system("pause");
  m.~map();
  exit(0);
}