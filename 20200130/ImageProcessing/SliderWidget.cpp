#include "SliderWidget.h"

SliderWidget::SliderWidget(QWidget* parent):QWidget(parent)
{
	vbl = new QVBoxLayout();
	
	slider = new QSlider(Qt::Horizontal, 0);
	slider->setTickPosition(QSlider::TicksAbove);
	slider->setTickInterval(5);
	slider->setRange(-255,255);
	slider->setMinimumWidth(530);
	slider->setValue(0);
	
	valueLabel = new QLabel("0", 0);
	valueLabel->setAlignment(Qt::AlignHCenter);
	
	vbl->addWidget(slider);
	vbl->addWidget(valueLabel);
	
	connect(slider, SIGNAL(valueChanged(int)), SLOT(changeValue()));
	
	this->setWindowTitle("Arithmetic Operation");
	this->setLayout(vbl);
	this->show();
}	

void SliderWidget::setInImg(QImage inImg){
	this->inImg = inImg;
}

void SliderWidget::setOutImgLabel(QLabel *outImgLabel){
	this->outImgLabel = outImgLabel;
}

void SliderWidget::changeValue(){
	QString temp;
	temp = temp.setNum(slider->value());
	valueLabel->setText(temp);
	
	outImg = inImg;
	
	unsigned char *index = outImg.bits();
	int buf;
	int w = outImg.width();
	int h = outImg.height();
	
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			buf = *(index+x+(w*y));
			buf += slider->value();
			if(buf > 255){
				buf = 255;
			} else if (buf < 0){
				buf = 0; 
				}
			*(index+(w*y)) = buf;
		}
	}
	outImgLabel->setPixmap(QPixmap::fromImage(outImg));
	outImgLabel->show();
}

