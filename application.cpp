#include "application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) : QMainWindow(parent), ui(new Ui::Application) {
  ui -> setupUi(this);
  ui -> pagesWidget -> setCurrentIndex(0);
  ui -> labelPID -> setText(QString("Application PID: %1").arg(QCoreApplication::applicationPid()));

  serverHistory.loadFromFile("server-history");

  for (QString entry : serverHistory.getAllEntries()) {
    ui -> listJoinHistory -> addItem(entry);
  }
}

Application::~Application() {
  delete ui;
}

void Application::on_btnEndQuit_released() {
  QCoreApplication::quit();
}

void Application::resetGame() {
  disconnect(clientSocket, &QTcpSocket::disconnected, this, &Application::showDisconnected);

  if (chatWindow -> isVisible() == true) {
    chatWindow -> close();
  }

  clientSocket -> readAll();
  clientSocket -> flush();
  clientSocket -> disconnectFromHost();
  clientSocket -> deleteLater();

  clientSocket = nullptr;
  ui -> btnEndQuit -> setEnabled(true);
}

void Application::on_listJoinHistory_itemClicked(QListWidgetItem *item) {
  QStringList entryList = item -> text().split(':', Qt::SplitBehaviorFlags::SkipEmptyParts, Qt::CaseSensitivity::CaseSensitive);

  ui -> textJoinGameAddress -> setText(entryList[0]);
  ui -> textJoinGamePort -> setText(entryList[1]);
}

void Application::showDisconnected() {
  ui -> pagesWidget -> setCurrentIndex(8); // Go to end page (on disconnect).
  ui -> labelEnd -> setText("Player has disconnected");

  resetGame();
}
