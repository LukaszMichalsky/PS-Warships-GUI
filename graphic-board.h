#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

class GraphicBoard : public QGraphicsView {
  private:
    void initScene();

  public:
    GraphicBoard(QWidget* parent = nullptr);
    GraphicBoard(QGraphicsScene* scene, QWidget* parent = nullptr);

  protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};
