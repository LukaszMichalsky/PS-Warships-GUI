#include "application.h"
#include "ui_application.h"

void Application::on_btnGameShoot_released() {
  sendNetworkData(QString("ATTACK_REQUEST_%1_%2").arg(pointToShoot.getX()).arg(pointToShoot.getY()).toUtf8());
}
