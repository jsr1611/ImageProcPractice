#include<QApplication>
#include<QWidget>
#include<QMainWindow>
#include<QHBoxLayout>

#include "CustomMenuBar.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	
	QMainWindow *window = new QMainWindow();
	CustomMenuBar *menubar = new CustomMenuBar();
	QWidget *imgSpace = new QWidget();
	QHBoxLayout *hbl = new QHBoxLayout();
	
	window->setCentralWidget(imgSpace);
	window->setMenuBar(menubar->getMenuBar());
	window->setStatusBar(menubar->getStatusBar());
	
	window->resize(550, 300);
	window->move(0,0);

	imgSpace->setLayout(hbl);
	hbl->addWidget(menubar->getInImgLabel());
	hbl->addWidget(menubar->getOutImgLabel());
	
	window->show();
	return app.exec();
}
