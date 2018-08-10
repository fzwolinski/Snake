#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include <string>
#include <vector>

class map {

public:
  int width;
  int height;
  std::string **field;
  std::vector<int> snakeHeadPositionX;
  std::vector<int> snakeHeadPositionY;
  int fruitPos[2];
  int numOfSegments;
  bool addSnakeSegment;

  void gotoxy(short, short);
  void init();
  void create();
  void render();
  void update(int[], std::string);
  void setFruit();
  ~map();
};


#endif //SNAKE_MAP_H