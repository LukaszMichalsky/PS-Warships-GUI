#pragma once

#include "logic/logic.h"

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QVector>

enum class GraphicBoardState : int {
  STATE_NONE = 0,
  STATE_CREATING = 1,
  STATE_PLAYING = 2
};

class GraphicBoard : public QGraphicsView {
  Q_OBJECT

  private:
    static const quint16 FIELD_SIZE;
    static const quint16 FIELD_BORDER_SIZE;
    static const QBrush FIELD_BORDER_COLOR;

    static const quint16 totalFieldSize;
    static const quint16 totalBoardLength;

    QGraphicsItemGroup* groupGhostItems = nullptr;
    QGraphicsItemGroup* groupBoardItems = nullptr;
    QGraphicsItemGroup* groupShips = nullptr;
    QVector<ShipGroup*> renderedGroups;

    bool ghostModeEnabled = false; // Ghost mode allows user to see ship position when moving cursor on board.
    ShipDirection ghostModeCurrentDirection = ShipDirection::DIRECTION_HORIZONTAL;
    board_size_t ghostModeCurrentSize = 4;
    QPixmap* ghostModeCurrentShip = nullptr;

    void initBoard();
    void initScene();
    void initResources();

    Board manualBuildBoard;
    quint8 manualBuildShipsLeft = 1;
    quint8 manualBuildCurrentSize = 4;

    QMouseEvent* lastEvent = nullptr;
    GraphicBoardState boardState = GraphicBoardState::STATE_NONE;

    void clickStateCreating(QMouseEvent* event);
    void clickStatePlaying(QMouseEvent* event);

  public:
    GraphicBoard(QWidget* parent = nullptr);
    GraphicBoard(QGraphicsScene* scene, QWidget* parent = nullptr);

    static QVector<QPixmap*> horizontalShips;
    static QVector<QPixmap*> verticalShips;
    static QPixmap* waterTile;

    bool getClickedPoint(QMouseEvent *inputEvent, Point& outputPoint);
    void redrawBoard(const Board& targetBoard);
    void setBoardState(GraphicBoardState newState);
    Board* getManualBoard();

    void setGhostMode(ship_size_t shipSize, ShipDirection shipDirection);
    void disableGhostMode();

  protected:
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

  signals:
    void manualBoardBuildFinished();
};
