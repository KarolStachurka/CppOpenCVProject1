#include "inputoutput.h"

InputOutput::InputOutput()
{

}
void InputOutput::readCSV(const string& filename, vector<Mat>& images, vector<int>& labels, char separator)
{
    ifstream file(filename.c_str(), ifstream::in);
    if (!file)
    {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line))
    {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel,separator);
        if(!path.empty() && !classlabel.empty())
        {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}
map<int,string> InputOutput::getModelNamesFromCSVfile()
{
    map<int, string> names;
    string filename = "faces.csv";
    char separator = ';';
    ifstream file(filename.c_str(), ifstream::in);
    if (!file)
    {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, label, name, prevName = "-1";
    while (getline(file, line))
    {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, label,separator);
        getline(liness, name);
        if(!label.empty() && !name.empty())
        {
            if(name != prevName)
                names[atoi(label.c_str())] = name.c_str();
        }
    }
    file.close();
    return names;
}

Ptr<face::LBPHFaceRecognizer> InputOutput::generateModel()
{
    string fn_csv = "faces.csv";
    vector<Mat> images;
    vector<int> labels;
        // Read in the data. This can fail if no valid input filename is given.
        try {
            readCSV(fn_csv, images, labels,';');
        } catch (cv::Exception& e) {
            cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
            exit(1);
        }
        if(images.size() <= 1) {
            string error_message = "This program needs at least 2 images to work. Please add more images to data set!";
            CV_Error(CV_StsError, error_message);
        }
        Ptr<face::LBPHFaceRecognizer> model = face::LBPHFaceRecognizer::create();
        model->train(images, labels);
        return model;
}
void InputOutput::generateInput(string modelName, int label)
{
    //create directory if not exists
    generateDirectory("facesDatabase");
    generateDirectory("facesDatabase/" + modelName);
    //open camera and save 50 screens of face to directory
    Camera camera;
    camera.setCameraOn();
    for(int i = 0; i < 50; i++)
    {
        Mat frame = camera.takeModelFacePicture();
        string name = "facesDatabase/" + modelName + "/" + modelName + to_string(i)+".pgm";
        imwrite(name,frame);
        writeToCSVfile(name + ";" + to_string(label) + ";" + modelName);
        this_thread::sleep_for(chrono::milliseconds(100));
    }


}
void InputOutput::generateDirectory(string fileName)
{
    int nError = 0;
    #if defined(_WIN32)
        nError = _mkdir(fileName.c_str()); // can be used on Windows
    #else
        nError = mkdir(fileName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // can be used on Linux
    #endif
        //to do :
        //handling errors
    if (nError != 0)
    {
    }
}
void InputOutput::writeToCSVfile(string data)
{
    ofstream file("faces.csv",ios::out | ios::app);
    if(file.is_open())
        file << data <<endl;
    file.close();
}
CascadeClassifier InputOutput::loadFaceCascade(string filepath)
{
    CascadeClassifier faceCascade;
    faceCascade.load(filepath);
    return faceCascade;
}
int InputOutput::getNewModelLabel()
{
    int label = 0;
    string filename = "faces.csv", line, helper, lastLabel;
    char separator = ';';
    ifstream file(filename.c_str(), ifstream::in);
    if (!file)
    {
        return label;
    }
    while (getline(file, line))
    {
        stringstream liness(line);
        getline(liness, helper, separator);
        getline(liness, lastLabel, separator);
        label = atoi(lastLabel.c_str()) + 1;
    }
    file.close();
    return label;
}
void InputOutput::removeModelFromFacesDatabase(string filename, string name, char separator)
{
    ifstream file(filename.c_str(), ifstream::in);
    ofstream newFile("backup.txt",ofstream::out);
    if (!file || !newFile)
    {
        return;
    }
    string line, path,label, modelName;
    while (getline(file, line))
    {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, label,separator);
        getline(liness,modelName);
        if(modelName != name)
            newFile << line << endl;
        else
            remove(path.c_str());
    }
    file.close();
    newFile.close();
    string dirPath = "facesDatabase/" + name;
    remove(dirPath.c_str());
    remove(filename.c_str());
    rename("backup.txt",filename.c_str());
}
