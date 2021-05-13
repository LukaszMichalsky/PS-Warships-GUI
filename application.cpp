#include "application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) : QMainWindow(parent), ui(new Ui::Application) {
  ui -> setupUi(this);
  ui -> pagesWidget -> setCurrentIndex(4);
}

Application::~Application() {
  delete ui;
}
