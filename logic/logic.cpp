#include "logic.h"

/////////////////
// BOARD CLASS //
/////////////////

Board::Board() {
  boardTable = new Ship* [boardSize];

  for (board_size_t x = 0; x < boardSize; x++) {
    boardTable[x] = new Ship[boardSize];
  }
}

Board::~Board() {
  if (boardTable != nullptr) {
    for (board_size_t x = 0; x < boardSize; x++) {
      delete[] boardTable[x];
      boardTable[x] = nullptr;
    }

    delete[] boardTable;
    boardTable = nullptr;
    boardSize = 0;
  }
}

bool Board::checkPointExists(Point point) const {
  short x = point.getX();
  short y = point.getY();

  return (x >= 0 && x < boardSize) && (y >= 0 && y < boardSize);
}

Ship* Board::getShipPointer(Point point) const {
  if (checkPointExists(point) == true) {
    board_size_t x = point.getX();
    board_size_t y = point.getY();

    return &boardTable[x][y];
  }

  return nullptr;
}

bool Board::setShip(Ship newShip) {
  Point newShipPoint = newShip.getPoint();
  board_size_t x = newShipPoint.getX();
  board_size_t y = newShipPoint.getY();

  if (checkPointExists(newShipPoint) == true) {
    boardTable[x][y] = newShip;
    return true;
  }

  return false;
}

void Board::fillShips(ShipState newState) {
  for (board_size_t x = 0; x < boardSize; x++) {
    for (board_size_t y = 0; y < boardSize; y++) {
      setShip(Ship(Point(x, y), newState));
    }
  }
}

bool Board::isFieldValidForNewShip(Point point) {
  QVector<Ship*> neighbors = getNeighborsPointers(point);

  if (checkPointExists(point) == true) {
    for (board_size_t s = 0; s < neighbors.size(); s++) {
      Ship* ship = neighbors[s];

      if (ship != nullptr) {
        if (ship -> getShipState() != ShipState::STATE_EMPTY) {
          return false;
        }
      }
    }
  } else {
    return false;
  }

  return true;
}

bool Board::shoot(bool &wasTargetHit, Point point) {
  bool wasHit = false;
  bool wasShoot = false;

  if (checkPointExists(point) == true) {
    Ship* shipPointer = getShipPointer(point);

    if (shipPointer -> getShipState() == ShipState::STATE_NORMAL) {
      shipPointer -> setShipState(ShipState::STATE_HIT);
      wasHit = true;

      if (shipPointer -> getShipGroup() -> getShipsLeft() == 0) { // Entire ship group has been drowned.
        for (Ship* ship : shipPointer -> getShipGroup() -> getShipPointers()) {
          ship -> setShipState(ShipState::STATE_DROWNED);
        }
      }
    } else if (shipPointer -> getShipState() == ShipState::STATE_EMPTY) {
      shipPointer -> setShipState(ShipState::STATE_MISSED);
    }

    wasShoot = true;
  }

  wasTargetHit = wasHit;
  return wasShoot;
}

QVector<Ship*> Board::getNeighborsPointers(Point point) {
  board_size_t pointX = point.getX();
  board_size_t pointY = point.getY();
  QVector<Ship*> neighbors = QVector<Ship*>();

  for (short x = -1; x < 2; x++) {
    for (short y = -1; y < 2; y++) {
      neighbors.push_back(getShipPointer(Point(pointX + x, pointY + y)));
    }
  }

  return neighbors;
}

////////////////
// SHIP CLASS //
////////////////

Ship::Ship() : shipPoint(Point(0, 0)), currentState(ShipState::STATE_EMPTY) {}
Ship::Ship(Point newPoint, ShipState newState) : shipPoint(newPoint), currentState(newState) {}
Ship::~Ship() {}

Point Ship::getPoint() {
  return shipPoint;
}

ShipGroup* Ship::getShipGroup() {
  return currentGroup;
}

ShipState Ship::getShipState() {
  return currentState;
}

void Ship::setShipGroup(ShipGroup *newGroup) {
  currentGroup = newGroup;
}

void Ship::setShipState(ShipState newState) {
  currentState = newState;
}

//////////////////////
// SHIP GROUP CLASS //
//////////////////////


ShipGroup::ShipGroup() {}

ShipGroup* ShipGroup::add(Board *targetBoard, Point topLeftPoint, ship_size_t groupSize, ShipDirection shipDirection) {
  board_size_t pointX = topLeftPoint.getX();
  board_size_t pointY = topLeftPoint.getY();

  ShipGroup* newGroup = nullptr;
  if (targetBoard == nullptr || groupSize < 1 || groupSize > 4) return nullptr;

  if (checkPosition(targetBoard, topLeftPoint, groupSize, shipDirection) == false) {
    return nullptr;
  } else {
    newGroup = new ShipGroup();

    newGroup -> groupDirection = shipDirection;
    newGroup -> groupSize = groupSize;
  }

  board_size_t deltaX = 0;
  board_size_t deltaY = 0;

  switch (shipDirection) {
    case ShipDirection::DIRECTION_HORIZONTAL: {
      deltaX = 1;
      break;
    } case ShipDirection::DIRECTION_VERTICAL: {
      deltaY = 1;
      break;
    } default: {
      delete newGroup;
      return nullptr;
    }
  }

  for (board_size_t s = 0; s < groupSize; s++) {
    Point newShipPoint = Point(pointX + deltaX * s, pointY + deltaY * s);
    Ship newShip = Ship(newShipPoint, ShipState::STATE_NORMAL);

    newShip.setShipGroup(newGroup);
    targetBoard -> setShip(newShip);
    newGroup -> shipPointers.push_back(&newShip);
  }

  return newGroup;
}

bool ShipGroup::checkPosition(Board *targetBoard, Point topLeftPoint, ship_size_t groupSize, ShipDirection shipDirection) {
  board_size_t pointX = topLeftPoint.getX();
  board_size_t pointY = topLeftPoint.getY();

  if (targetBoard == nullptr) return false;

  board_size_t deltaX = 0;
  board_size_t deltaY = 0;

  switch (shipDirection) {
    case ShipDirection::DIRECTION_HORIZONTAL: {
      deltaX = 1;
      break;
    } case ShipDirection::DIRECTION_VERTICAL: {
      deltaY = 1;
      break;
    } default: {
      return false;
    }
  }

  for (board_size_t s = 0; s < groupSize; s++) {
    if (targetBoard -> isFieldValidForNewShip(Point(pointX + deltaX * s, pointY + deltaY * s)) == false) {
      return false;
    }
  }

  return true;
}

ShipDirection ShipGroup::getDirection() {
  return groupDirection;
}

QVector<Ship*> ShipGroup::getShipPointers() {
  return shipPointers;
}

board_size_t ShipGroup::getShipsLeft() {
  board_size_t shipsLeft = 0;

  for (Ship* pointer : shipPointers) {
    if (pointer -> getShipState() == ShipState::STATE_NORMAL) {
      shipsLeft++;
    }
  }

  return shipsLeft;
}

board_size_t ShipGroup::getSize() {
  return groupSize;
}
