#ifndef FINALMENU_H
#define FINALMENU_H                                                            
                                                                              
#include<QtGui/QWidget>
#include<QSqlQueryModel>
#include"ui_frm_Result.h"                                                
                                                                              
class frm_Result:public QWidget
{
        Q_OBJECT
        public:
                frm_Result(QWidget *parent=0);
                ~frm_Result();
                QSqlQueryModel *model1;
		QSqlQueryModel *model2;
        private:
                Ui::frm_Result ui;
        private slots:
                void on_Return_clicked();
};
#endif //FINALMENU_H

