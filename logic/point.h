#pragma once

class Point {
  private:
    short X = 0;
    short Y = 0;

  public:
    Point(short newX, short newY);
    ~Point();

    short getX();
    short getY();

    void setX(short newX);
    void setY(short newY);

    bool equals(const Point& otherPoint);
};
