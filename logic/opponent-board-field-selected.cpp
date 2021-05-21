#include "application.h"
#include "ui_application.h"

QVector<char> characters({'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'});

void Application::opponentBoardFieldSelected(Point& selectedPoint) {

  char X = characters[selectedPoint.getX()];
  board_size_t Y = selectedPoint.getY() + 1;

  ui -> labelGameHint -> setText(QString("Selected field (%1, %2) - ready to shoot!").arg(X).arg(Y));
  ui -> btnGameShoot -> setEnabled(true);
}
