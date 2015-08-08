#include <QtGui/QApplication>
#include <QDesktopWidget>
#include "menu.h"
#include "connection.h"

int main(int argc, char * argv[])
{
	QApplication a(argc,argv);
	if(!createConnection())
		return 1;
	menu *w = new menu;
	w->show();
	w->move((QApplication::desktop()->width() - w->width())*0.5,(QApplication::desktop()->height() - w->height())*0.4);
	return a.exec();
}

