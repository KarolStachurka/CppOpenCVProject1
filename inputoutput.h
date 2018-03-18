#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/face.hpp"
#include "opencv2/core.hpp"
#include "camera.h"
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace cv;

class InputOutput
{
public:
    InputOutput();
    void readCSV(const string& filename, vector<Mat>& images, vector<int>& labels, char separator);
    Ptr<face::LBPHFaceRecognizer> generateModel();
    CascadeClassifier loadFaceCascade(string filepath);
    void generateInput(string modelName,int label);
    void generateDirectory(string fileName);
    void removeModelFromFacesDatabase(string filename, string name, char separator);
    void writeToCSVfile(string data);
    int getNewModelLabel();
    map<int,string> getModelNamesFromCSVfile();
};

#endif // INPUTOUTPUT_H
