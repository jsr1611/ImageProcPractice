#include<iostream>

#include "Camera_Widget_0131.h"

using namespace std;

CameraWidget::CameraWidget(QWidget* parent):QWidget(parent)
{
	recordFlag = 0;
	
	hbl = new QHBoxLayout();
	vbl = new QVBoxLayout();
	
	screenshotButton = new QPushButton("Screenshot", 0);
	recordButton = new QPushButton("Record", 0);
	openButton = new QPushButton("Open Video", 0);
	
	imgLabel = new QLabel();
	
	hbl->addWidget(screenshotButton);
	hbl->addWidget(recordButton);
	hbl->addWidget(openButton);
	
	vbl->addLayout(hbl);
	vbl->addWidget(imgLabel);
	this->setLayout(vbl);

	cam.set( CV_CAP_PROP_FORMAT, CV_8UC3);
	cam.set( CV_CAP_PROP_FRAME_WIDTH, 640);
	cam.set( CV_CAP_PROP_FRAME_HEIGHT, 480);
	
	if(!cam.open()) {cerr<<"Error opening the camera"<<endl;}
	
	connect(screenshotButton, SIGNAL(clicked()), SLOT(takeScreenshot()));
	connect(recordButton, SIGNAL(clicked()), SLOT(recordVideo()));
	connect(openButton, SIGNAL(clicked()), SLOT(openVideo()));
	
	camTimer = new QTimer(this);
	openTimer = new QTimer(this);
	connect(camTimer, SIGNAL(timeout()), SLOT(updateCam()));
	connect(openTimer, SIGNAL(timeout()), SLOT(updateVideo()));
	camTimer->start(10);
	
}

void CameraWidget::closeEvent(QCloseEvent *event)
{
	cam.release();
	camTimer->stop();
	delete camTimer;
	
	QWidget::closeEvent(event);
}

void CameraWidget::updateCam()
{
	cam.grab();
	cam.retrieve(camImg);
	
	qImg = QImage((uchar *)camImg.data, camImg.cols, camImg.rows, camImg.step, QImage::Format_RGB888);
	
	if(recordFlag == 1){
		if(!out.isOpened()){
			out.open("output.avi", CV_FOURCC("*.XVID"), 20, 
				cvSize(camImg.cols, camImg.rows), true);
		} else {
			out << camImg;
		}
	}
	qImg.rgbSwapped();
	
	imgLabel->resize(640, 480);
	imgLabel->setPixmap(QPixmap::fromImage(qImg));
	imgLabel->show();
}

void CameraWidget::takeScreenshot()
{
	imwrite("picture.jpg", camImg); // qImg.save("picture.jpg");
	
	cout <<"이미지를 저장하였습니다."<<endl;
}

void CameraWidget::recordVideo()
{
	if(recordFlag == 0 ){
		recordFlag = 1;
		recordButton->setDown(true);
		cout << "영상저장이 시작됩니다."<< endl;

	} else if (recordFlag == 1){
		recordFlag = 0;
		recordButton->setDown(false);
		cout << "영상저장이 종료되었습니다."<< endl;
		}
}

void CameraWidget::openVideo()
{
	if(recordFlag == 0){
		capture = cvCaptureFromFile("output.avi");
		frame = NULL;
		
		camTimer->stop();
		openTimer->start(((1/cvGetCaptureProperty(capture, CV_CAP_PROP_FPS))*1000)+25);
		cout << "영상출력 시작"<< endl;
	} else if(recordFlag == 1){
		cout << "녹화중입니다." << endl;
	}
}

void CameraWidget::updateVideo()
{
	frame = cvQueryFrame(capture);
	if(frame == NULL){
	
		openTimer->stop();
		camTimer->start(10);
		cout << "영상출력 종료"<< endl;
		
	} else {
		camImg = cv::cvarrToMat(frame);
	}
	qImg = QImage((uchar *)camImg.data, camImg.cols, camImg.rows, camImg.step, QImage::Format_RGB888);
	imgLabel->resize(640, 480);
	imgLabel->setPixmap(QPixmap::fromImage(qImg));
	imgLabel->show();
}
