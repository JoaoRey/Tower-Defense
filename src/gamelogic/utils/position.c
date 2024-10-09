#include "position.h"

void position_init(Position *position, float x, float y) {
  position->x = x;
  position->y = y;
}

void position_setX(Position *position, float x) {
  position->x = x;
}

void position_setY(Position *position, float y) {
  position->y = y;
}

float position_getX(Position *position) {
  return position->x;
}

float position_getY(Position *position) {
  return position->y;
}

int position_equals(Position *position1, Position *position2) {
  return position1->x == position2->x && position1->y == position2->y;
}

int position_hashCode(Position *position) {
  return (int) (position->x) ^ (int) (position->y);
}
