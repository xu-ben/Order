#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

static bool createConnection()
{
	QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("order.db");
	if(!db.open())
	{
		QMessageBox::critical(0,qApp->tr("Cannot open database!"),qApp->tr("Unable to establish a database connection.\n"),QMessageBox::Cancel);
		return false;
	}
	return true;
}
#endif

