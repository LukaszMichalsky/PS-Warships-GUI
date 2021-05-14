#include "application.h"
#include "ui_application.h"

QByteArray Application::waitForNetworkData() {
  while (clientSocket -> bytesAvailable() == 0) {
    QCoreApplication::processEvents();
    QThread::msleep(10);
  }

  if (clientSocket -> bytesAvailable() > 0) {
    QByteArray message = clientSocket -> read(1);
    quint8 length = message[0];

    while (clientSocket -> bytesAvailable() < length) {
      QCoreApplication::processEvents();
      QThread::msleep(10);
    }

    message.clear();
    message = clientSocket -> readAll();

    return message;
  }
}

void Application::sendNetworkData(const QByteArray &data) {
  quint8 messageLength = data.size();
  QByteArray message;

  message.append(messageLength);
  message.append(data);

  clientSocket -> write(message);
}
