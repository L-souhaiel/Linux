

#include <QApplication>
#include<QLayout>
#include<QWidget>
#include<QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialog>
#include <QRadioButton>
#include<QMessageBox>
#include<QtWidgets>
#include "principalwindow.h"
#include"loginwindow.h"



int main ( int argc , char * argv[])

{

   QApplication app(argc , argv);


   LoginWindow *window ;
   PrincipalWindow  *fennster = new PrincipalWindow;

   window = new LoginWindow(fennster);
    fennster->setwidgets(window) ;

    fennster->show() ;
    app.exec();


}
