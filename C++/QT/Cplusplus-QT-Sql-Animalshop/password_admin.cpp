#include "password_admin.h"

password_Admin::password_Admin()
{

    QVBoxLayout *layout = new QVBoxLayout;
    Enter = new QPushButton("Enter");
    layout_password = new QFormLayout;
    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    QPushButton *cancel = new QPushButton("Quit");
    QHBoxLayout *layout_boutton = new QHBoxLayout ;
    layout_boutton->addWidget(cancel);
    layout_boutton->addWidget(Enter);
    layout_password->addRow("Enter Admin Password " , password);
    layout->addLayout(layout_password);
    layout->addLayout(layout_boutton);
    setLayout(layout);
    setWindowTitle("Connexion To Admin ");


  connect(Enter , SIGNAL(clicked()) , this , SLOT(runAdmin_insert()));

   connect(cancel , SIGNAL(clicked()) ,qApp, SLOT(quit()) );
}




void password_Admin::runAdmin_insert()

{


    if ( password->text()=="admin1234")
    {
         QMessageBox::information(this , "Good " , " Succesful Connexion ");
         Adminsection *admin = new Adminsection;
         admin->show();



    }
    else  { QMessageBox::critical(this , "Error " , " your Password is not Correct") ; }





}
