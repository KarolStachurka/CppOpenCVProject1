#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "facedetector.h"

using namespace std;
using namespace cv;

class Camera
{
    const string FRONTAL_FACE_CASCADE = "Data/haarcascade_frontalface_alt.xml";
    const string PROFILE_FACE_CASCADE = "Data/haarcascade_profileface.xml";
public:
    VideoCapture openedCamera;

    Camera();
    void cameraOutput();
    void faceDetectionCameraOutput();
    void faceRecognitionCameraOutput();
    void setCameraOn();
    Mat takeModelFacePicture();
    Mat takePicture();
};

#endif // CAMERA_H
