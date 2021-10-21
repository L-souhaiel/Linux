#include "adminsection.h"
//
Adminsection::Adminsection()
{

    QVBoxLayout *layout = new QVBoxLayout;
    insert = new QRadioButton("Insert new Animal ");
    delet = new QRadioButton("Delete Animal");
    turnover = new QRadioButton("Turnover");
    QPushButton *select = new QPushButton("Select");
    QPushButton *quit = new QPushButton("Quit");






    QHBoxLayout *layout_select = new QHBoxLayout;
    QVBoxLayout *layout_sel = new QVBoxLayout;



    layout_sel->addWidget(insert);
    layout_sel->addWidget(delet);
    layout_sel->addWidget(turnover);

    layout_select->addLayout(layout_sel);
    QPixmap image("/home/louati/Documents/layout/Adminstarteur.png");
    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(image);
    layout_select->addWidget(imageLabel);
    layout->addLayout(layout_select);

    layout->addWidget(select);
    layout->addWidget(quit);
    setLayout(layout);
    setWindowTitle("Adminstration");
    setFixedSize(600,450);
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    move(x, y);
    connect(select,SIGNAL(clicked()) , this , SLOT(selected()) );
    connect(quit , SIGNAL(clicked()) ,qApp, SLOT(quit()) );



}


void Adminsection::selected()

{


    if (insert->isChecked())

    {
        Insert_Anim *insertion = new Insert_Anim;
        insertion->show();

    }


    else  if (delet->isChecked())

    {
        delete_Animal *delAnim = new delete_Animal;
        delAnim->show();
    }


    else if (turnover->isChecked())

    {
        turnOver_class *turnoverloded = new turnOver_class;
        turnoverloded->show();

    }


}
