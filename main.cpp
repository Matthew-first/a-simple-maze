#include <QtWidgets/QApplication>
#include"Window.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Window b;
	b.show();
	return a.exec();
}
