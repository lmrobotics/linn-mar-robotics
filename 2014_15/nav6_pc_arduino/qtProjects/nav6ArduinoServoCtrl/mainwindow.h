#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "nav6/IMU.h"
#include "nav6/IMUAdvanced.h"
#include "arduino/serialMessageTransport.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool arduinoReady;
    IMUAdvanced *imu;
    QTimer pollingTimer;
    int lastServoPos;
    serialMessageTransport *robot;

private slots:
    void dialChanged();
    void processRxData();
    void processNav6RxData();
    void processTimer();
};

#endif // MAINWINDOW_H
