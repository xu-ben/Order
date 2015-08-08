#ifndef MENU_H
#define MENU_H

#include <QtGui/QWidget>
#include <QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include "ui_menu.h"
#include "order.h"
#include "edit.h"

class menu:public QWidget
{
	Q_OBJECT
public:
	menu(QWidget *parent = 0, Qt::WFlags flags = 0);
	~menu();
	QSqlQueryModel *model;
	QSqlQueryModel *order_model;
	QImage image;
	QSqlQuery query;
	int orders_id;
	edit * order_dlg;
	edit * update_dlg;
private:
	Ui::menu ui;
private slots:
	void Radio_stable_clicked();
	void Radio_dishes_clicked();
	void Radio_soup_clicked();
	void ImageLabel_update(QModelIndex index);
	void Button_order_clicked();
	void Button_update_clicked();
	void Button_delete_clicked();
	void Button_submit_clicked();
	void Button_clear_clicked();
	void Edit_order_changed(QString quantity);
	void Edit_update_changed(QString quantity);
	void order_dlg_show();
	void update_dlg_show();
};
#endif//MENU_H

