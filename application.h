#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
  class Application;
}
QT_END_NAMESPACE

class Application : public QMainWindow {
  Q_OBJECT

public:
  Application(QWidget *parent = nullptr);
  ~Application();

private slots:
  // Main menu UI controls slots
  void on_btnMainJoinGame_released();
  void on_btnMainStartServer_released();

  // Start server page UI controls slots
  void on_btnStartServer_released();
  void on_btnStartServerReturn_released();

  // Join game page UI controls slots
  void on_btnJoinGameReturn_released();
  void on_btnJoinGame_released();

private:
  Ui::Application *ui;
  QString playerUsername;

  QTcpServer* serverListener = nullptr;
  QTcpSocket* serverSocket = nullptr;
  QTcpSocket* clientSocket = nullptr;
};
