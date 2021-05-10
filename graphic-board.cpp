#include "graphic-board.h"

GraphicBoard::GraphicBoard(QWidget* parent) : QGraphicsView(parent) { initScene(); }
GraphicBoard::GraphicBoard(QGraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent) { initScene(); }

void GraphicBoard::initScene() {
  QGraphicsScene* boardScene = new QGraphicsScene(0, 0, 0, 0, this);
  this -> setScene(boardScene);
}

void GraphicBoard::drawBoard(const Board *targetBoard) {
  const quint16 FIELD_SIZE = 25;
  const quint16 FIELD_BORDER_SIZE = 2;
  const QBrush FIELD_BORDER_COLOR = QBrush(QColor(48, 48, 48));

  quint16 totalFieldSize = FIELD_SIZE + FIELD_BORDER_SIZE;
  quint16 totalBoardLength = FIELD_SIZE * 10 + FIELD_BORDER_SIZE * 9;

  for (quint8 i = 0; i < 9; i++) {
    this -> scene() -> addRect(totalFieldSize * i + FIELD_SIZE + 1, 0, FIELD_BORDER_SIZE, totalBoardLength, Qt::NoPen, FIELD_BORDER_COLOR);
    this -> scene() -> addRect(0, totalFieldSize * i + FIELD_SIZE + 1, totalBoardLength, FIELD_BORDER_SIZE, Qt::NoPen, FIELD_BORDER_COLOR);
  }

  if (targetBoard != nullptr) {
    // Drawing board...
  }
}

void GraphicBoard::mouseMoveEvent(QMouseEvent *event) {}

void GraphicBoard::mouseReleaseEvent(QMouseEvent *event) {}
