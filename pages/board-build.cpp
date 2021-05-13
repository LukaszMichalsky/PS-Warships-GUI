#include "application.h"
#include "ui_application.h"

void Application::on_btnBoardBuildRandom_released() {
  ui -> pagesWidget -> setCurrentIndex(5); // Go to board random builder page.
  on_btnBuildRandomRerandomize_released();
}

void Application::on_btnBoardBuildManual_released() {
  ui -> pagesWidget -> setCurrentIndex(6); // Go to board manual builder page.

  ui -> boardBuildManual -> setBoardState(GraphicBoardState::STATE_CREATING);
  ui -> boardBuildManual -> setGhostMode(4, ShipDirection::DIRECTION_HORIZONTAL);
  ui -> boardBuildManual -> setFocus();

  connect(ui -> boardBuildManual, &GraphicBoard::manualBoardBuildFinished, [&] () {
    ui -> btnBuildManualContinue -> setDisabled(false);
  });
}
