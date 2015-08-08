#include "order.h"
#include <QtGui>

order::order(QWidget *parent):QWidget(parent)
{
	ui.setupUi(this);
	model = new QSqlQueryModel();
	ui.table_order->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.table_order->verticalHeader()->hide();
	query.exec("select max(id) from orders");
	int id,i;
	float total;
	QModelIndex index;
	if(query.next())
	{
		id = query.value(0).toInt();
		ui.OrderIDLabel->setText(QString::number(id));
	}
	model->setQuery("select menu.name as 'Order Food Name', menu.price as 'Per Price', orders.quantity as 'Quantity', menu.price*orders.quantity as 'Total Price' from menu,orders where orders.id = " + QString::number(id) + " and menu.id = orders.menuid");
	ui.table_order->setModel(model);
	ui.table_order->setColumnWidth(0,150);
	ui.table_order->setColumnWidth(1,100);
	ui.table_order->setColumnWidth(2,100);
	ui.table_order->setColumnWidth(3,100);
	
	total = 0;
	for(i = 0; i < ui.table_order->model()->rowCount(); i++)
	{
		index = model->index(i,3);
		total +=  index.data().toString().toFloat();
	}
	ui.PayLabel->setText(QString("%1").arg(total));
	
}

order::~order()
{}
