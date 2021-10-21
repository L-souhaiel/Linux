#include "loginwindow.h"
#include "create_user_window.h"
#include"Selection_Animal.h"
#include "password_admin.h"
LoginWindow::LoginWindow(PrincipalWindow *window) : m_window(window)
{

    setWindowTitle("Connexion");
    QPushButton *Login = new QPushButton ("Login") ;
    QPushButton *quitter = new QPushButton ("Quitte") ;
    QPushButton *newuser = new QPushButton ("New User");
    QPushButton *alsgast = new QPushButton ("als Gast");
    QPushButton *Admin = new QPushButton("als Admin");
    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(Login);
    layout1->addWidget (quitter);
    layout1->addWidget (newuser);
    layout1->addWidget(alsgast);
    layout1->addWidget(Admin);
    QFormLayout *layout2 = new QFormLayout ;
    login = new QLineEdit;
    Password = new QLineEdit;
    Password->setEchoMode(QLineEdit ::Password) ;
    QVBoxLayout *Hauptlayout  = new QVBoxLayout ;
    layout2->addRow(  "Login :",login  ) ;
    layout2->addRow( "Password :",Password);
    Hauptlayout ->addLayout(layout2) ;
    Hauptlayout ->addLayout(layout1) ;
    setLayout(Hauptlayout);
    connect(quitter , SIGNAL(clicked() ), qApp , SLOT(quit() )  );
    connect(newuser , SIGNAL(clicked() ), this , SLOT(Create_user() ) );
    connect(alsgast,SIGNAL(clicked()) , this , SLOT(Loggingast()));
    connect(Login , SIGNAL(clicked()) ,this , SLOT(loggin()));
    connect(Admin,SIGNAL(clicked()), this , SLOT(loginAdmin()) );


}




void LoginWindow::loginAdmin()

{


    dbConnection db;
    if (db.returnDB().open()){

                        password_Admin *pass = new password_Admin;
                          //pass->show();



                       m_window->setwidgets(pass);                 }

    else  { qDebug()<<db.lastError();}

}











void LoginWindow::Loggingast()

{



   dbConnection db;


    if (db.returnDB().open())
    {
    selection_Animal *selection_window = new selection_Animal("gast" ,"gast");
    selection_window->show();
   }

    else qDebug() << db.lastError() ;

}








QString LoginWindow::returnuser() { return login->displayText() ; }












void LoginWindow::loggin()
{


dbConnection db ;

if (db.returnDB().open())

{



    if (checktheexistance(login->displayText()))

    {
        Password->setEchoMode(QLineEdit::Normal);

       if (checkthecomptabiliti(login->displayText() , Password->displayText()))

       {

    selection_Animal *selection_windows = new selection_Animal(login->displayText() , Password->displayText());
    selection_windows->show();

       }

       else  { QMessageBox::critical(this , "Error" , "Password incorect"); }

    }

    else  {QMessageBox::critical(this , "Error" ," User Not found  , Try again or register  ");}

}

else  {qDebug() << db.lastError();}


}

















void LoginWindow::Create_user()
{

 Create_user_Window *user_window = new Create_user_Window();
 user_window->show();


}
