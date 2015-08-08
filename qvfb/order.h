#ifndef ORDER_H
#define ORDER_H

#include <QtGui/QWidget>
#include <QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include "ui_order.h"

class order:public QWidget
{
	Q_OBJECT
public:
	order(QWidget *parent = 0);
	~order();
	QSqlQueryModel *model;
	QSqlQuery query;
private:
	Ui::order ui;
};
#endif//ORDER_H
