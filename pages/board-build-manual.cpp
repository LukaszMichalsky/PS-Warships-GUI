#include "application.h"
#include "ui_application.h"

void Application::on_btnBuildManualReturn_released() {
  ui -> pagesWidget -> setCurrentIndex(4); // Go to board building mode selection page.
}
