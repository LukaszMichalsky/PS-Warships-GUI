#include "graphic-board.h"

void GraphicBoard::clickStatePlaying(QMouseEvent *event) {
  Point clickedFieldPoint(0, 0);

  if (getClickedPoint(event, clickedFieldPoint) == true) {
    emit getSelectedPoint(clickedFieldPoint);
  }
}
