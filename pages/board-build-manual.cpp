#include "application.h"
#include "ui_application.h"

void Application::on_btnBuildManualReturn_released() {
  ui -> pagesWidget -> setCurrentIndex(4); // Go to board building mode selection page.
}

void Application::on_btnBuildManualContinue_released() {
  ui -> pagesWidget -> setCurrentIndex(3); // Go to waiting area

  ui -> labelWaitingUsername -> setText("Waiting for second player");
  ui -> labelWaiting -> setText("...");

  QByteArray myUsername = playerUsername.toUtf8();
  sendNetworkData(myUsername);
  QString playerUsername = QString::fromUtf8(waitForNetworkData());

  ui -> labelWaitingUsername -> setText(QString("Player %1 is ready!").arg(playerUsername));
  ui -> labelWaiting -> setText("Starting game...");
}
