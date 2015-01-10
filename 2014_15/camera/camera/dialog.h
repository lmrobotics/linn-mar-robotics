#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <cv.h>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class Dialog;
}

using namespace cv;
using namespace std;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
public slots:
    void processStream();
private:
    Ui::Dialog *ui;
    VideoCapture capWebcam;
    Mat mat;
    QTimer* Timer;
};

#endif // DIALOG_H
