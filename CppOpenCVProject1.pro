#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T12:27:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CppOpenCVProject1
TEMPLATE = app
CONFIG += console c++11
CONFIG += link_pkgconfig
PKGCONFIG += x11

INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /home/august/dlib

LIBS += -L/usr/local/lib \
-lopencv_core \
-lopencv_imgproc \
-lopencv_imgcodecs \
-lopencv_highgui \
-lopencv_ml \
-lopencv_videoio \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_objdetect \
-lopencv_contrib \
-lopencv_legacy \
-lopencv_flann \
-lopencv_face \
-pthread

SOURCES += main.cpp \
        mainwindow.cpp \
        facedetector.cpp \
        camera.cpp \
        inputoutput.cpp \
        ../../dlib/dlib/all/source.cpp

HEADERS  += mainwindow.h \
        facedetector.h \
        camera.h \
        inputoutput.h

FORMS    += mainwindow.ui
