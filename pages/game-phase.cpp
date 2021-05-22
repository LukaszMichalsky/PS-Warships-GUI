#include "application.h"
#include "ui_application.h"

void Application::on_btnGameChat_released() {
  chatWindow -> setAttribute(Qt::WA_QuitOnClose, false);

  if (chatWindow -> isVisible() == false) {
    chatWindow -> show();
  } else {
    chatWindow -> activateWindow();
  }
}
