#include"frm_Result.h"
#include "frm_Main.h"
#include "CTemp.h"
#include <QtGui>
#include<QSqlQuery>
#include<QtGui/QApplication>
#include <QTextCodec>
#include <QDesktopWidget>

frm_Result::frm_Result(QWidget *parent):QWidget(parent)
{
	ui.setupUi(this);
	model1=new QSqlQueryModel();
	model1->setQuery("SELECT Name as 'Dish_Name', Price as 'Unit_Price($)', Num, Price*Num as 'Price($)' FROM dishs_ordered");
	ui.tableView1->setAlternatingRowColors(true);
	ui.tableView1->horizontalHeader()->setResizeMode(QHeaderView::Stretch); 
	ui.tableView1->setModel(model1);
	ui.tableView1->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView1->setEditTriggers(QAbstractItemView::NoEditTriggers);    //events handle
	QSqlQuery query;
	query.exec("select SUM(Price*Num) as 'Total price' from dishs_ordered");
	query.first();
	QString total_price = query.value(0).toString();
	if(total_price == "") {
		total_price = "0";
	}
	ui.lbl_TotalPrice->setText("<h3 align='left'><font color='green'>The total price is : </font><font color='red'>"
		+total_price+"</font><font color='green'>$</font></h3>");
	if(CTemp::submit_time == "") {
		ui.lbl_SubmitTime->setText("");
	}else {
		ui.lbl_SubmitTime->setText("<h3 align='left'><font color='green'>Submit time: </font><font color='red'>"+ CTemp::submit_time +"</font></h3>");		
	}
	connect(ui.Button_Return,SIGNAL(clicked()),this,SLOT(on_Return_clicked()));
}
frm_Result::~frm_Result()
{
}
void frm_Result::on_Return_clicked()
{
	frm_Main *win = new frm_Main();
	int pos_X = (int)(QApplication::desktop()->width() - win->width()) / 2;
	int pos_Y = (int)(QApplication::desktop()->height() - win->height()) / 2;
	win->setGeometry(pos_X,pos_Y,win->width(),win->height());
	win->show();
	//query->setQuery("delete from dishs_ordered");
	//ui.tableView->setModel(query);
	this->close();
}
