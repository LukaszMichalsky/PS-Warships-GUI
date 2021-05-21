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

*/

void Application::getOpponentAction() {
  QByteArray incomingData = waitForNetworkData();
  QString incomingString = QString::fromUtf8(incomingData);
  QStringList stringData = incomingString.split("_", Qt::SkipEmptyParts, Qt::CaseSensitivity::CaseSensitive);

  if (stringData[0] == "ATTACK" && stringData[1] == "REQUEST") {
    board_size_t attackX = stringData[2].toUInt();
    board_size_t attackY = stringData[3].toUInt();
    bool targetHit;

    boardMy -> shoot(targetHit, Point(attackX, attackY));
    ShipState shipStateAfterShoot = boardMy -> getShipPointer(Point(attackX, attackY)) -> getShipState();

    if (shipStateAfterShoot == ShipState::STATE_MISSED) {
      sendNetworkData(QString("ATTACK_RESPONSE_%1_%2_MISSED").arg(attackX).arg(attackY).toUtf8());
    } else if (shipStateAfterShoot == ShipState::STATE_HIT) {
      sendNetworkData(QString("ATTACK_RESPONSE_%1_%2_HIT").arg(attackX).arg(attackY).toUtf8());
    } else if (shipStateAfterShoot == ShipState::STATE_DROWNED) {
      myDrownedShips++;

      if (myDrownedShips < 10) {
        sendNetworkData(QString("ATTACK_RESPONSE_%1_%2_DROWNED").arg(attackX).arg(attackY).toUtf8());
      } else {
        sendNetworkData(QString("ATTACK_RESPONSE_%1_%2_WIN").arg(attackX).arg(attackY).toUtf8());
      }
    }

    ui -> boardGameMy -> redrawShoots(*boardMy);
    ui -> boardGameOpponent -> setBoardState(GraphicBoardState::STATE_PLAYING);
    ui -> labelGameHint -> setText("Select field for attacking on opponent's board...");
  }

  if (stringData[0] == "ATTACK" && stringData[1] == "RESPONSE") {
    board_size_t attackX = stringData[2].toUInt();
    board_size_t attackY = stringData[3].toUInt();

    if (stringData[4] == "MISSED") {
      boardOpponent -> setShip(Ship(Point(attackX, attackY), ShipState::STATE_MISSED));
    } else if (stringData[4] == "HIT") {
      boardOpponent -> setShip(Ship(Point(attackX, attackY), ShipState::STATE_HIT));
    } else if (stringData[4] == "DROWNED") {
      boardOpponent -> setShip(Ship(Point(attackX, attackY), ShipState::STATE_DROWNED));
    }

    ui -> boardGameOpponent -> redrawShoots(*boardOpponent);
    ui -> boardGameOpponent -> setBoardState(GraphicBoardState::STATE_NONE);
    ui -> btnGameShoot -> setEnabled(false);

    if (stringData[4] != "WIN") {
      getOpponentAction();
    }
  }
}
