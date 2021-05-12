#include "graphic-board.h"

void GraphicBoard::initResources() {
  if (waterTile == nullptr) waterTile = new QPixmap(":/resources/images/water.png");

  if (horizontalShips[0] == nullptr) horizontalShips[0] = new QPixmap(":/resources/images/H1.png");
  if (horizontalShips[1] == nullptr) horizontalShips[1] = new QPixmap(":/resources/images/H2.png");
  if (horizontalShips[2] == nullptr) horizontalShips[2] = new QPixmap(":/resources/images/H3.png");

  if (verticalShips[0] == nullptr) verticalShips[0] = new QPixmap(":/resources/images/V1.png");
  if (verticalShips[1] == nullptr) verticalShips[1] = new QPixmap(":/resources/images/V2.png");
  if (verticalShips[2] == nullptr) verticalShips[2] = new QPixmap(":/resources/images/V3.png");
}
