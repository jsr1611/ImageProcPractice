#include<iostream>
#include<raspicam/raspicam_cv.h>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;

int main( int argc, char **argv){
	raspicam::RaspiCam_Cv Camera;
	cv::Mat image;
	
	Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3);
	Camera.set( CV_CAP_PROP_FRAME_WIDTH, 640);
	Camera.set( CV_CAP_PROP_FRAME_HEIGHT, 480);
	
	if( !Camera.open() ){cerr<<"Error opening the camera"<<endl;return -1;}
	
	while(1){
		Camera.grab();
		Camera.retrieve( image );
//		cv::rotate(image, image, cv::ROTATE_90_CLOCKWISE);

		cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
		
		for(int y=0; y<image.cols; y++){
			for(int x=0; x<image.rows; x++){
				int temp = 0;
				temp += (int)image.at<cv::Vec3b>(x,y)[0];
				temp += (int)image.at<cv::Vec3b>(x,y)[1];
				temp += (int)image.at<cv::Vec3b>(x,y)[2];
				
				if(126 <= (temp/3)) {
					image.at<cv::Vec3b>(x,y)[0] = 255;
					image.at<cv::Vec3b>(x,y)[1] = 255;
					image.at<cv::Vec3b>(x,y)[2] = 255;					
				} else {
					image.at<cv::Vec3b>(x,y)[0] = 0;					
					image.at<cv::Vec3b>(x,y)[1] = 0;
					image.at<cv::Vec3b>(x,y)[2] = 0;									
				}
			}
		}
		
		cv::imshow( "test", image );
		if( cv::waitKey(1)> 0 ) break;
	}
	Camera.release();
}

