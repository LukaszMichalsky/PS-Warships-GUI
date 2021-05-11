#include "graphic-board.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

void GraphicBoard::initBoard() {
  const QVector<QString> coordinateLetters({"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"});
  const QVector<QString> coordinateNumbers({" 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "10"});
  const QFont coordinateFont = QFont("Consolas", 10, QFont::Bold, false);
  const QPixmap waterTile = QPixmap(":/resources/images/water.png");

  groupBoardItems = scene() -> createItemGroup({});
  groupShips = scene() -> createItemGroup({});

  for (quint8 i = 0; i < 9; i++) { // Drawing borders.
    QGraphicsRectItem* borderItemVertical = new QGraphicsRectItem(totalFieldSize * i + FIELD_SIZE, 0, FIELD_BORDER_SIZE, totalBoardLength);
    borderItemVertical -> setPen(Qt::NoPen);
    borderItemVertical -> setBrush(FIELD_BORDER_COLOR);

    QGraphicsRectItem* borderItemHorizontal = new QGraphicsRectItem(0, totalFieldSize * i + FIELD_SIZE, totalBoardLength, FIELD_BORDER_SIZE);
    borderItemHorizontal -> setPen(Qt::NoPen);
    borderItemHorizontal -> setBrush(FIELD_BORDER_COLOR);

    groupBoardItems -> addToGroup(borderItemVertical);
    groupBoardItems -> addToGroup(borderItemHorizontal);
  }

  for (quint8 x = 0; x < 10; x++) { // Drawing water tiles.
    for (quint8 y = 0; y < 10; y++) {
      QGraphicsPixmapItem* waterItem = new QGraphicsPixmapItem(waterTile);
      waterItem -> setPos(totalFieldSize * x, totalFieldSize * y);
      groupBoardItems -> addToGroup(waterItem);
    }
  }

  for (quint8 i = 0; i < 10; i++) { // Drawing coordinates.
    QGraphicsTextItem* coordLetterTop = new QGraphicsTextItem(coordinateLetters[i]);
    coordLetterTop -> setFont(coordinateFont);
    coordLetterTop -> setPos(totalFieldSize * i + 5, -25);
    coordLetterTop -> setDefaultTextColor(QColor(0xDD, 0xDD, 0xDD));

    QGraphicsTextItem* coordLetterBottom = new QGraphicsTextItem(coordinateLetters[i]);
    coordLetterBottom -> setFont(coordinateFont);
    coordLetterBottom -> setPos(totalFieldSize * i + 5, totalBoardLength);
    coordLetterBottom -> setDefaultTextColor(QColor(0xDD, 0xDD, 0xDD));

    QGraphicsTextItem* coordLetterLeft = new QGraphicsTextItem(coordinateNumbers[i]);
    coordLetterLeft -> setFont(coordinateFont);
    coordLetterLeft -> setPos(-25, totalFieldSize * i + 2);
    coordLetterLeft -> setDefaultTextColor(QColor(0xDD, 0xDD, 0xDD));

    QGraphicsTextItem* coordLetterRight = new QGraphicsTextItem(coordinateNumbers[i].trimmed());
    coordLetterRight -> setFont(coordinateFont);
    coordLetterRight -> setPos(totalBoardLength + 4, totalFieldSize * i + 2);
    coordLetterRight -> setDefaultTextColor(QColor(0xDD, 0xDD, 0xDD));

    groupBoardItems -> addToGroup(coordLetterTop);
    groupBoardItems -> addToGroup(coordLetterBottom);
    groupBoardItems -> addToGroup(coordLetterLeft);
    groupBoardItems -> addToGroup(coordLetterRight);
  }
}
