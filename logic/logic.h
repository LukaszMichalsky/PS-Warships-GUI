#pragma once

#include "point.h"

#include <QVector>

// Type aliases.
using board_size_t = quint8;
using ship_size_t = quint8;

enum class ShipCount : int {
  SHIP_SINGLE = 4,
  SHIP_DOUBLE = 3,
  SHIP_TRIPLE = 2,
  SHIP_QUADRUPLE = 1
};

enum class ShipDirection : int {
  DIRECTION_HORIZONTAL = 0,
  DIRECTION_VERTICAL = 1
};

enum class ShipState : int {
  STATE_EMPTY = 0,
  STATE_DROWNED = 1,
  STATE_HIT = 2,
  STATE_MISSED = 3,
  STATE_NORMAL = 4
};

class Board;
class Ship;
class ShipGroup;

class Board {
  private:
    Ship** boardTable = nullptr;
    board_size_t boardSize = 10;

    bool checkPointExists(Point point) const;
    bool setShip(Ship newShip);

    friend class Ship;
    friend class ShipGroup;

  public:
    Board();
   ~Board();

    Board(const Board&) = delete;
    Board& operator= (const Board&) = delete;

    void fillShips(ShipState newState);
    bool isFieldValidForNewShip(Point point);

    bool shoot(bool& wasTargetHit, Point point);
    QVector<Ship*> getNeighborsPointers(Point point);
    Ship* getShipPointer(Point point) const;
};

class Ship {
  private:
    Point shipPoint = Point(0, 0);
    ShipGroup* currentGroup = nullptr;
    ShipState currentState = ShipState::STATE_EMPTY;

    void setShipGroup(ShipGroup* newGroup);

    friend class ShipGroup;

  public:
    Ship();
    Ship(Point newPoint, ShipState newState);
    ~Ship();

    Point getPoint();
    ShipGroup* getShipGroup();
    ShipState getShipState();

    void setShipState(ShipState newState);
};

class ShipGroup {
  private:
    QVector<Ship*> shipPointers = QVector<Ship*>();
    ship_size_t groupSize = 0;
    ShipDirection groupDirection = ShipDirection::DIRECTION_HORIZONTAL;

    ShipGroup();

  public:
    ShipGroup(const ShipGroup&) = delete;
    ShipGroup(ShipGroup&&) = delete;

    ShipGroup& operator= (const ShipGroup&) = delete;
    ShipGroup& operator= (const ShipGroup&&) = delete;

    static ShipGroup* add(Board* targetBoard, Point topLeftPoint, ship_size_t groupSize, ShipDirection shipDirection);
    static bool checkPosition(Board* targetBoard, Point topLeftPoint, ship_size_t groupSize, ShipDirection shipDirection);

    ShipDirection getDirection();
    QVector<Ship*> getShipPointers();

    ship_size_t getShipsLeft();
    ship_size_t getSize();
};
