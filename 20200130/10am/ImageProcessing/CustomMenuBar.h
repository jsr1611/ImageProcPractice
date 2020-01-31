#ifndef __CUSTOM_MENU__
#define __CUSTOM_MENU__

#include<QWidget>
#include<QMenuBar>
#include<QStatusBar>
#include<QMenu>
#include<QAction>

#include<QLabel>

class CustomMenuBar : public QWidget
{
	public:
		CustomMenuBar(QWidget *parent = 0);
		QMenuBar* getMenuBar();
		QStatusBar* getStatusBar();
		QLabel* getInImgLabel();
		QLabel* getOutImgLabel();
		
	private:
		QMenuBar *menubar;
		QStatusBar *statusbar;
		QMenu *fileMenu;
		QAction *openAct;
		QAction *saveAct;
		QAction *exitAct;
		
		QMenu *imgMenu;
		QAction *binaryAct;
		QAction *arithAct;
		QAction *edgeAct;
		
		QMenu *cameraMenu;
		QAction *picamAct;
		
		QLabel *inImgLabel;
		QLabel *outImgLabel;
};

#endif
