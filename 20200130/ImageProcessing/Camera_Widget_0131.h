#ifndef __CAMERA_WIDGET__
#define __CAMERA_WIDGET__

#include<QWidget>
#include<QLabel>
#include<QTimer>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QCloseEvent>
#include<opencv2/opencv.hpp>
#include<raspicam/raspicam_cv.h>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;

class CameraWidget : public QWidget
{
	Q_OBJECT
	public:
		CameraWidget(QWidget* parent = 0);
		void closeEvent(QCloseEvent* event);
		
	public slots:
		void updateCam();
		void takeScreenshot();
		void recordVideo();
		void openVideo();
		void updateVideo();
		
	private:
		raspicam::RaspiCam_Cv cam;
		QImage qImg;
		cv::Mat camImg;
		QLabel* imgLabel;
		
		QTimer* camTimer;
		QTimer* openTimer;
		
		QPushButton *screenshotButton;
		QPushButton *recordButton;
		QPushButton *openButton;
		
		QHBoxLayout *hbl;
		QVBoxLayout *vbl;
		
		int recordFlag;
		VideoWriter out;
		CvCapture* capture;
		IplImage* frame;
};

#endif
