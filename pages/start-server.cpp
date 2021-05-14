#include "application.h"
#include "ui_application.h"

void Application::on_btnStartServerReturn_released() {
  ui -> pagesWidget -> setCurrentIndex(0); // Go to main menu page
}

void Application::on_btnStartServer_released() {
  QString newUsername = ui -> textStartServerName -> text();
  QString newPort = ui -> textStartServerPort -> text();

  playerUsername = (newUsername.isEmpty() == true) ? ui -> textStartServerName -> placeholderText() : newUsername;
  quint16 port = (newPort.isEmpty() == true) ? ui -> textStartServerPort -> placeholderText().toUInt() : newPort.toUInt();

  if (port == 0 || port < 1024 || port > 65535) {
    QMessageBox::critical(this, "Error", "Invalid port, must be a proper number in range from 1024 to 65535");
    return;
  }

  ui -> labelWaitingUsername -> setText("Logging as " + playerUsername);
  ui -> pagesWidget -> setCurrentIndex(3); // Go to waiting page

  serverListener = new QTcpServer();
  serverListener -> listen(QHostAddress::Any, port);

  connect(serverListener, &QTcpServer::newConnection, [=] () {
    clientSocket = serverListener -> nextPendingConnection();
    ui -> labelWaiting -> setText("Player connected!");

    QTimer::singleShot(1500, [=] () {
      ui -> pagesWidget -> setCurrentIndex(4); // Go to board building mode selection page
    });
  });
}
