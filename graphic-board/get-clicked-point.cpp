#include "graphic-board.h"

bool GraphicBoard::getClickedPoint(QMouseEvent *inputEvent, Point& outputPoint) { // Returns point coordinates from 1 to 10.
  bool clicked = false;

  quint16 eventX = inputEvent -> x();
  quint16 eventY = inputEvent -> y();

  qint16 boardX = eventX - 32;
  qint16 boardY = eventY - 34;

  if (boardX > -1 && boardX < totalBoardLength && boardY > -1 && boardY < totalBoardLength) {
    quint8 fieldX = boardX / totalFieldSize;
    quint8 fieldY = boardY / totalFieldSize;

    quint8 internalX = boardX % totalFieldSize;
    quint8 internalY = boardY % totalFieldSize;

    if (internalX < FIELD_SIZE && internalY < FIELD_SIZE) {
      outputPoint.setX(fieldX);
      outputPoint.setY(fieldY);

      clicked = true;
    }
  }

  return clicked;
}
