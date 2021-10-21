#include "delete_animal.h"
#include "Selection_Animal.h"

delete_Animal::delete_Animal()
{


    QPushButton *delet= new QPushButton("Delete");
    QPushButton *cancel= new QPushButton("Cancel");



    id_box = new QSpinBox ;
    id_layout = new QVBoxLayout;
    QLabel *id_label = new QLabel("Enter the Id of the Animal want to delete ");
    id_box->setSingleStep(1);
    id_box->setValue(1);
    id_box->setRange(1,10000000);
    id_layout->addWidget(id_label);
    id_layout->addWidget(id_box);
    id_layout->addWidget(delet);
    id_layout->addWidget(cancel);
    setLayout(id_layout);
    setWindowTitle("Delte Animal");
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    move(x, y);
    connect(cancel,SIGNAL(clicked()), qApp , SLOT(quit()) );
    connect(delet,SIGNAL(clicked()) , this , SLOT(delete_animal_funk()));


}







void delete_Animal::delete_animal_funk()

{


    QString id = id_box->cleanText();

    dbConnection db;
    db.returnDB().open();
    QString delt_req(" delete from Animal where id = ");
    delt_req +=add_les_guillemet(id);

    QSqlQuery qry;

    if(qry.exec(delt_req)) {QMessageBox::information(this , "GOOD" , "Succesful Delete") ; } else {
       qDebug()<<qry.lastError();
       QMessageBox::critical(this , " Error" , " please try another Time");
    }

}
