#include "stdafx.h"
#include "FaceDetector.h"
#include <fstream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

FaceDetector::~FaceDetector()
{
	if (m_video.isOpened())
	{
		m_video.release();
	}
}

bool FaceDetector::openFile(string fileName)
{
	m_video.open(fileName);
	if (!m_video.isOpened())
	{
		cout << "open camera error!" << endl;
		return false;
	}

	m_fileName = fileName;
	m_isFile = true;

	return true;
}

bool FaceDetector::openCamera()
{
	m_video.open(0, CAP_DSHOW);
	if (!m_video.isOpened())
	{
		cout << "open camera error!" << endl;
		return false;
	}
	m_isFile = false;
	return true;
}

void FaceDetector::startDetectFace()
{
	if (!m_video.isOpened())
	{
		cout << "Please open a video file before start detect face!" << endl;
		return;
	}

	//load CascadeClassifier
	CascadeClassifier classiFier;
	if (!classiFier.load(m_HaarCascadeTypeName))
	{
		cout << "Can't load CascadeClassifier!" << endl;
		return;
	}

	//get FPS from video file
	int frameRate = m_video.get(CAP_PROP_FPS);
	if (frameRate == 0)
	{
		//set camera FPS
		frameRate = 30;
	}
	
	Mat frame;
	Mat grayFrame;
	vector<Rect> faces;
	while (true)
	{
		m_video >> frame;
		if (frame.empty())
			break;
		//erase face data
		faces.clear();
		if (frame.channels() > 1)
		{
			cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
		}
		else
		{
			grayFrame = frame.clone();
		}		

		classiFier.detectMultiScale(grayFrame, faces, 1.1, 3, 0, Size(20,20), Size(500,500));
		for (vector<Rect>::const_iterator iter=faces.begin(); iter!=faces.end(); iter++)
		{
			rectangle(frame, *iter, Scalar(0, 0, 255));
		}

		if (m_isFile)
		{
			imshow("video", frame);
		}
		else
		{
			imshow("camera", frame);
		}
		if (waitKey(1) == 'q')
			break;
	}

	m_video.release();
}

void FaceDetector::setHaarCascadeTypeName(HaarCascadeType type)
{
	switch (type)
	{
	case FaceDetector::FRONT_ALCAT_FACE:
		m_HaarCascadeTypeName = string(DATA_BASIC_PATH) + "haarcascade_frontalcatface.xml";
		break;
	case FaceDetector::FRONT_ALCAT_FACE_EXTENDED:
		m_HaarCascadeTypeName = string(DATA_BASIC_PATH) + "haarcascade_frontalcatface_extended.xml";
		break;
	case FaceDetector::FRONT_ALCAT_FACE_ALT:
		m_HaarCascadeTypeName = string(DATA_BASIC_PATH) + "haarcascade_frontalface_alt.xml";
		break;
	case FaceDetector::FRONT_ALCAT_FACE_ALT_TREE:
		m_HaarCascadeTypeName = string(DATA_BASIC_PATH) + "haarcascade_frontalface_alt_tree.xml";
		break;
	case FaceDetector::FRONT_ALCAT_FACE_ALT2:
		m_HaarCascadeTypeName = string(DATA_BASIC_PATH) + "haarcascade_frontalface_alt2.xml";
		break;
	case FaceDetector::FRONT_ALCAT_FACE_DEFAULT:
		m_HaarCascadeTypeName = string(DATA_BASIC_PATH) + "haarcascade_frontalface_default.xml";
		break;
	default:
		break;
	}
}
