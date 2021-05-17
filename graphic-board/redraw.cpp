#include "graphic-board.h"

void GraphicBoard::redrawShips(const Board &targetBoard) {
  for (QGraphicsItem* shipItem : groupShips -> childItems()) { // Clearing board from existing items.
    if (shipItem != nullptr) {
      delete shipItem;
    }
  }

  Point shipPoint(0, 0);
  renderedGroups.clear();

  for (short x = 0; x < 10; x++) {
    for (short y = 0; y < 10; y++) {
      shipPoint.setX(x);
      shipPoint.setY(y);

      Ship* shipPointer = targetBoard.getShipPointer(shipPoint);
      ShipGroup* groupPointer = nullptr;

      if (shipPointer != nullptr) {
        groupPointer = shipPointer -> getShipGroup();

        if (groupPointer != nullptr) {
          if (renderedGroups.contains(groupPointer) == false) {
            renderedGroups.push_back(groupPointer);

            ShipDirection groupDirection = groupPointer -> getDirection();
            ship_size_t groupSize = groupPointer -> getSize();
            QGraphicsPixmapItem* newShip = nullptr;

            if (groupDirection == ShipDirection::DIRECTION_HORIZONTAL) {
              newShip = new QGraphicsPixmapItem(*horizontalShips[groupSize - 1]);
            } else {
              newShip = new QGraphicsPixmapItem(*verticalShips[groupSize - 1]);
            }

            newShip -> setPos(x * totalFieldSize, y * totalFieldSize);
            groupShips -> addToGroup(newShip);
          }
        }
      }
    }
  }
}

void GraphicBoard::redrawShoots(const Board &targetBoard) {
  for (QGraphicsItem* shootItem : groupShoots -> childItems()) {
    if (shootItem != nullptr) {
      delete shootItem;
    }
  }

  Point shootPoint(0, 0);

  for (short x = 0; x < 10; x++) {
    for (short y = 0; y < 10; y++) {
      shootPoint.setX(x);
      shootPoint.setY(y);

      Ship* fieldPointer = targetBoard.getShipPointer(shootPoint);
      ShipState fieldState = fieldPointer -> getShipState();
      QGraphicsPixmapItem* splashItem = nullptr;

      switch ((int) fieldState) {
        case (int) ShipState::STATE_HIT: {
          splashItem = new QGraphicsPixmapItem(*splashHit);
          break;
        } case (int) ShipState::STATE_MISSED: {
          splashItem = new QGraphicsPixmapItem(*splashMiss);
          break;
        } case (int) ShipState::STATE_DROWNED: {
          splashItem = new QGraphicsPixmapItem(*splashDrowned);
        }
      }

      if (splashItem != nullptr) {
        splashItem -> setPos(x * totalFieldSize, y * totalFieldSize);
        groupShoots -> addToGroup(splashItem);
      }
    }
  }
}
