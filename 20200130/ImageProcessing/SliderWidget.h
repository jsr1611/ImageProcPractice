#ifndef __SLIDER_WIDGET__
#define __SLIDER_WIDGET__

#include<QWidget>
#include<QSlider>
#include<QLabel>
#include<QString>
#include<QVBoxLayout>

class SliderWidget : public QWidget
{
	Q_OBJECT
	public:
		SliderWidget(QWidget *parent = 0);
		void setInImg(QImage);
		void setOutImgLabel(QLabel*);
		
	public slots:
		void changeValue();
	
	private:
		QImage inImg;
		QImage outImg;
		QLabel *outImgLabel;
		QSlider *slider;
		QLabel *valueLabel;
		QVBoxLayout *vbl;
		unsigned char * index;
};

#endif
