#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Application;
}
QT_END_NAMESPACE

class Application : public QMainWindow {
    Q_OBJECT

public:
    Application(QWidget *parent = nullptr);
    ~Application();

private slots:
    // Main menu UI controls slots
    void on_btnMainJoinGame_released();
    void on_btnMainStartServer_released();

    // Start server page UI controls slots
    void on_btnStartServerReturn_released();

    // Join game page UI controls slots
    void on_btnJoinGameReturn_released();

private:
    Ui::Application *ui;
};
