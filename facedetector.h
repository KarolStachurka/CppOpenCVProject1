#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/face.hpp"
#include "opencv2/core.hpp"
#include <fstream>
#include <sstream>
#include "inputoutput.h"

using namespace std;
using namespace cv;

class FaceDetector
{
public:
    //Content
    Mat frameWithoutFacesDetected;
    Mat frameWithFacesDetected;
    Mat frameWithFacesRecognized;
    int numberOfFaces;
    vector<Rect> detectedFaces;
    map<int,string> modelNames;
    Ptr<face::LBPHFaceRecognizer> model;
    CascadeClassifier faceCascade;
    CascadeClassifier profileCascade;

    //constructors
    FaceDetector();
    FaceDetector(Mat frame, CascadeClassifier classifier);
    FaceDetector(Mat frame,CascadeClassifier classifier, Ptr<face::LBPHFaceRecognizer> model, map<int,string> modelNames);

    //setters
    void setFrame(Mat newFrame);
    void setfaceCascade(CascadeClassifier faceCascade);
    void setProfileCascade(CascadeClassifier profileCascade);
    void setDetectedFaces();
    void setModelNames(map<int,string> names);
    void setFrameWithFacesDetected();
    void setFrameWithFacesRecognized();

    //getters
    CascadeClassifier getFaceCascade();
    vector<Rect> getDetectedFaces();
    Mat getFrameWithoutFacesDetected();
    Mat getFrameWithFacesDetected();
    Mat getFrameWithFacesRecognized();

    //Main Features
    Mat detectFaceFrontal(Mat frame);
    Mat detectFaceAll(Mat frame);
    Mat recognizeFace(Mat frame);
    Mat faceSwap(Mat frame);


};

#endif // FACEDETECTOR_H
