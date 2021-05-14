#include "application.h"
#include "ui_application.h"

void Application::startGame() {
  QByteArray myUsername = playerUsername.toUtf8();
  sendNetworkData(myUsername);
  otherPlayerUsername = QString::fromUtf8(waitForNetworkData());

  ui -> labelWaitingUsername -> setText(QString("Player %1 is ready!").arg(otherPlayerUsername));
  ui -> labelWaiting -> setText("Starting game...");

  QTimer::singleShot(1500, [&] () {
    ui -> pagesWidget -> setCurrentIndex(7); // Go to game page.
    ui -> boardGameMy -> redrawShips(*boardMy);
  });
}
