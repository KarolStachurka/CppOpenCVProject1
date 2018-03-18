#include "camera.h"

Camera::Camera()
{
}
void Camera::setCameraOn()
{
    VideoCapture camera(0);
    this->openedCamera = camera;
}

void Camera::cameraOutput()
{
    if(!openedCamera.isOpened())
        return;
    while(true)
    {
        Mat frame;
        openedCamera >> frame;
        imshow("view", frame);
        if(waitKey(30) >= 0)
        {
            destroyAllWindows();
            break;
        }
     }
}
void Camera::faceDetectionCameraOutput()
{
    if(!openedCamera.isOpened())
        return;
    InputOutput io;
    CascadeClassifier classifier = io.loadFaceCascade(FRONTAL_FACE_CASCADE);
    CascadeClassifier classifier2 = io.loadFaceCascade(PROFILE_FACE_CASCADE);
    while(true)
    {
        Mat frame;
        openedCamera >> frame;
        FaceDetector faceDetection(frame,classifier);
        faceDetection.setProfileCascade(classifier2);
        faceDetection.setDetectedFaces();
        faceDetection.setFrameWithFacesDetected();
        frame = faceDetection.getFrameWithFacesDetected();
        imshow("view", frame);
        if(waitKey(30) >= 0)
        {
            destroyAllWindows();
            break;
        }
     }
}
void Camera::faceRecognitionCameraOutput()
{
    if(!openedCamera.isOpened())
        return;
    InputOutput io;
    Ptr<face::LBPHFaceRecognizer> model = io.generateModel();
    CascadeClassifier classifier = io.loadFaceCascade(FRONTAL_FACE_CASCADE);
    CascadeClassifier classifier2 = io.loadFaceCascade(PROFILE_FACE_CASCADE);
    map<int,string> modelNames = io.getModelNamesFromCSVfile();
    while(true)
    {
        Mat frame;
        openedCamera >> frame;
        FaceDetector faceDetection(frame,classifier,model,modelNames);
        faceDetection.setProfileCascade(classifier2);
        faceDetection.setDetectedFaces();
        faceDetection.setFrameWithFacesRecognized();
        frame = faceDetection.getFrameWithFacesRecognized();
        imshow("view", frame);
        if(waitKey(30) >= 0)
        {
            destroyAllWindows();
            break;
        }
     }
}
Mat Camera::takeModelFacePicture()
{
    Mat frame;
    if(!openedCamera.isOpened())
        return frame;
    openedCamera >> frame;
    InputOutput io;
    CascadeClassifier classifier = io.loadFaceCascade(FRONTAL_FACE_CASCADE);
    CascadeClassifier classifier2 = io.loadFaceCascade(PROFILE_FACE_CASCADE);
    FaceDetector faceDetection(frame,classifier);
    faceDetection.setProfileCascade(classifier2);
    faceDetection.setDetectedFaces();
    faceDetection.setFrameWithFacesDetected();
    vector<Rect> faces = faceDetection.getDetectedFaces();
    if(faces.size() == 1)
    {
        Rect rect( faces[0].x, faces[0].y, faces[0].width, faces[0].height);
        frame = frame(rect);
    }
    cvtColor( frame, frame, CV_BGR2GRAY );
    resize( frame, frame, Size(200,200));
    return frame;
}
Mat Camera::takePicture()
{
    Mat frame;
    openedCamera >> frame;
    return frame;
}


