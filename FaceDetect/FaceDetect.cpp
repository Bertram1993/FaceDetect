// FaceDetect.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/FaceDetector.h"
using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	//FaceDetector faceDetector1;
	//faceDetector1.setHaarCascadeTypeName(static_cast<FaceDetector::HaarCascadeType>(2));//2//4
	//faceDetector1.openFile("G:\\TestStream\\f(x) - LA chA TA.avi");

	//faceDetector1.openCamera();
	//faceDetector1.startDetectFace();

	if (argc == 2)
	{
		char *cmd = argv[1];
		if (cmd != nullptr && strcmp(cmd, "--help")==0)
		{
			cout << "Please input \"--file videoFileName\" to detect the face while the video is playing" << endl;
			cout << "Please input \"--cap camera\" to open the default camera and detect face" << endl;
			cout << "\"--type number\" mean to set HaarCascadeType; number = [0,5]; It is optional." << endl;
			cout << "Please input \"--help\" for help" << endl;
			cout << "Please press keyboard to continue..." << endl;
		}
		waitKey(0);
		return 0;
	}
	else if (argc < 3)
	{
		cout << "Your input params is invalid!" << endl;
		cout << "Please input \"--help\" for help" << endl;
		cout << "Please press keyboard to continue..." << endl;
		waitKey(0);
		return 0;
	}

	char *param1 = argv[1];
	char *param2 = argv[2];
	char *param3 = nullptr;
	int type = FaceDetector::FRONT_ALCAT_FACE_ALT;

	if (argc == 5)
	{
		if (strcmp(argv[3], "--type") == 0)
		{
			param3 = argv[4];
		}
	}
	if (param3)
	{
		type = *param3 - 0x30;
		if (type < 0 || type >= FaceDetector::FRONT_ALCAT_FACE_INVALID)
		{
			type = FaceDetector::FRONT_ALCAT_FACE_ALT;
		}
	}

	FaceDetector faceDetector;
	if (strcmp(param1, "--file") == 0)
	{
		faceDetector.setHaarCascadeTypeName(static_cast<FaceDetector::HaarCascadeType>(type));
		faceDetector.openFile(param2);
		faceDetector.startDetectFace();
	}
	else if (strcmp(param1, "--cap") == 0 && strcmp(param2,"camera") == 0)
	{
		faceDetector.setHaarCascadeTypeName(static_cast<FaceDetector::HaarCascadeType>(type));
		faceDetector.openCamera();
		faceDetector.startDetectFace();
	}

    return 0;
}

