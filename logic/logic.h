#pragma once

#include "point.h"

#include <QVector>

// Type aliases.
using board_size_t = quint8;
using ship_size_t = quint8;

enum class ShipDirection {
  DIRECTION_HORIZONTAL,
  DIRECTION_VERTICAL
};

enum class ShipState {
  STATE_EMPTY,
  STATE_DROWNED,
  STATE_HIT,
  STATE_MISSED,
  STATE_NORMAL
};

class Board;
class Ship;
class ShipGroup;

class Board {
  private:
    Ship** boardTable = nullptr;
    board_size_t boardSize = 0;

    bool checkPointExists(Point point);
    bool setShip(Ship newShip);

    friend class Ship;
    friend class ShipGroup;

  public:
    Board(board_size_t newSize);
   ~Board();

    Board(const Board&) = delete;
    Board& operator= (const Board&) = delete;

    Ship* getShipPointer(Point point);
    board_size_t getBoardSize();

    void fillShips(ShipState newState);
    bool isFieldValidForNewShip(Point point);

    bool shoot(bool& wasTargetHit, Point point);
    QVector<Ship*> getNeighborsPointers(Point point);
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
