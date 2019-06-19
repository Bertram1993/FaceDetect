#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define DATA_BASIC_PATH "../3rdParty/data/haarcascades/"
class FaceDetector
{
public:
	enum HaarCascadeType
	{
		FRONT_ALCAT_FACE = 0,
		FRONT_ALCAT_FACE_EXTENDED,
		FRONT_ALCAT_FACE_ALT,//Ч����õ�
		FRONT_ALCAT_FACE_ALT_TREE,
		FRONT_ALCAT_FACE_ALT2,//Ч����õ�
		FRONT_ALCAT_FACE_DEFAULT,
		FRONT_ALCAT_FACE_INVALID
	};
	string m_fileName;
	string m_HaarCascadeTypeName;
	bool m_isFile;
	VideoCapture m_video;


	FaceDetector()=default;
	~FaceDetector();

	bool openFile(string fileName);
	bool openCamera();
	void startDetectFace();
	void setHaarCascadeTypeName(HaarCascadeType type);

};

