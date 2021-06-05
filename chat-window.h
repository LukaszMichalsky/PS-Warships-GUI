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

    void addMessage(QString message);

  private:
    Ui::ChatWindow *ui;

  signals:
    void messageSent(QString message);

  private slots:
    void on_btnSendMessage_released();
};
