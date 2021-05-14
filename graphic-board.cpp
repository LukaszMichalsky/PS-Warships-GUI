#include "graphic-board.h"

const quint16 GraphicBoard::FIELD_SIZE = 25;
const quint16 GraphicBoard::FIELD_BORDER_SIZE = 2;
const QBrush GraphicBoard::FIELD_BORDER_COLOR = QBrush(QColor(48, 48, 48));

const quint16 GraphicBoard::totalFieldSize = FIELD_SIZE + FIELD_BORDER_SIZE;
const quint16 GraphicBoard::totalBoardLength = FIELD_SIZE * 10 + FIELD_BORDER_SIZE * 9;

QPixmap* GraphicBoard::waterTile = nullptr;
QPixmap* GraphicBoard::splashHit = nullptr;
QPixmap* GraphicBoard::splashMiss = nullptr;
QPixmap* GraphicBoard::splashDrowned = nullptr;

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

void GraphicBoard::setBoardState(GraphicBoardState newState) {
  boardState = newState;
}

Board* GraphicBoard::getManualBoard() {
  return &manualBuildBoard;
}

void GraphicBoard::keyReleaseEvent(QKeyEvent *event) {
  if (ghostModeEnabled == true) {
    if (event -> key() == Qt::Key::Key_R) {
      if (ghostModeCurrentDirection == ShipDirection::DIRECTION_HORIZONTAL) {
        setGhostMode(ghostModeCurrentSize, ShipDirection::DIRECTION_VERTICAL);
      } else {
        setGhostMode(ghostModeCurrentSize, ShipDirection::DIRECTION_HORIZONTAL);
      }

      if (lastEvent != nullptr) {
        mouseMoveEvent(lastEvent);
      }
    }
  }
}

void GraphicBoard::mouseMoveEvent(QMouseEvent *event) {
  if (ghostModeEnabled == true) {
    if (ghostModeCurrentShip != nullptr) {
      Point currentField(0, 0);
      Point lastField(-1, -1);

      for (QGraphicsItem* ghostShip : groupGhostItems -> childItems()) {
        if (ghostShip != nullptr) {
          delete ghostShip;
        }
      }

      if (getClickedPoint(event, currentField) == true) {
        if (currentField.equals(lastField) == false) {
          if (ShipGroup::checkPosition(&manualBuildBoard, currentField, ghostModeCurrentSize, ghostModeCurrentDirection) == true) {
            QGraphicsPixmapItem* newGhostShip = new QGraphicsPixmapItem(*ghostModeCurrentShip);
            newGhostShip -> setPos(currentField.getX() * totalFieldSize, currentField.getY() * totalFieldSize);
            groupGhostItems -> addToGroup(newGhostShip);

            lastField.setX(currentField.getX());
            lastField.setY(currentField.getY());

            lastEvent = event;
          }
        }
      }
    }
  }
}

void GraphicBoard::mouseReleaseEvent(QMouseEvent *event) {
  switch (boardState) {
    case GraphicBoardState::STATE_NONE: {
      // Do nothing
    } case GraphicBoardState::STATE_PLAYING: {
      clickStatePlaying(event);
      break;
    } case GraphicBoardState::STATE_CREATING: {
      clickStateCreating(event);
      break;
    }
  }
}
