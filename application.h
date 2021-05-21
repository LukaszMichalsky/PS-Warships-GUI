#pragma once

#include "logic/logic.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
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
    void on_btnBuildRandomContinue_released();

    // Board manual builder UI controls slots.
    void on_btnBuildManualReturn_released();
    void on_btnBuildManualContinue_released();

    // Game phase page UI controls slots.
    void on_btnGameShoot_released();

    // Other slots
    void animateAttack(Point attackPoint, bool thisPlayer, bool missedShoot);
    void getOpponentAction();
    void opponentBoardFieldSelected(Point& selectedPoint);

  private:
    Ui::Application *ui;
    QString playerUsername;
    QString otherPlayerUsername;

    QTcpServer* serverListener = nullptr;
    QTcpSocket* clientSocket = nullptr;

    void randomizeBoard(Board& targetBoard);
    void startGame();

    QByteArray waitForNetworkData();
    void sendNetworkData(const QByteArray &data);

    Board* boardMy = nullptr;
    Board* boardOpponent = new Board();

    board_size_t myDrownedShips = 0;
    Point pointToShoot = Point(0, 0);
    QMovie* animation = nullptr;
    QString* lastAttackState = new QString();
};
