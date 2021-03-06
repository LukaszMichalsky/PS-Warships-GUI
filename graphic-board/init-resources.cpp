#include "graphic-board.h"

void GraphicBoard::initResources() {
  if (waterTile == nullptr) waterTile = new QPixmap(":/resources/images/water.png");
  if (splashHit == nullptr) splashHit = new QPixmap(":/resources/images/splash-hit.png");
  if (splashMiss == nullptr) splashMiss = new QPixmap(":/resources/images/splash-miss.png");
  if (splashDrowned == nullptr) splashDrowned = new QPixmap(":/resources/images/splash-drowned.png");

  if (horizontalShips[0] == nullptr) horizontalShips[0] = new QPixmap(":/resources/images/H1.png");
  if (horizontalShips[1] == nullptr) horizontalShips[1] = new QPixmap(":/resources/images/H2.png");
  if (horizontalShips[2] == nullptr) horizontalShips[2] = new QPixmap(":/resources/images/H3.png");
  if (horizontalShips[3] == nullptr) horizontalShips[3] = new QPixmap(":/resources/images/H4.png");

  if (verticalShips[0] == nullptr) verticalShips[0] = new QPixmap(":/resources/images/V1.png");
  if (verticalShips[1] == nullptr) verticalShips[1] = new QPixmap(":/resources/images/V2.png");
  if (verticalShips[2] == nullptr) verticalShips[2] = new QPixmap(":/resources/images/V3.png");
  if (verticalShips[3] == nullptr) verticalShips[3] = new QPixmap(":/resources/images/V4.png");
}
