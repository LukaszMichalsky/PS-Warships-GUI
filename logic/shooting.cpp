#include "application.h"
#include "ui_application.h"

void Application::on_btnGameShoot_released() {
  ui -> labelGameHint -> setText("Waiting for opponent's turn...");
  sendNetworkData(QString("ATTACK_REQUEST_%1_%2").arg(pointToShoot.getX()).arg(pointToShoot.getY()).toUtf8());
}
