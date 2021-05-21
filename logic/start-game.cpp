#include "application.h"
#include "ui_application.h"

void Application::startGame() {
  QByteArray myUsername = playerUsername.toUtf8();
  sendNetworkData(myUsername);
  otherPlayerUsername = QString::fromUtf8(waitForNetworkData());

  ui -> labelWaitingUsername -> setText(QString("Player %1 is ready!").arg(otherPlayerUsername));
  ui -> labelWaiting -> setText("Starting game...");

  QTimer::singleShot(1500, [&] () {
    ui -> pagesWidget -> setCurrentIndex(7); // Go to game page.
    ui -> boardGameMy -> redrawShips(*boardMy);
    ui -> labelGameTitle -> setText("Playing with: " + otherPlayerUsername);

    if (serverListener == nullptr) { // I am the client.
      ui -> labelGameHint -> setText("Waiting for opponent's turn...");
      getOpponentAction();
    } else { // I am the server.
      ui -> boardGameOpponent -> setBoardState(GraphicBoardState::STATE_PLAYING);
      ui -> labelGameHint -> setText("Select field for attacking on opponent's board...");
    }

    connect(ui -> boardGameOpponent, &GraphicBoard::getSelectedPoint, this, &Application::opponentBoardFieldSelected);
  });
}
