#include "application.h"
#include "ui_application.h"

/*

  NETWORK DOCUMENTATION
  ---------------------
  Message types
    1. ATTACK_REQUEST_X_Y
      - where X is X coord of selected point, from 0 (inclusive) to 9 (inclusive)
      - where Y is Y coord of selected point, from 0 (inclusive) to 9 (inclusive)

    2. ATTACK_RESPONSE_X_Y_MSG
      - where X, Y are point coordinates (same as above)
      - where MSG is attack result, one from the following: 'DROWNED, HIT, MISSED, WIN'

    3. CHAT_MESSAGE_MSG
      - where MSG is the actual chat message

*/

void Application::animateAttack(Point attackPoint, bool thisPlayer, bool missedShoot) {
  int baseX = thisPlayer == true ? 20 : 440;
  int baseY = 70;
  int fieldSize = ui -> boardGameMy -> getTotalFieldSize();

  baseX += 35;
  baseY += 37;

  baseX += attackPoint.getX() * fieldSize;
  baseY += attackPoint.getY() * fieldSize;

  if (animation != nullptr) {
    delete animation;
  }

  if (missedShoot == true) {
    animation = new QMovie(":/resources/animations/shoot-miss.gif");
  } else {
    animation = new QMovie(":/resources/animations/shoot-hit.gif");
  }

  ui -> labelGameAnimation -> move(baseX, baseY);
  ui -> labelGameAnimation -> setMovie(animation);

  ui -> boardGameMy -> redrawShoots(*boardMy);
  ui -> boardGameOpponent -> redrawShoots(*boardOpponent);

  animation -> start();
}

void Application::getOpponentAction() {
  QByteArray incomingData = waitForNetworkData();
  QString incomingString = QString::fromUtf8(incomingData);
  QStringList stringData = incomingString.split("_", Qt::SkipEmptyParts, Qt::CaseSensitivity::CaseSensitive);

  if (incomingData.isEmpty() == true) {
    return; // Application is stopping.
  }

  if (stringData[0] == "CHAT" && stringData[1] == "MESSAGE") {
    chatWindow -> addMessage(stringData[2]);

    if (chatWindow -> isVisible() == false) {
      chatWindow -> show();
    } else {
      chatWindow -> activateWindow();
    }
  }

  ui -> boardGameOpponent -> setBoardState(GraphicBoardState::STATE_NONE);

  if (stringData[0] == "ATTACK" && stringData[1] == "REQUEST") {
    board_size_t attackX = stringData[2].toUInt();
    board_size_t attackY = stringData[3].toUInt();
    bool targetHit;

    boardMy -> shoot(targetHit, Point(attackX, attackY));
    ShipState shipStateAfterShoot = boardMy -> getShipPointer(Point(attackX, attackY)) -> getShipState();

    if (shipStateAfterShoot == ShipState::STATE_MISSED) {
      animateAttack(Point(attackX, attackY), true, true);
      sendNetworkData(QString("ATTACK_RESPONSE_%1_%2_MISSED").arg(attackX).arg(attackY).toUtf8());
    } else if (shipStateAfterShoot == ShipState::STATE_HIT) {
      animateAttack(Point(attackX, attackY), true, false);
      sendNetworkData(QString("ATTACK_RESPONSE_%1_%2_HIT").arg(attackX).arg(attackY).toUtf8());
    } else if (shipStateAfterShoot == ShipState::STATE_DROWNED) {
      animateAttack(Point(attackX, attackY), true, false);
      myDrownedShips++;

      if (myDrownedShips < 10) {
        sendNetworkData(QString("ATTACK_RESPONSE_%1_%2_DROWNED").arg(attackX).arg(attackY).toUtf8());
      } else {
        sendNetworkData(QString("ATTACK_RESPONSE_%1_%2_WIN").arg(attackX).arg(attackY).toUtf8());
      }
    }

    QTimer::singleShot(2000, [=] () {
      if (myDrownedShips < 10) {
        if (shipStateAfterShoot == ShipState::STATE_MISSED) { // Opponent's attack chain stops.
          ui -> boardGameOpponent -> setBoardState(GraphicBoardState::STATE_PLAYING);
          ui -> labelGameHint -> setText("Select field for attacking on opponent's board...");
        }
      } else {
        ui -> pagesWidget -> setCurrentIndex(8); // Go to end page (as loser).
        ui -> labelEnd -> setText("You LOST the game...");

        resetGame();
      }
    });
  }

  if (stringData[0] == "ATTACK" && stringData[1] == "RESPONSE") {
    board_size_t attackX = stringData[2].toUInt();
    board_size_t attackY = stringData[3].toUInt();

    if (stringData[4] == "MISSED") {
      boardOpponent -> setShip(Ship(Point(attackX, attackY), ShipState::STATE_MISSED));
      animateAttack(Point(attackX, attackY), false, true);
    } else if (stringData[4] == "HIT") {
      boardOpponent -> setShip(Ship(Point(attackX, attackY), ShipState::STATE_HIT));
      animateAttack(Point(attackX, attackY), false, false);
    } else if (stringData[4] == "DROWNED") {
      boardOpponent -> setShip(Ship(Point(attackX, attackY), ShipState::STATE_DROWNED));
      setDrownedShip(*boardOpponent, Point(attackX, attackY));
      animateAttack(Point(attackX, attackY), false, false);
    } else if (stringData[4] == "WIN") {
      boardOpponent -> setShip(Ship(Point(attackX, attackY), ShipState::STATE_DROWNED));
      setDrownedShip(*boardOpponent, Point(attackX, attackY));
      animateAttack(Point(attackX, attackY), false, false);

      delete lastAttackState;
      lastAttackState = new QString("WIN");
    }

    ui -> btnGameShoot -> setEnabled(false);

    QTimer::singleShot(2000, [=] () {
      if (*lastAttackState == "WIN") {
        ui -> pagesWidget -> setCurrentIndex(8); // Go to end page (as winner).
        ui -> labelEnd -> setText("You WIN the game! CONGRATULATIONS!");

        resetGame();
      } else {
        ui -> labelGameHint -> setText("Select field for attacking on opponent's board...");

        if (stringData[4] == "MISSED" || stringData[4] == "WIN") { // Stop attack chain (another player's turn).
          ui -> labelGameHint -> setText("Waiting for opponent's turn...");
        } else {
          ui -> boardGameOpponent -> setBoardState(GraphicBoardState::STATE_PLAYING);
        }
      }
    });
  }
}
