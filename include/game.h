#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "map.h"

class game {
private:
  map m;
  int pos[2];
  int points;
  char mode;
  std::string dir;

  void hidecursor();
  void checkKeyboardInput();
  void checkCollision();
  void run();
  void addPoint();
  void extendSnake();
  void end();
  void paramsSelection();
  void showScore();

public:
  game();
};

#endif //SNAKE_GAME_H