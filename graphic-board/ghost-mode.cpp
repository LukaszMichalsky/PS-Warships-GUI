#include "graphic-board.h"

void GraphicBoard::disableGhostMode() {
  ghostModeEnabled = false;
}

void GraphicBoard::setGhostMode(ship_size_t shipSize, ShipDirection shipDirection) {
  ghostModeEnabled = true;
  ghostModeCurrentSize = shipSize;
  ghostModeCurrentDirection = shipDirection;

  if (ghostModeCurrentDirection == ShipDirection::DIRECTION_HORIZONTAL) {
    ghostModeCurrentShip = horizontalShips[shipSize - 1];
  } else {
    ghostModeCurrentShip = verticalShips[shipSize - 1];
  }
}
