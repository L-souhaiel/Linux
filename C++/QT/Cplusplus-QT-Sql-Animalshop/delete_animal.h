
#ifndef DELETE_ANIMAL_H
#define DELETE_ANIMAL_H
#include<QtWidgets>
#include"dbconnection.h"

class delete_Animal : public QWidget
{
    Q_OBJECT
public:
    delete_Animal();

public slots :
    void delete_animal_funk();
private :
    QVBoxLayout * id_layout ;
    QSpinBox *id_box;
        QRect screenGeometry = QApplication::desktop()->screenGeometry();
};

#endif // DELETE_ANIMAL_H


















































