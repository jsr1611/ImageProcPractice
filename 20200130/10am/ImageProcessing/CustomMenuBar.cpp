#include "CustomMenuBar.h"

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

