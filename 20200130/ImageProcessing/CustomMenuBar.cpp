#include "CustomMenuBar.h"
#include "SliderWidget.h"

CustomMenuBar::CustomMenuBar(QWidget* parent):QWidget(parent)
{
	menubar = new QMenuBar(0);
	statusbar = new QStatusBar(0);
	
	fileMenu = new QMenu("File");
	openAct = new QAction("Open", 0);
	saveAct = new QAction("Save", 0);
	exitAct = new QAction("Exit", 0);
	
	imgMenu = new QMenu("Image Processing");
	binaryAct = new QAction("Binarization", 0);
	arithAct = new QAction("Arithmetic Operation", 0);
	edgeAct = new QAction("Edge Detection", 0);
	
	cameraMenu = new QMenu("Camera");
	picamAct = new QAction("Pi Camera", 0);
	
	inImgLabel = new QLabel();
	outImgLabel = new QLabel();
	
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);
	
	imgMenu->addAction(binaryAct);
	imgMenu->addAction(arithAct);
	imgMenu->addAction(edgeAct);
	
	cameraMenu->addAction(picamAct);
	
	menubar->addMenu(fileMenu);
	menubar->addMenu(imgMenu);
	menubar->addMenu(cameraMenu);
	
	connect(openAct, SIGNAL(triggered()), SLOT(openFile()));
	connect(saveAct, SIGNAL(triggered()), SLOT(saveFile()));
	connect(exitAct, SIGNAL(triggered()), SLOT(quitApp()));
		
	connect(binaryAct, SIGNAL(triggered()), SLOT(Binarization()));
	connect(arithAct, SIGNAL(triggered()), SLOT(Arithmetic()));
	connect(edgeAct, SIGNAL(triggered()), SLOT(EdgeDetection()));
}

void CustomMenuBar::picamSlot(){
	CameraWidget* c = new CameraWidget();
	c->show();
}

//Open File function
void CustomMenuBar::openFile()
{
	filepath = QFileDialog::getOpenFileName(
		this,
		"Open File",
		QDir::currentPath(),
		"BMP files (*.bmp);; JPG files (*.jpg);; All files (*.*)"
		// [여백주의 (*.bmp);; (0) (*.bmp) ;; (X)]
	);
	
	if(inImg.load(filepath)) {
		inImgLabel->setPixmap(QPixmap::fromImage(inImg));
	} else {
		statusbar->showMessage("Image Open Error");
	}
	
	statusbar->showMessage(filepath.insert(0, "Image Open : "));
	inImgLabel->show();
}

//Save File function
void CustomMenuBar::saveFile(){
	filepath = QFileDialog::getSaveFileName(
		this,
		"Save File",
		QDir::currentPath(),
		"BMP files (*.bmp);; JPG files (*.jpg);; All files (*.*)"
	);
	if(outImg.save(filepath)){
		statusbar->showMessage("Image Save");
	} else {
		statusbar->showMessage("Image Save Error");
	}
}

//Quit Application function
void CustomMenuBar::quitApp(){
	QApplication::quit();
}

//Binarization function
void CustomMenuBar::Binarization(){
	
	outImgLabel->setPixmap(QPixmap::fromImage(inImg));
	outImgLabel->show();
	outImg = inImg;
	
	unsigned char *index = outImg.bits();
	int w = outImg.width();
	int h = outImg.height();
	
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			if(*(index+x+(w*y)) > 128){
				*(index+x+(w*y)) = 255;
			} else{
				*(index+x+(w*y)) = 0;
			}
		}
	}
	outImgLabel->setPixmap(QPixmap::fromImage(outImg));
	outImgLabel->show();
}

void CustomMenuBar::Arithmetic(){
	SliderWidget *slider = new SliderWidget();
	
	outImgLabel->setPixmap(QPixmap::fromImage(inImg));
	outImgLabel->show();
	
	slider->setInImg(inImg);
	slider->setOutImgLabel(outImgLabel);
	slider->move(0, 330);
	slider->show();
}

void CustomMenuBar::EdgeDetection(){
	QWidget *bgWidget = new QWidget(0);
	QButtonGroup *bg = new QButtonGroup(bgWidget);
	
	QRadioButton *rb1 = new QRadioButton("Roberts", bgWidget);
	QRadioButton *rb2 = new QRadioButton("Prewitt", bgWidget);
	QRadioButton *rb3 = new QRadioButton("Sobel", bgWidget);
	rb1->move(10,10);
	rb2->move(10,40);
	rb3->move(10,70);
	bg->addButton(rb1,0);
	bg->addButton(rb2, 1);
	bg->addButton(rb3, 2);
	
	connect(bg, SIGNAL(buttonClicked(int)), SLOT(rbClicked(int)));
	
	outImgLabel->setPixmap(QPixmap::fromImage(inImg));
	outImgLabel->show();
	
	bgWidget->move(550, 0);
	bgWidget->show();

}

void CustomMenuBar::rbClicked(int id){
	QImage tempImg;
	tempImg = outImg = inImg;
	
	unsigned char *index = outImg.bits();
	unsigned char *tempIndex = tempImg.bits();
	int w = outImg.width();
	int h = outImg.height();
	
	int robertsX[3][3] = {{-1,0,0},{0,1,0},{0,0,0}};
	int robertsY[3][3] = {{0,0,-1}, {0,1,0}, {0,0,0}};
	
	int prewittX[3][3] = {{-1,-1,-1},{0,0,0},{1,1,1}};
	int prewittY[3][3] = {{1,0,-1},{1,0,-1},{1,0,-1}};

	int sobelX[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};
	int sobelY[3][3] = {{1,0,-1}, {2,0,-2}, {1,0,-1}};
	int maskX[3][3], maskY[3][3];
	int temp, tempX, tempY;
	
	switch(id){
		case 0:
			memcpy(maskX, robertsX, sizeof(int)*3*3);
			memcpy(maskY, robertsY, sizeof(int)*3*3);
			break;
		case 1:
			memcpy(maskX, prewittX, sizeof(int)*3*3);
			memcpy(maskY, prewittY, sizeof(int)*3*3);
			break;
		case 2:
			memcpy(maskX, sobelX, sizeof(int)*3*3);
			memcpy(maskY, sobelY, sizeof(int)*3*3);
			break;
		default:
			statusbar->showMessage("Button");
			break;
	}
	
for(int y=1; y<h-1; y++){
	for(int x=1; x<w-1; x++){
		temp = tempX=tempY=0;
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				tempX += *(index+x+j-1+(w*(y+i-1)))*maskX[i][j];
				tempY += *(index+x+j-1+(w*(y+i-1)))*maskY[i][j];
				
			}
		}
		temp = (int)sqrt(tempX*tempX + tempY*tempY);
		if(temp > 255){
		*(tempIndex+x+(w*y)) = 255;
		} else {
			*(tempIndex+x+(w*y))=(unsigned char) temp;
		}
	}	
	}
	outImg=tempImg;
	outImgLabel->setPixmap(QPixmap::fromImage(outImg));
	outImgLabel->show();

}

	
QMenuBar* CustomMenuBar::getMenuBar()
{
return menubar;
}

QStatusBar* CustomMenuBar::getStatusBar()
{
	return statusbar;
}

QLabel* CustomMenuBar::getInImgLabel()
{
	return inImgLabel;
}

QLabel* CustomMenuBar::getOutImgLabel()
{
	return outImgLabel;
}

