#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sstream>
#include "arduino/PhysicalInterfaceClass.h"
#include "arduino/msgSetServoPosition.h"
#include "arduino/msgSetServoPositionResp.h"
#include "arduino/messageTransport.h"
#include "arduino/MessageTypesClass.h"
#include "arduino/BaseMessageClass.h"

#include <stdio.h>
using namespace Utility;
using namespace Messages;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    arduinoReady(true),
    lastServoPos(0)
{
    ui->setupUi(this);

    // initialize Arduino interface
    connect(ui->dial, SIGNAL(valueChanged(int)), this, SLOT(dialChanged()));
    connect(&PhysicalInterfaceClass::serial, SIGNAL(readyRead()), this, SLOT(processRxData()));
    PhysicalInterfaceClass::connect();
    msgSetServoPosition servoCtrl ((uint8)lastServoPos);
    servoCtrl.sendData();


    imu = new IMUAdvanced(100);
    connect(imu->serialPort, SIGNAL(readyRead()), this, SLOT(processNav6RxData()));

    connect(&pollingTimer, SIGNAL(timeout()), this, SLOT(processTimer()));
    // start timer with a 10 ms timeout
    pollingTimer.start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dialChanged()
{

    std::stringstream ss;
    uint8 dialValue = this->ui->dial->value();
    ss << this->ui->dial->value();;
    if (arduinoReady)
    {
       this->ui->label->setText(QString::fromStdString(ss.str()));
       msgSetServoPosition servoCtrl (dialValue);
       arduinoReady = false;
       servoCtrl.sendData();
    }
}

void MainWindow::processNav6RxData()
{
    imu->processRxData();
}

void MainWindow::processRxData()
{
    if (messageTransport::messageAvailable())
    {
        BaseMessageClass *tmp = messageTransport::getMessage();
        MessageTypesClass::messageId msgType = tmp->messageType();
        switch (msgType)
        {
        case MessageTypesClass::msgSetServoPositionRespId:
        {
            arduinoReady = true;
        }
        break;

        }
        delete tmp;
    }
    return;
} // processRxData

void MainWindow::processTimer()
{
    bool calibrating = imu->IsCalibrating();
    bool connected = imu->IsConnected();
    std::stringstream ss;

    ss << (connected ? "Connected" : "Not Connected");
    this->ui->labelConnected->setText(QString::fromStdString(ss.str()));
    ss.str("");
    ss.clear();

    ss << (calibrating ? "Calibrating" : "Calibrated");
    this->ui->labelCalibrating->setText(QString::fromStdString(ss.str()));
    ss.str("");
    ss.clear();

    ss << "Pitch " << imu->GetPitch();
    this->ui->labelPitch->setText(QString::fromStdString(ss.str()));
    ss.str("");
    ss.clear();

    ss << "Roll " << imu->GetRoll();
    this->ui->labelRoll->setText(QString::fromStdString(ss.str()));
    ss.str("");
    ss.clear();

    ss << "Yaw " << imu->GetYaw();
    this->ui->labelYaw->setText(QString::fromStdString(ss.str()));
    ss.str("");
    ss.clear();


    int newServoPos = 142 - (imu->GetPitch() + 70);
    if (arduinoReady && (newServoPos > 0) && (lastServoPos != newServoPos))
    {
        arduinoReady = false;
        lastServoPos = newServoPos;
        ss << newServoPos;
        this->ui->dial->setValue(newServoPos);
        this->ui->label->setText(QString::fromStdString(ss.str()));
        msgSetServoPosition servoCtrl (newServoPos);
        servoCtrl.sendData();
    }

}
