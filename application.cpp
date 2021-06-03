#include "application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) : QMainWindow(parent), ui(new Ui::Application) {
  ui -> setupUi(this);
  ui -> pagesWidget -> setCurrentIndex(0);
  ui -> labelPID -> setText(QString("Application PID: %1").arg(QCoreApplication::applicationPid()));
}

Application::~Application() {
  delete ui;
}

void Application::on_btnEndQuit_released() {
  QCoreApplication::quit();
}
