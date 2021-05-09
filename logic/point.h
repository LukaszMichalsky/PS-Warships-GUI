#pragma once

using size = unsigned char;

class Point {
  private:
    size X = 0;
    size Y = 0;

  public:
    Point(size newX, size newY);
    ~Point();

    size getX();
    size getY();

    void setX(size newX);
    void setY(size newY);

    bool equals(const Point& otherPoint);
};
