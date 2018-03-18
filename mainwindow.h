#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "camera.h"
#include "inputoutput.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_showVideoButton_clicked();

    void on_detectFaceButton_clicked();

    void on_recognizeFaceButton_clicked();

    void on_addModelButton_clicked();

    void on_removeModelButton_clicked();

    void on_takePictureButton_clicked();

private:
    Ui::MainWindow *ui;
    Camera camera;
};

#endif // MAINWINDOW_H
