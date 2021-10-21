#include "create_user_window.h"
#include "loginwindow.h"




Create_user_Window :: Create_user_Window ()

{

 setWindowTitle("Create new account");

Email = new QLineEdit;
Password= new QLineEdit;
 QFormLayout *layout1 = new QFormLayout;
 layout1->addRow("Enter User name :",Email );
 layout1->addRow("Enter password :",Password);
 Password->setEchoMode(QLineEdit::Password);
 QPushButton *Confirm = new QPushButton("Confirm");
 QVBoxLayout *hauptlayout = new QVBoxLayout;
 hauptlayout->addLayout(layout1);
 hauptlayout->addWidget(Confirm);
 setLayout(hauptlayout);
 int x = ((screenGeometry.width() - this->width()) / 2);
 int y = ((screenGeometry.height() - this->height()) / 2);
 move(x, y);
 connect(Confirm , SIGNAL(clicked()) , this , SLOT(dialoggenerienTrue()) );

}






void Create_user_Window:: dialoggenerienTrue ( )

{



dbConnection db;
db.returnDB().open();
qDebug()<<db.lastError();
QString user = Email->displayText();
Password->setEchoMode(QLineEdit::Normal);
QString passwort = Password->displayText();







if(!checktheexistance(user))

{
    QString qry_insert("insert into Custmer (user_name , password) values ( ");
    qry_insert +=add_les_guillemet(user) + " , " + add_les_guillemet(passwort) + " )";
    qDebug()<<qry_insert;
    QSqlQuery qry ;
    if ( qry.exec( qry_insert ))

    {
   QMessageBox::information(this, "Good", " Successful registration");
    }

    else  {qDebug()<<qry.lastError();}

}

else {  QMessageBox::critical(this ,"Error" ,"the user is already taken , try with another User Name") ;}




}







