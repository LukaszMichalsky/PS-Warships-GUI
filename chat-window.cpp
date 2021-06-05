#include "chat-window.h"
#include "ui_chat-window.h"

ChatWindow::ChatWindow(QWidget* parent) : QStackedWidget(parent), ui(new Ui::ChatWindow) {
  ui -> setupUi(this);

  connect(ui -> textMessage, &QLineEdit::textChanged, [&] (const QString &newText) {
    if (newText.isEmpty() == true) {
      ui -> btnSendMessage -> setEnabled(false);
    } else {
      ui -> btnSendMessage -> setEnabled(true);
    }
  });
}

ChatWindow::~ChatWindow() {
  delete ui;
}

void ChatWindow::addMessage(QString message) {
  QListWidgetItem* newItem = new QListWidgetItem();
  newItem -> setText(message);

  ui -> listMessages -> addItem(newItem);
}

void ChatWindow::on_btnSendMessage_released() {
  emit messageSent(ui -> textMessage -> text());
  ui -> textMessage -> clear();
}
