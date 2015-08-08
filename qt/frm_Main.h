#ifndef menu_H
#define menu_H                                                              
#include<QtGui/QWidget>
#include"ui_frm_Main.h"
class frm_Main:public QWidget
{
        Q_OBJECT
        public:
			frm_Main(QWidget *parent = 0,Qt::WFlags flags = 0);
			~frm_Main();
        private:
			Ui::frm_Main ui;
        private slots:
			void Button_View_clicked();
			void Button_ViewMine_clicked();
			void Button_Exit_clicked();
};

                                                                                
#endif //DXLMENU_H
