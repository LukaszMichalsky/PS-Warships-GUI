#include "application.h"
#include "ui_application.h"

void Application::on_btnStartServerReturn_released() {
    ui -> pagesWidget -> setCurrentIndex(0); // Go to main menu page
}

void Application::on_btnStartServer_released() {
    ui -> pagesWidget -> setCurrentIndex(3); // Go to waiting page
}
