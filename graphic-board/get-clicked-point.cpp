#include "graphic-board.h"

#include <QDebug>

bool GraphicBoard::getClickedPoint(QMouseEvent *inputEvent, Point& outputPoint) {
  bool clicked = false;

  quint16 eventX = inputEvent -> x();
  quint16 eventY = inputEvent -> y();

  qint16 boardX = eventX - 32;
  qint16 boardY = eventY - 34;

  // qDebug() << QString("[Event X] %1 [Event Y] %2").arg(eventX).arg(eventY).toStdString().c_str();
  // qDebug() << QString("[Board X] %1 [Board Y] %2").arg(boardX).arg(boardY).toStdString().c_str();

  if (boardX > -1 && boardX < totalBoardLength && boardY > -1 && boardY < totalBoardLength) {
    quint8 fieldX = boardX / totalFieldSize;
    quint8 fieldY = boardY / totalFieldSize;

    quint8 internalX = boardX % totalFieldSize;
    quint8 internalY = boardY % totalFieldSize;

    // qDebug() << QString("  [Field X] %1 [Field Y] %2").arg(fieldX).arg(fieldY).toStdString().c_str();
    // qDebug() << QString("  [Internal X] %1 [Internal Y] %2").arg(internalX).arg(internalY).toStdString().c_str();

    if (internalX < FIELD_SIZE && internalY < FIELD_SIZE) {
      quint8 resultX = fieldX + 1;
      quint8 resultY = fieldY + 1;

      // qDebug() << QString("    [RESULT X] %1 [RESULT Y] %2").arg(resultX).arg(resultY).toStdString().c_str();

      outputPoint.setX(resultX);
      outputPoint.setY(resultY);

      clicked = true;
    }
  }

  return clicked;
}
