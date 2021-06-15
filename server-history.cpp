#include "server-history.h"

ServerHistory::ServerHistory() {
  history = QVector<QString>();
}

void ServerHistory::addEntry(QString hostName, quint16 port) {
  QString newEntry = QString("%1:%2").arg(hostName).arg(port);

  if (history.contains(newEntry) == true) {
    history.removeAll(newEntry);
  }

  history.push_front(newEntry);
}

QVector<QString> ServerHistory::getAllEntries() {
  return history;
}

void ServerHistory::loadFromFile(QString filePath) {
  QFile file(filePath);

  if (file.exists() == true) {
    if (file.open(QFile::ReadOnly) == true) {
      history.clear();
      QTextStream fileStream(&file);

      while (fileStream.atEnd() == false) {
        QString dataLine = fileStream.readLine().trimmed();

        if (dataLine.isEmpty() == false) {
          history.push_back(dataLine);
        }
      }

      file.close();
    }
  }
}

void ServerHistory::saveToFile(QString filePath) {
  QFile file(filePath);

  if (file.open(QFile::WriteOnly | QFile::Truncate) == true) {
    for (QString entry : history) {
      QByteArray entryBytes = entry.toUtf8().append('\n');
      file.write(entryBytes);
    }

    file.close();
  }
}
