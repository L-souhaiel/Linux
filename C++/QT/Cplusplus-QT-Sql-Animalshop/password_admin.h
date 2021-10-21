#ifndef PASSWORD_ADMIN_H
#define PASSWORD_ADMIN_H

#include<QtWidgets>
#include "adminsection.h"

class password_Admin : public QWidget
{
     Q_OBJECT

public:
    password_Admin();

public slots :
    void runAdmin_insert();
private :
    QFormLayout *layout_password ;
    QPushButton *Enter;
    QLineEdit *password;
};

#endif // PASSWORD_ADMIN_H
