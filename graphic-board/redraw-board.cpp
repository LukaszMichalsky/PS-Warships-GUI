#include "graphic-board.h"

void GraphicBoard::redrawBoard(const Board &targetBoard) {
  for (QGraphicsItem* shipItem : groupShips -> childItems()) { // Clearing board from existing items.
    if (shipItem != nullptr) {
      delete shipItem;
    }
  }

  Point shipPoint(0, 0);

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
