#include "application.h"
#include "ui_application.h"

void Application::on_btnMainStartServer_released() {
    ui -> pagesWidget -> setCurrentIndex(1);
}

void Application::on_btnMainJoinGame_released() {
    ui -> pagesWidget -> setCurrentIndex(2);
}
