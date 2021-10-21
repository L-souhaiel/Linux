#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include<QtWidgets>
#include<QApplication>
#include<QWidget>
#include "principalwindow.h"

class LoginWindow : public QWidget
{

    Q_OBJECT

public:

    LoginWindow( PrincipalWindow *window);

public slots :

   void  Create_user();
   void Loggingast();
   void loggin();
   QString returnuser() ;
   void loginAdmin();

private :
   QString m_user;
    QLineEdit *Password ;
     QLineEdit *login;
     PrincipalWindow *m_window;

};































#endif // LOGINWINDOW_H
