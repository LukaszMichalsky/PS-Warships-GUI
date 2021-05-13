#pragma once

#include "logic/logic.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
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
    // Main menu UI controls slots.
    void on_btnMainJoinGame_released();
    void on_btnMainStartServer_released();

    // Start server page UI controls slots.
    void on_btnStartServer_released();
    void on_btnStartServerReturn_released();

    // Join game page UI controls slots.
    void on_btnJoinGameReturn_released();
    void on_btnJoinGame_released();

    // Board building mode selection page UI controls slots.
    void on_btnBoardBuildRandom_released();
    void on_btnBoardBuildManual_released();

    // Board random builder UI controls slots.
    void on_btnBuildRandomReturn_released();
    void on_btnBuildRandomRerandomize_released();

    // Board manual builder UI controls slots.
    void on_btnBuildManualReturn_released();

  private:
    Ui::Application *ui;
    QString playerUsername;

    QTcpServer* serverListener = nullptr;
    QTcpSocket* serverSocket = nullptr;
    QTcpSocket* clientSocket = nullptr;

    void randomizeBoard(Board& targetBoard);
};
