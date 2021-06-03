#include "application.h"
#include "ui_application.h"

void Application::setDrownedShip(Board &targetBoard, Point targetPoint) {
  Ship* pointer = targetBoard.getShipPointer(targetPoint);

  if (pointer != nullptr) {
    if (pointer -> getShipState() == ShipState::STATE_DROWNED) {
      for (Ship* neighborPointer : targetBoard.getNeighborsPointers(targetPoint)) {
        if (neighborPointer != nullptr) {
          if (neighborPointer -> getShipState() == ShipState::STATE_HIT) {
            neighborPointer -> setShipState(ShipState::STATE_DROWNED);
            setDrownedShip(targetBoard, neighborPointer -> getPoint()); // Set DROWNED state for entire ship object recursively.
          }
        }
      }
    }
  }
}
