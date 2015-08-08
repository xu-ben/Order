#ifndef EDIT_H
#define EDIT_H

#include <QtGui/QWidget>
#include "ui_edit.h"

class edit:public QWidget
{
	Q_OBJECT
public:
	QString quantity;
	bool changed;
	edit(QWidget *parent = 0);
	~edit();
private:
	Ui::edit ui;
private slots:
	void B0_clicked();
	void B1_clicked();
	void B2_clicked();
	void B3_clicked();
	void B4_clicked();
	void B5_clicked();
	void B6_clicked();
	void B7_clicked();
	void B8_clicked();
	void B9_clicked();
	void Bback_clicked();
	void Bclear_clicked();
	void Benter_clicked();
signals:
	void Changed(const QString &);
};
#endif//EDIT_H
