#ifndef TURNOVER_CLASS_H
#define TURNOVER_CLASS_H

#include<QtWidgets>
#include "search_turn_over_admin.h"
class turnOver_class : public QWidget
{
    Q_OBJECT

public:
    turnOver_class();

public slots : void searching();

   private :  QDateEdit *date;
            QRect screenGeometry = QApplication::desktop()->screenGeometry();

};

#endif // TURNOVER_CLASS_H
