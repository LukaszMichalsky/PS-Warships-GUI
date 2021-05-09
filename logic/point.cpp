#include "point.h"

Point::Point(size newX, size newY) : X(newX), Y(newY) {}
Point::~Point() {}

size Point::getX() {
  return X;
}

size Point::getY() {
  return Y;
}

void Point::setX(size newX) {
  X = newX;
}

void Point::setY(size newY) {
  Y = newY;
}

bool Point::equals(const Point &otherPoint) {
  return (X == otherPoint.X) && (Y == otherPoint.Y);
}
