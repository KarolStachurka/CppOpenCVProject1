#include "facedetector.h"

FaceDetector::FaceDetector()
{

}
FaceDetector::FaceDetector(Mat frame, CascadeClassifier classifier)
{
    this->frameWithoutFacesDetected = frame;
    this->faceCascade = classifier;
}

FaceDetector::FaceDetector(Mat frame, CascadeClassifier classifier, Ptr<face::LBPHFaceRecognizer> model, map<int, string> modelNames)
{
    this->frameWithoutFacesDetected = frame;
    this->faceCascade = classifier;
    this->model = model;
    this->modelNames = modelNames;


}
Mat FaceDetector::getFrameWithFacesDetected(){
    return frameWithFacesDetected;
}
Mat FaceDetector::getFrameWithoutFacesDetected(){
    return frameWithoutFacesDetected;
}
Mat FaceDetector::getFrameWithFacesRecognized(){
    return frameWithFacesRecognized;
}

CascadeClassifier FaceDetector::getFaceCascade(){
    return faceCascade;
}
vector<Rect> FaceDetector::getDetectedFaces(){
    return detectedFaces;
}
void FaceDetector::setFrameWithFacesDetected()
{
    Mat helper = detectFaceFrontal(frameWithoutFacesDetected);
    this->frameWithFacesDetected = helper;
}
void FaceDetector::setFrameWithFacesRecognized()
{
    Mat helper = detectFaceFrontal(frameWithoutFacesDetected);
    helper = recognizeFace(helper);
    this->frameWithFacesRecognized = detectFaceFrontal(helper);
}

void FaceDetector::setfaceCascade(CascadeClassifier faceCascade)
{
    this->faceCascade = faceCascade;
}
void FaceDetector::setProfileCascade(CascadeClassifier profileCascade)
{
    this->profileCascade = profileCascade;
}

void FaceDetector::setDetectedFaces()
{
    Mat frame_gray, mirrored;
    vector<Rect> helper;
    cvtColor( frameWithoutFacesDetected, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    faceCascade.detectMultiScale( frame_gray, helper, 1.3, 4, 0|CV_HAAR_SCALE_IMAGE, Size(60, 60) );
    detectedFaces.insert(detectedFaces.end(),helper.begin(),helper.end());
    profileCascade.detectMultiScale( frame_gray, helper, 1.3, 4, 0|CV_HAAR_SCALE_IMAGE, Size(60, 60) );
    for( size_t i = 0; i < helper.size(); i++ )
      {
        for( size_t j = 0; j < detectedFaces.size(); j++ )
          {
            if(helper[i].x < (detectedFaces[j].x + detectedFaces[j].width) && helper[i].x > detectedFaces[j].x)
                helper.erase(helper.begin() + i);
            if(detectedFaces[j].x < (helper[i].x + helper[i].width) && detectedFaces[j].x > helper[i].x)
                helper.erase(helper.begin() + i);
          }
       }
    detectedFaces.insert(detectedFaces.end(),helper.begin(),helper.end());
    flip(frame_gray,mirrored,1);
    profileCascade.detectMultiScale( mirrored, helper, 1.3, 4, 0|CV_HAAR_SCALE_IMAGE, Size(60, 60) );
    for( size_t i = 0; i < helper.size(); i++ )
      {
        helper[i].x = mirrored.rows - helper[i].x;
      }
    for( size_t i = 0; i < helper.size(); i++ )
      {
        for( size_t j = 0; j < detectedFaces.size(); j++ )
          {
            if(detectedFaces[j].x < (helper[i].x + helper[i].width) && detectedFaces[j].x > helper[i].x)
                helper.erase(helper.begin() + i);
            if(helper[i].x < (detectedFaces[j].x + detectedFaces[j].width) && helper[i].x > detectedFaces[j].x)
                helper.erase(helper.begin() + i);
          }
      }
    detectedFaces.insert(detectedFaces.end(),helper.begin(),helper.end());
}

void FaceDetector::setModelNames(map<int,string> names)
{
    this->modelNames = names;
}

Mat FaceDetector::detectFaceFrontal(Mat frame)
{   Mat original = frame.clone();
    for( size_t i = 0; i < detectedFaces.size(); i++ )
      {
        Rect rect(detectedFaces[i].x, detectedFaces[i].y, detectedFaces[i].width, detectedFaces[i].height);
        rectangle(original,rect,Scalar( 0, 0, 255 ),2);
        //putText(frame,"Stranger_"+to_string(i+1),cvPoint(detectedFaces[i].x,detectedFaces[i].y - 10), FONT_HERSHEY_PLAIN, 1, cvScalar(0,0,255), 2, 3);
      }
      // face counter
      string faceNumber = "Number of faces:" + to_string(detectedFaces.size());
      putText(original,faceNumber,cvPoint( original.rows, (original.cols - 180)), FONT_ITALIC, 0.5, cvScalar(0,0,0), 2, 3);
      return original;
}
Mat FaceDetector::recognizeFace(Mat frame)
{
    Mat original = frame.clone();
    Mat gray;
    cvtColor(original, gray, CV_BGR2GRAY);
    for( size_t i = 0; i < detectedFaces.size(); i++)
    {
        Rect face_i = detectedFaces[i];
        Mat face = gray(face_i);
        Mat face_resized;
        resize(face, face_resized, Size(200,200), 1.0, 1.0, INTER_CUBIC);
        int prediction = -1;
        double confidence;
        model->predict(face_resized,prediction,confidence);
        string box_text;
        //Shows name and confidence level
        if(prediction > -1)
            box_text = modelNames[prediction] + "  " + to_string(confidence);
        // lower confidence level to achieve more accuracy to model, lesser chance to recognize model face in different position
         if(confidence > 60)
            box_text = "Stranger " + to_string(confidence);
         int pos_x = std::max(face_i.tl().x - 10, 0);
         int pos_y = std::max(face_i.tl().y - 10, 0);
         putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255,0,0), 2.0);
    }
         return original;
}
Mat FaceDetector::faceSwap(Mat frame)
{
    Mat original = frame.clone();
//    if(detectedFaces.size() == 2)
//    {
//        Rect first = detectedFaces[0];
//        Rect second = detectedFaces[1];
//        first.size();
//    }
    return original;
}

