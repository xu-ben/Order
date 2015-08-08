#ifndef CONNECTION_H
#define CONNECTION_H
#include<QMessageBox>
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
static bool createConnection()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("menu.db");
	if(!db.open())
	{
		QMessageBox::critical(0,qApp->tr("Error"),qApp->tr("Connect to database failed.\n"),QMessageBox::Cancel);
		return false;
	}
	/*
	QSqlQuery query;
	query.exec("insert into dishs(ID,Name,Type,Price) values(1,'Dumplings','Staple Food',5.0)");//饺子
	query.exec("insert into dishs(ID,Name,Type,Price) values(2,'Noodles','Staple Food',8.4)");//面条
	query.exec("insert into dishs(ID,Name,Type,Price) values(3,'Beef','Meat',45.0)");//牛肉
	query.exec("insert into dishs(ID,Name,Type,Price) values(4,'Roast duck','Meat',49.9)");//烤鸭
	query.exec("insert into dishs(ID,Name,Type,Price) values(5,'Fish ball soup','Soup',12.0)");//鱼丸汤
	query.exec("insert into dishs(ID,Name,Type,Price) values(6,'Milk','Drink',3.9)");//牛奶
	query.exec("insert into dishs(ID,Name,Type,Price) values(7,'Coffee','Drink',6.5)");//咖啡
	query.exec("insert into dishs(ID,Name,Type,Price) values(8,'Fish Flavored pork','Home Kooking',16.0)");//鱼香肉丝
	query.exec("insert into dishs(ID,Name,Type,Price) values(9,'Mapo Tofu','Home Kooking',12.0)");//麻婆豆腐
	query.exec("insert into dishs(ID,Name,Type,Price) values(10,'Pickled fish','Home Kooking',28.0)");//酸菜鱼
	query.exec("insert into dishs(ID,Name,Type,Price) values(11,'large meatball','Home Kooking',23.5)");//狮子头
	query.exec("insert into dishs(ID,Name,Type,Price) values(12,'Boiled meat','Home Kooking',27.0)");//水煮肉
	query.exec("insert into dishs(ID,Name,Type,Price) values(13,'Braised eggplant','Home Kooking',15.0)");//烧茄子
	query.exec("insert into dishs(ID,Name,Type,Price) values(14,'Rice','Staple Food',2.0)");//米饭
	*/
	return true;
}
#endif
