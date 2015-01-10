#include "dialog.h"
#include "ui_dialog.h"
#include <QtCore>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    capWebcam.open(0);
    if(!capWebcam.isOpened()){
        ui->txtbox->appendPlainText("error cam not connected");
        return;
    }

    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), this, SLOT(processStream()));
    Timer->start(20);

}
void Dialog::processStream(){
    capWebcam.read(mat);

    if(mat.empty())
        return;

    QImage img((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    ui->lblstream->setPixmap(QPixmap::fromImage(img));
}

Dialog::~Dialog()
{
    delete ui;
    delete Timer;
}
