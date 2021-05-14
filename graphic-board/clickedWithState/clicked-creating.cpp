#include "graphic-board.h"

void GraphicBoard::clickStateCreating(QMouseEvent *event) {
  Point selectedPoint(0, 0);

  if (getClickedPoint(event, selectedPoint) == true) {
    bool added = ShipGroup::add(&manualBuildBoard, selectedPoint, ghostModeCurrentSize, ghostModeCurrentDirection);

    if (added) {
      redrawShips(manualBuildBoard);
      manualBuildShipsLeft--;
    }
  }

  if (manualBuildShipsLeft == 0) {
    manualBuildCurrentSize--;

    switch (manualBuildCurrentSize) {
      case 3: {
        manualBuildShipsLeft = 2; break;
      } case 2: {
        manualBuildShipsLeft = 3; break;
      } case 1: {
        manualBuildShipsLeft = 4; break;
      }
    }
  }

  if (manualBuildCurrentSize == 0 && manualBuildShipsLeft == 0) {
    disableGhostMode();
    setBoardState(GraphicBoardState::STATE_NONE);

    emit manualBoardBuildFinished();
  } else {
    setGhostMode(manualBuildCurrentSize, ghostModeCurrentDirection);
  }
}
