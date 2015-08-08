#include<QtGui/QApplication>
#include <QTextCodec>
#include <QDesktopWidget>
#include"frm_Main.h"
#include"DBTools.h"
#include"CTemp.h"
int main(int argc,char * argv[])
{
	QApplication a(argc,argv);
	//下面这句就可以支持中文
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	frm_Main *win = new frm_Main;
	int pos_X = (int)(QApplication::desktop()->width() - win->width()) / 2;
	int pos_Y = (int)(QApplication::desktop()->height() - win->height()) / 2;
	win->setGeometry(pos_X,pos_Y,win->width(),win->height());
	//win->setWindowOpacity(0.9);
	
	if(!createConnection())
		return 1;
	win->show();
	
	return a.exec();
}
