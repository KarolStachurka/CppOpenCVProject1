#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_showVideoButton_clicked()
{
    Camera camera;
    camera.setCameraOn();
    camera.cameraOutput();
}

void MainWindow::on_detectFaceButton_clicked()
{
    Camera camera;
    camera.setCameraOn();
    camera.faceDetectionCameraOutput();
}


void MainWindow::on_recognizeFaceButton_clicked()
{
    Camera camera;
    camera.setCameraOn();
    camera.faceRecognitionCameraOutput();

}

void MainWindow::on_addModelButton_clicked()
{
    InputOutput io;
    int label = io.getNewModelLabel();
    QString qModelName =ui->newFaceModelName->text();
    string modelName = qModelName.toStdString();
    if(qModelName.isEmpty())
        return;
    io.generateInput(modelName,label);
    ui->newFaceModelName->clear();
}

void MainWindow::on_removeModelButton_clicked()
{
    InputOutput io;
    QString qModelName =ui->modelToRemoveName->text();
    string modelName = qModelName.toStdString();
    if(qModelName.isEmpty())
        return;
    io.removeModelFromFacesDatabase("faces.csv",modelName,';');
    ui->modelToRemoveName->clear();
}

void MainWindow::on_takePictureButton_clicked()
{
    InputOutput io;
    io.saveFrame();
}
