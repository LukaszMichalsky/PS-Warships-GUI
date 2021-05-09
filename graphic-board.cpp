#include "graphic-board.h"

GraphicBoard::GraphicBoard(QWidget* parent) : QGraphicsView(parent) { initScene(); }
GraphicBoard::GraphicBoard(QGraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent) { initScene(); }

void GraphicBoard::initScene() {
  QGraphicsScene* boardScene = new QGraphicsScene(0, 0, 0, 0, this);
  this -> setScene(boardScene);
}

void GraphicBoard::mouseMoveEvent(QMouseEvent *event) {}

void GraphicBoard::mouseReleaseEvent(QMouseEvent *event) {}
