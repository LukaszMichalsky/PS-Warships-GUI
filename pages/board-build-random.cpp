#include "application.h"
#include "ui_application.h"

void Application::on_btnBuildRandomReturn_released() {
  ui -> pagesWidget -> setCurrentIndex(4); // Go to board building mode selection page
}

void Application::on_btnBuildRandomRerandomize_released() {
  Board randomizedBoard;

  ui -> btnBuildRandomReturn -> setDisabled(true);
  ui -> btnBuildRandomRerandomize -> setDisabled(true);
  randomizeBoard(randomizedBoard);

  ui -> btnBuildRandomReturn -> setDisabled(false);
  ui -> btnBuildRandomRerandomize -> setDisabled(false);
  ui -> boardBuildRandom -> redrawBoard(randomizedBoard);
}
