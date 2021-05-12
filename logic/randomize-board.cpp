#include "application.h"
#include "ui_application.h"

void Application::randomizeBoard(Board &targetBoard) {
  Point newShipPoint(0, 0);
  ShipDirection newDirection;

  for (int i = 0; i < (int) ShipCount::SHIP_SINGLE; i++) {
    while (true) {
      newShipPoint.setX(QRandomGenerator::global() -> bounded(0, 10));
      newShipPoint.setY(QRandomGenerator::global() -> bounded(0, 10));
      newDirection = (QRandomGenerator::global() -> bounded(0, 2) == 0) ? ShipDirection::DIRECTION_HORIZONTAL : ShipDirection::DIRECTION_VERTICAL;

      if (ShipGroup::add(&targetBoard, newShipPoint, 1, newDirection) != nullptr) {
        break;
      }
    }
  }

  for (int i = 0; i < (int) ShipCount::SHIP_DOUBLE; i++) {
    while (true) {
      newShipPoint.setX(QRandomGenerator::global() -> bounded(0, 10));
      newShipPoint.setY(QRandomGenerator::global() -> bounded(0, 10));
      newDirection = (QRandomGenerator::global() -> bounded(0, 2) == 0) ? ShipDirection::DIRECTION_HORIZONTAL : ShipDirection::DIRECTION_VERTICAL;

      if (ShipGroup::add(&targetBoard, newShipPoint, 2, newDirection) != nullptr) {
        break;
      }
    }
  }

  for (int i = 0; i < (int) ShipCount::SHIP_TRIPLE; i++) {
    while (true) {
      newShipPoint.setX(QRandomGenerator::global() -> bounded(0, 10));
      newShipPoint.setY(QRandomGenerator::global() -> bounded(0, 10));
      newDirection = (QRandomGenerator::global() -> bounded(0, 2) == 0) ? ShipDirection::DIRECTION_HORIZONTAL : ShipDirection::DIRECTION_VERTICAL;

      if (ShipGroup::add(&targetBoard, newShipPoint, 3, newDirection) != nullptr) {
        break;
      }
    }
  }
}
