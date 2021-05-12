#include "graphic-board.h"

const quint16 GraphicBoard::FIELD_SIZE = 25;
const quint16 GraphicBoard::FIELD_BORDER_SIZE = 2;
const QBrush GraphicBoard::FIELD_BORDER_COLOR = QBrush(QColor(48, 48, 48));

const quint16 GraphicBoard::totalFieldSize = FIELD_SIZE + FIELD_BORDER_SIZE;
const quint16 GraphicBoard::totalBoardLength = FIELD_SIZE * 10 + FIELD_BORDER_SIZE * 9;

QPixmap* GraphicBoard::waterTile = nullptr;
QVector<QPixmap*> GraphicBoard::horizontalShips(4, nullptr);
QVector<QPixmap*> GraphicBoard::verticalShips(4, nullptr);

GraphicBoard::GraphicBoard(QWidget* parent) : QGraphicsView(parent) { initScene(); }
GraphicBoard::GraphicBoard(QGraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent) { initScene(); }

void GraphicBoard::initScene() {
  QGraphicsScene* boardScene = new QGraphicsScene(0, 0, 0, 0, this);
  this -> setScene(boardScene);

  initResources(); // This method must be invoked first.
  initBoard();
}

void GraphicBoard::mouseMoveEvent(QMouseEvent *event) {}

void GraphicBoard::mouseReleaseEvent(QMouseEvent *event) {}
