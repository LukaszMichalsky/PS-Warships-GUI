#pragma once

#include "logic/logic.h"

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

class GraphicBoard : public QGraphicsView {
  private:
    static const quint16 FIELD_SIZE;
    static const quint16 FIELD_BORDER_SIZE;
    static const QBrush FIELD_BORDER_COLOR;

    static const quint16 totalFieldSize;
    static const quint16 totalBoardLength;

    QGraphicsItemGroup* groupBoardItems = nullptr;
    QGraphicsItemGroup* groupShips = nullptr;

    void initBoard();
    void initScene();

  public:
    GraphicBoard(QWidget* parent = nullptr);
    GraphicBoard(QGraphicsScene* scene, QWidget* parent = nullptr);

    bool getClickedPoint(QMouseEvent *inputEvent, Point& outputPoint);
    void redrawBoard(const Board& targetBoard);

  protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};
