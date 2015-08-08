#include"frm_Main.h"
#include"frm_MenuList.h"
#include"frm_Result.h"
#include "CTemp.h"
#include<QtGui/QApplication>
#include <QTextCodec>
#include <QDesktopWidget>
#include<QMessageBox>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <qdatetime.h>

frm_Main::frm_Main(QWidget *parent,Qt::WFlags flags):QWidget(parent,flags)
{
	ui.setupUi(this);
	//事件关联
	connect(ui.Button_View,SIGNAL(clicked()),this,SLOT(Button_View_clicked()));
	connect(ui.Button_ViewMine,SIGNAL(clicked()),this,SLOT(Button_ViewMine_clicked()));
	connect(ui.Button_Exit,SIGNAL(clicked()),this,SLOT(Button_Exit_clicked()));
	ui.Button_View->setEnabled(true);
	ui.Button_ViewMine->setEnabled(true);
	ui.Button_Exit->setEnabled(true);
}
frm_Main::~frm_Main()
{
}
//打开选菜窗口 
void frm_Main::Button_View_clicked()
{
	frm_MenuList *win = new frm_MenuList();
	int pos_X = (int)(QApplication::desktop()->width() - win->width()) / 2;
	int pos_Y = (int)(QApplication::desktop()->height() - win->height()) / 2;
	win->setGeometry(pos_X,pos_Y,win->width(),win->height());
	win->show();
	this->close();
}
//打开已选菜单列表 
void frm_Main::Button_ViewMine_clicked()
{
	frm_Result *win = new frm_Result();
	int pos_X = (int)(QApplication::desktop()->width() - win->width()) / 2;
	int pos_Y = (int)(QApplication::desktop()->height() - win->height()) / 2;
	win->setGeometry(pos_X,pos_Y,win->width(),win->height());
	win->show();
	this->close();
}
void frm_Main::Button_Exit_clicked()
{
	int ret = QMessageBox::information(this, "notice", "confirm?", QMessageBox::No, QMessageBox::Yes);
	if(ret == QMessageBox::No) {
		return;
	}
	QSqlQuery query;
	if(!query.exec("delete from dishs_ordered")) {
		QMessageBox::information(this,"notice","system error");
		return ;
	}
	QMessageBox::information(this, "goodbye", "Thank you for your coming, goodbye!");
	this->close();
}
