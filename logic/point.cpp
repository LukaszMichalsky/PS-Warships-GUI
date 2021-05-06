#include "point.h"

Point::Point(short newX, short newY) : X(newX), Y(newY) {}
Point::~Point() {}

short Point::getX() {
  return X;
}

short Point::getY() {
  return Y;
}

void Point::setX(short newX) {
  X = newX;
}

void Point::setY(short newY) {
  Y = newY;
}

bool Point::equals(const Point &otherPoint) {
  return (X == otherPoint.X) && (Y == otherPoint.Y);
}
