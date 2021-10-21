#ifndef ADMINSECTION_H
#define ADMINSECTION_H

#include<QtWidgets>
#include"dbconnection.h"
#include "insert_anim.h"
#include "turnover_class.h"
#include "delete_animal.h"
class Adminsection : public QWidget
{
    Q_OBJECT

public:
    Adminsection();

public slots :
    void selected();

private:
    QRadioButton *insert;
    QRadioButton *delet;
    QRadioButton *turnover;
     QRect screenGeometry = QApplication::desktop()->screenGeometry();


};

#endif // ADMINSECTION_H
