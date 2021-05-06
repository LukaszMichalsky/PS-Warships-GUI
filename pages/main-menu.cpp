#include "application.h"
#include "ui_application.h"

void Application::on_btnMainStartServer_released() {
  ui -> pagesWidget -> setCurrentIndex(1); // Go to server start page
}

void Application::on_btnMainJoinGame_released() {
  ui -> pagesWidget -> setCurrentIndex(2); // Go to join game page
}
