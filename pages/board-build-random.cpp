#include "application.h"
#include "ui_application.h"

void Application::on_btnBuildRandomReturn_released() {
  ui -> pagesWidget -> setCurrentIndex(4); // Go to board building mode selection page
}

void Application::on_btnBuildRandomRerandomize_released() {
  Board* randomizedBoard = new Board();

  ui -> btnBuildRandomReturn -> setDisabled(true);
  ui -> btnBuildRandomRerandomize -> setDisabled(true);
  randomizeBoard(*randomizedBoard);

  ui -> btnBuildRandomReturn -> setDisabled(false);
  ui -> btnBuildRandomRerandomize -> setDisabled(false);
  ui -> boardBuildRandom -> redrawBoard(*randomizedBoard);

  boardMy = randomizedBoard;
}

void Application::on_btnBuildRandomContinue_released() {
  ui -> pagesWidget -> setCurrentIndex(3); // Go to waiting area

  ui -> labelWaitingUsername -> setText("Waiting for second player");
  ui -> labelWaiting -> setText("...");

  startGame();
}
