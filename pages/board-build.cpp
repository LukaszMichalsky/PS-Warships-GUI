#include "application.h"
#include "ui_application.h"

void Application::on_btnBoardBuildRandom_released() {
  ui -> pagesWidget -> setCurrentIndex(5); // Go to board random builder page
  on_btnBuildRandomRerandomize_released();
}
