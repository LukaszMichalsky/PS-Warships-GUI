#include "application.h"
#include "ui_application.h"

void Application::on_btnJoinGameReturn_released() {
  ui -> pagesWidget -> setCurrentIndex(0); // Go to main menu page
}

void Application::on_btnJoinGame_released() {
  QString newUsername = ui -> textJoinGameName -> text();
  QString newHostname = ui -> textJoinGameAddress -> text();
  QString newPort = ui -> textJoinGamePort -> text();

  playerUsername = (newUsername.isEmpty() == true) ? ui -> textJoinGameName -> placeholderText() : newUsername;
  QString hostname = (newHostname.isEmpty() == true) ? ui -> textJoinGameAddress -> placeholderText() : newHostname;
  quint16 port = (newPort.isEmpty() == true) ? ui -> textJoinGamePort -> placeholderText().toUInt() : newPort.toUInt();

  if (port == 0 || port < 1024 || port > 65535) {
    QMessageBox::critical(this, "Error", "Invalid port, must be a proper number in range from 1024 to 65535");
    return;
  }

  ui -> pagesWidget -> setCurrentIndex(3); // Go to waiting area

  ui -> labelWaitingUsername -> setText("Logging as " + playerUsername);
  ui -> labelWaiting -> setText("Trying to connect to " + hostname + "...");

  clientSocket = new QTcpSocket();
  clientSocket -> connectToHost(hostname, port, QTcpSocket::ReadWrite, QTcpSocket::NetworkLayerProtocol::IPv4Protocol);

  connect(clientSocket, &QTcpSocket::connected, [=] () {
    ui -> labelWaiting -> setText("Connected to server!");

    QTimer::singleShot(1500, [&] () {
      ui -> pagesWidget -> setCurrentIndex(4); // Go to board building mode selection page
    });
  });
}
