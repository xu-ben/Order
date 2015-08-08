#include"frm_MenuList.h"
#include"frm_Result.h"
#include "CTemp.h"
#include <QtGui>
#include<QtGui/QApplication>
#include <QTextCodec>
#include <QDesktopWidget>
#include<QMessageBox>
#include<QSqlQuery>
#include <qdatetime.h>

frm_MenuList::frm_MenuList(QWidget *parent):QWidget(parent)
{
    ui.setupUi(this);
    select_Flag=false;// set select flag
    int pos_X=250;
	int pos_Y=250;
	this->setGeometry(pos_X,pos_Y,this->width(),this->height());
	this->setWindowOpacity(0.9);
 
 	//菜单表
    query=new QSqlQueryModel();//create query object
    query->setQuery("SELECT ID as 'Dish ID', Name as 'Dish Name', Type as 'Dish Type', Price as 'Unit Price($)' FROM dishs");
    ui.tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch); 
    ui.tableView->setAlternatingRowColors(true);
    ui.tableView->setModel(query);
    ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);//single selection mode
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);    //events handle
	//订单表
    query_order = new QSqlQueryModel();
    ui.tableView_2->setAlternatingRowColors(true);
    ui.tableView_2->horizontalHeader()->setResizeMode(QHeaderView::Stretch); 
    ui.tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);//single selection mode
	ui.tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);    //events handle
	update_order();
	
	connect(ui.Button_Return,SIGNAL(clicked()),this,SLOT(on_Return_clicked()));
	connect(ui.Button_Submit,SIGNAL(clicked()),this,SLOT(on_Submit_clicked()));
	connect(ui.Button_Add,SIGNAL(clicked()),this,SLOT(on_Add_clicked()));
	connect(ui.Button_Delete,SIGNAL(clicked()),this,SLOT(on_Delete_clicked()));
	connect(ui.txtSearch,SIGNAL(textChanged(const QString &)),this,SLOT(on_txt_Search_Changed(const QString &)));
	connect(ui.tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(on_Table_Click(QModelIndex)));  //table click
}
frm_MenuList::~frm_MenuList()
{
}
void frm_MenuList::on_Table_Click(QModelIndex qmodalindex)
{
	select_Flag=true;
	//选中的行号
	int curRow=qmodalindex.row();
	QAbstractItemModel *modessl = ui.tableView->model();
    QModelIndex indextemp = modessl->index(curRow, 0);
    QSqlQuery query;
    query.exec("select ImgPath from dishs where ID = " + indextemp.data(0).toString());
    query.first();
   	QString filename = query.value(0).toString();
   	//以黄金分割比显示图片
   	ui.lbl_Img->setText("<img width='372' height='230' src='" + filename + "' />");
}
//add dish to menu
void frm_MenuList::on_Add_clicked()
{
	if(select_Flag==false)
	{
		QMessageBox::information(this,"notice","Operation failed,please select an Item!");
		return;
	}
	QSqlQuery query;
	bool value;
	int curRow=ui.tableView->currentIndex().row(); //选中行
	QAbstractItemModel *modessl = ui.tableView->model();
    QModelIndex indextemp = modessl->index(curRow,0);
    QString dish_id=indextemp.data(0).toString();
    query.exec("select count(*) from dishs_ordered where ID="+dish_id);
    query.first();
   	int num = query.value(0).toInt();
	if(num==0)//如果没有这道菜则新增 
	{
		value=query.exec("insert into dishs_ordered(ID,Name,Type,Price) select ID,Name,Type,Price from dishs where ID="+dish_id);	
	}
	else //菜已点,累加
	{
		value=query.exec("update dishs_ordered set Num=Num+1 where ID="+dish_id);	
	}
	if(!value)
		QMessageBox::information(this,"notice","System Error!");
	update_order();
}
void frm_MenuList::on_txt_Search_Changed(QString text)
{
	select_Flag=false;
	QString strWhere="";
	if(text!="")
	{
		strWhere="where Name like '%"+text+"%' or Type like '%"+text+"%'";
	}
	query->setQuery("SELECT ID as 'Dish ID', Name as 'Dish Name', Type as 'Dish Type', Price as 'Unit Price($)' FROM dishs " + strWhere);
	ui.lbl_Img->setText("");
}
void frm_MenuList::update_order()
{
	query_order->setQuery("SELECT ID, Name, Price*Num as 'Price($)', Num FROM dishs_ordered");
    ui.tableView_2->setModel(query_order);
	QSqlQuery tq;
	tq.exec("select SUM(Price*Num) as 'Total price' from dishs_ordered");
	tq.first();
	QString total_price = tq.value(0).toString();
	if(total_price == "")
	{
		total_price = "0";
	}
	ui.lbl_total_price->setText("<center><h3><font color='green'>Total price : </font><font color='red'>"
	+ total_price + "</font><font color='green'>$</font></h3></center>");
}

void frm_MenuList::on_Delete_clicked()
{
	QSqlQuery query;
	bool value;
	int curRow = ui.tableView_2->currentIndex().row(); //选中行
	if(curRow < 0) {
		QMessageBox::information(this,"notice","Operation failed,please select an Item!");
		return ;
	}
	QAbstractItemModel *modessl = ui.tableView_2->model();
    QModelIndex indextemp = modessl->index(curRow, 0);
    QString order_id = indextemp.data(0).toString();
    query.exec("select Num from dishs_ordered where ID=" + order_id);
    query.first();
  	int num = query.value(0).toInt();
	if(num > 1)
	{
		value=query.exec("update dishs_ordered set Num=Num-1 where ID="+order_id);
		if(!value)
			QMessageBox::information(this,"notice","delete failed");  
	}
	else if(num==1)
	{
		value=query.exec("delete from dishs_ordered where ID="+order_id);
		if(!value)
			QMessageBox::information(this,"notice","delete failed");  
	}
	else
	{
		QMessageBox::information(this,"notice","delete failed!");
	}
	update_order();
}
void frm_MenuList::on_Submit_clicked()
{
	int ret = QMessageBox::information(this, "notice", "confirm?", QMessageBox::No, QMessageBox::Yes);
	if(ret == QMessageBox::No) {
		return;
	}
	CTemp::order_flag = true;
	CTemp::submit_time = QTime::currentTime().toString();
	frm_Result *win = new frm_Result();
	int pos_X = (int)(QApplication::desktop()->width() - win->width()) / 2;
	int pos_Y = (int)(QApplication::desktop()->height() - win->height()) / 2;
	win->setGeometry(pos_X,pos_Y,win->width(),win->height());
	win->show();
	this->close();
}
void frm_MenuList::on_Return_clicked() {
	frm_Main *win = new frm_Main();
	int pos_X = (int)(QApplication::desktop()->width() - win->width()) / 2;
	int pos_Y = (int)(QApplication::desktop()->height() - win->height()) / 2;
	win->setGeometry(pos_X,pos_Y,win->width(),win->height());
	win->show();
	this->close();	
}
