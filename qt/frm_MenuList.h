#ifndef menulist_H
#define menulist_H
                                                                                
#include<QtGui/QWidget>
#include<QtSql/QSqlQueryModel>
#include"ui_frm_MenuList.h"
#include"frm_Main.h"
                                                                                
class frm_MenuList:public QWidget
{
        Q_OBJECT
        public:
			frm_MenuList(QWidget *parent=0);
			~frm_MenuList();
			QSqlQueryModel *query;
			QSqlQueryModel *query_order;
        private:
			Ui::frm_MenuList ui;
			bool select_Flag;
        private slots:
			void on_Add_clicked();
			void on_txt_Search_Changed(QString text);
			void on_Table_Click(QModelIndex qmodalindex);
			void on_Delete_clicked();
			void update_order();
			void on_Submit_clicked();
			void on_Return_clicked();
};
#endif //menulist_H
