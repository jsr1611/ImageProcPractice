#include<QApplication>
#include<QLabel>

int main(int argc, char **argv){

QApplication app(argc, argv);
QLabel *hello = new QLabel("<font color=blue><i>Hello </i>World</font>", 0);
hello->resize(125, 50);
hello->move(300, 300);
hello->show();

return app.exec();
}
