#include<stdio.h>
#include<stdlib.h>
#include<cv.h>
#include<highgui.h>

int main(int argc, char **argv){
	CvCapture *capture = 0;
	IplImage *frame = 0;
	int key = 0;
	
	capture = cvCaptureFromCAM(0);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FPS, 10);
	
	if( !capture ){
		fprintf(stderr, "Cannot open webcam!\n");
		return 1;
	}
	
	cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
	
	while( key != 'q'){
		frame = cvQueryFrame( capture );
		if( !frame ){
			fprintf( stdout, "ERROR: frame is null ...\n");
			break;
		}
		
		cvShowImage( "result", frame);
		key = cvWaitKey( 1 );
	}
	cvDestroyWindow( "result" );
	cvReleaseCapture( &capture );
	
	return 0;
}
