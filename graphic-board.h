#pragma once

#include "logic/logic.h"

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QVector>

class GraphicBoard : public QGraphicsView {
  private:
    static const quint16 FIELD_SIZE;
    static const quint16 FIELD_BORDER_SIZE;
    static const QBrush FIELD_BORDER_COLOR;

    static const quint16 totalFieldSize;
    static const quint16 totalBoardLength;

    static QVector<QPixmap*> horizontalShips;
    static QVector<QPixmap*> verticalShips;
    static QPixmap* waterTile;

    QGraphicsItemGroup* groupBoardItems = nullptr;
    QGraphicsItemGroup* groupShips = nullptr;
    QVector<ShipGroup*> renderedGroups;

    void initBoard();
    void initScene();
    void initResources();

  public:
    GraphicBoard(QWidget* parent = nullptr);
    GraphicBoard(QGraphicsScene* scene, QWidget* parent = nullptr);

    bool getClickedPoint(QMouseEvent *inputEvent, Point& outputPoint);
    void redrawBoard(const Board& targetBoard);

  protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};
