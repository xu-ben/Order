#include "menu.h"
#include <QMessageBox>
#include <QtGui>

menu::menu(QWidget *parent, Qt::WFlags flags):QWidget(parent,flags)
{
	ui.setupUi(this);
	model = new QSqlQueryModel();
	order_model = new QSqlQueryModel();
	
	//Initialize Menu
	ui.table_menu->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.table_menu->verticalHeader()->hide();
	model->setQuery("select ID as 'Menu ID', Name as 'Food Name', Price from menu where Type = 'stable food'");
	ui.table_menu->setModel(model);
	ui.table_menu->setColumnWidth(0,100);
	ui.table_menu->setColumnWidth(1,148);
	ui.table_menu->setColumnWidth(2,100);
	
	//Initialize ImageLabel
	image.load("./images/zhushi.png");
	ui.ImageLabel->setPixmap(QPixmap::fromImage(image));
  ui.radio_stable->setChecked(true);
	
	//Initialize Order
	orders_id = 1;
	ui.table_order->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.table_order->verticalHeader()->hide();
	query.exec("select max(id) from orders");
	if(query.next())
	{
		orders_id = query.value(0).toInt() + 1;
	}
	//order_model->setQuery("select menu.id as 'Menu ID', Name as 'Food Name', Price as 'Per Price', Quantity as 'Quantity' from menu,orders where orders.id= " + QString::number(orders_id));
	ui.table_order->setModel(order_model);
	ui.table_order->setColumnWidth(0,75);
	ui.table_order->setColumnWidth(1,113);
	ui.table_order->setColumnWidth(2,75);
	ui.table_order->setColumnWidth(3,75);
	
	connect(ui.radio_stable, SIGNAL(clicked()),this,SLOT(Radio_stable_clicked()));
	connect(ui.radio_dishes, SIGNAL(clicked()),this,SLOT(Radio_dishes_clicked()));
	connect(ui.radio_soup, SIGNAL(clicked()),this,SLOT(Radio_soup_clicked()));
	connect(ui.table_menu, SIGNAL(clicked(QModelIndex)),this,SLOT(ImageLabel_update(QModelIndex)));
	connect(ui.button_order, SIGNAL(clicked()),this,SLOT(Button_order_clicked()));
	connect(ui.button_update, SIGNAL(clicked()),this,SLOT(Button_update_clicked()));
	connect(ui.button_delete, SIGNAL(clicked()),this,SLOT(Button_delete_clicked()));
	connect(ui.button_submit, SIGNAL(clicked()),this,SLOT(Button_submit_clicked()));
	connect(ui.button_clear, SIGNAL(clicked()),this,SLOT(Button_clear_clicked()));
	connect(ui.order_quantity, SIGNAL(clicked()),this,SLOT(order_dlg_show()));
	connect(ui.update_quantity, SIGNAL(clicked()),this,SLOT(update_dlg_show()));
	
	order_dlg = new edit();
	connect(order_dlg, SIGNAL(Changed(QString)), this, SLOT(Edit_order_changed(QString)));
	update_dlg = new edit();
	connect(update_dlg, SIGNAL(Changed(QString)), this, SLOT(Edit_update_changed(QString)));
}

menu::~menu()
{
	order_dlg->close();	
	update_dlg->close();
}

void menu::Radio_stable_clicked()
{
	ui.radio_stable->setChecked(true);
	ui.radio_dishes->setChecked(false);
	ui.radio_soup->setChecked(false);
 	image.load("./images/zhushi.png");
	ui.ImageLabel->setPixmap(QPixmap::fromImage(image));
	model->setQuery("select ID as 'Menu ID', Name as 'Food Name', Price as 'Per Price' from menu where Type = 'stable food'"); //id=" + QString::number(orders_id));
}

void menu::Radio_dishes_clicked()
{
	ui.radio_stable->setChecked(false);
	ui.radio_dishes->setChecked(true);
	ui.radio_soup->setChecked(false);
 	image.load("./images/xiaocai.png");
	ui.ImageLabel->setPixmap(QPixmap::fromImage(image));
	model->setQuery("select ID as 'Menu ID', Name as 'Food Name', Price as 'Per Price' from menu where Type = 'dishes food'");
}

void menu::Radio_soup_clicked()
{
	ui.radio_stable->setChecked(false);
	ui.radio_dishes->setChecked(false);
	ui.radio_soup->setChecked(true);
 	image.load("./images/tangzhou.png");
	ui.ImageLabel->setPixmap(QPixmap::fromImage(image));
	model->setQuery("select ID as 'Menu ID', Name as 'Food Name', Price as 'Per Price' from menu where Type = 'soup_porridge'");
}

void menu::ImageLabel_update(QModelIndex index)
{
	QModelIndex cell = index.sibling(index.row(),0);
	QString id = cell.data().toString();
	query.exec("select Imagepath from menu where ID = "+ id);
	QString path;
	if(query.next())
	{
		path = query.value(0).toString();
	}
	image.load(path);
	ui.ImageLabel->setPixmap(QPixmap::fromImage(image));
	
}

void menu::Button_order_clicked()
{
	int row = ui.table_menu->currentIndex().row();
	if(row == -1)
	{
			QMessageBox::information(0,"Failed to Order","Please choose menu!",QMessageBox::Ok);
			return;
	}
	if(ui.order_quantity->text() == "")
	{
		QMessageBox::information(0,"Failed to Order","Please input your order Quantity!",QMessageBox::Ok);
		return;
	}
	QModelIndex index = ui.table_menu->currentIndex();
	QModelIndex cell = index.sibling(index.row(),0);
	QString menuid = cell.data().toString();
	query.exec("select * from orders where MenuID = "+ menuid + "and ID = " + QString::number(orders_id));
	if(query.next())
	{
		QMessageBox::information(0,"Failed to Order","This Order has been Selected!",QMessageBox::Ok);
		return;
	}
	bool result = query.exec("insert into orders(id, menuid, quantity) values(" + QString::number(orders_id) + "," + menuid + "," + ui.order_quantity->text() + ")");
	if(result)
		order_model->setQuery("select menu.id as 'Menu ID', Name as 'Food Name', Price as 'Per Price', Quantity as 'Quantity' from menu,orders where menu.id = orders.menuid and orders.id= " + QString::number(orders_id));
	else
		QMessageBox::information(0,"notic","Failed to Order!",QMessageBox::Ok);
	
	ui.order_quantity->setText("1");
}
	
void menu::Button_update_clicked()
{
	int row = ui.table_order->currentIndex().row();
	if(row == -1)
	{
			QMessageBox::information(0,"Failed to Order","Please choose Order!",QMessageBox::Ok);
			return;
	}
	if(ui.update_quantity->text() == "")
	{
		QMessageBox::information(0,"Failed to Order","Please input your order Quantity!",QMessageBox::Ok);
		return;
	}
	QModelIndex index = ui.table_order->currentIndex();
	QModelIndex cell = index.sibling(index.row(),0);
	QString menuid = cell.data().toString();
	bool result = query.exec("update orders set quantity =" + ui.update_quantity->text() + " where id = " + QString::number(orders_id) + " and menuid = " + menuid);
	if(result)
		order_model->setQuery("select menu.id as 'Menu ID', Name as 'Food Name', Price as 'Per Price', Quantity as 'Quantity' from menu,orders where menu.id = orders.menuid and orders.id= " + QString::number(orders_id));
	else
		QMessageBox::information(0,"notic","Failed to Update Order!",QMessageBox::Ok);
	ui.update_quantity->setText("1");
}
void menu::Button_delete_clicked()
{
	int row = ui.table_order->currentIndex().row();
	if(row == -1)
	{
			QMessageBox::information(0,"Failed to Order","Please choose Order!",QMessageBox::Ok);
			return;
	}
	
	QModelIndex index = ui.table_order->currentIndex();
	QModelIndex cell = index.sibling(index.row(),0);
	QString menuid = cell.data().toString();
	bool result = query.exec("delete from orders where (id = " + QString::number(orders_id) + ") and (menuid = " + menuid + ")");
	if(result)
	{
		query.exec("select * from orders where ID = " + QString::number(orders_id));
		if(query.next())
			order_model->setQuery("select menu.id as 'Menu ID', Name as 'Food Name', Price as 'Per Price', Quantity as 'Quantity' from menu,orders where menu.id = orders.menuid and orders.id= " + QString::number(orders_id));
		else
			order_model->setQuery("");
	}
	else
		QMessageBox::information(0,"notic","Failed to Delete!",QMessageBox::Ok);
}

void menu::Button_clear_clicked()
{
	//Judge if order is empty
	query.exec("select * from orders where ID = " + QString::number(orders_id));
	if(query.next())
	{
		//if not, clear all	
		bool result = query.exec("delete from orders where id = " + QString::number(orders_id));
		order_model->setQuery("");
	}
	else
		//if yes, make a notice
		QMessageBox::information(0,"notic","Failed to Clear!",QMessageBox::Ok);
}

void menu::Button_submit_clicked()
{
	//Judge if order is empty
	query.exec("select * from orders where ID = " + QString::number(orders_id));
	if(query.next())
	{
		//if not, build up a order List	
		order *obj = new order();
		obj->show();
	}
	else
		//if yes, make a notice
		QMessageBox::information(0,"notic","No Order!",QMessageBox::Ok);
}

void menu::Edit_order_changed(QString quantity)
{
	ui.order_quantity->setText(quantity);
}

void menu::order_dlg_show()
{
	order_dlg->show();
	order_dlg->move((QApplication::desktop()->width() - order_dlg->width())/2,(QApplication::desktop()->height() - order_dlg->height())*0.6);
}

void menu::Edit_update_changed(QString quantity)
{
	ui.update_quantity->setText(quantity);
}

void menu::update_dlg_show()
{
	update_dlg->show();
	update_dlg->move((QApplication::desktop()->width() - update_dlg->width())/2,(QApplication::desktop()->height() - update_dlg->height())*0.7);
}
