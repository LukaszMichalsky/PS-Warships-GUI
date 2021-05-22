#pragma once

#include <QStackedWidget>

namespace Ui {
  class ChatWindow;
}

class ChatWindow : public QStackedWidget {
  Q_OBJECT

  public:
    explicit ChatWindow(QWidget* parent = nullptr);
    ~ChatWindow();

  private:
    Ui::ChatWindow *ui;
};
