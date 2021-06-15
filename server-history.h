#pragma once

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QVector>

class ServerHistory : public QObject {
  Q_OBJECT

  private:
    QVector<QString> history;

  public:
    ServerHistory();

    void addEntry(QString hostName, quint16 port);
    QVector<QString> getAllEntries();

    void loadFromFile(QString filePath);
    void saveToFile(QString filePath);
};
