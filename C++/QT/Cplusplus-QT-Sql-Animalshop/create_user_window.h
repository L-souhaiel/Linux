#ifndef CREATE_USER_WINDOW_H
#define CREATE_USER_WINDOW_H

#include<QtWidgets>
#include<QApplication>
#include<QWidget>
#include "loginwindow.h"
#include<QMessageBox>
#include "dbconnection.h"
#include "Selection_Animal.h"


class Create_user_Window : public QWidget

{
    Q_OBJECT

public :
     Create_user_Window ();

public slots :

     void dialoggenerienTrue (/*const QString &message*/);

private :
     QLineEdit *Email;
      QLineEdit *Password ;
       QRect screenGeometry = QApplication::desktop()->screenGeometry();
};











#endif // CREATE_USER_WINDOW_H
