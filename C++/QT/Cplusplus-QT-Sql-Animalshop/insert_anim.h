#ifndef INSERT_ANIM_H
#define INSERT_ANIM_H
#include<QtWidgets>
#include"dbconnection.h"

class Insert_Anim  : public QWidget
{
    Q_OBJECT
public:
    Insert_Anim();

public slots :
   void runrace();
   void insert_slot();

private :

   QComboBox *listspecies ;
   QComboBox *listRace ;
   QSpinBox *preis_box;
   QSpinBox *pries_buy_box;
   QDateEdit *date;
   QRadioButton *castrate;
   QRadioButton *notCastrate;
   QRadioButton *male ;
   QRadioButton *female ;
   QLineEdit *nom ;
   QLineEdit *color ;
   QFormLayout *layoutcolor;
   QFormLayout *layoutnom ;
   QFormLayout *layoutprice;
   QFormLayout *layout_preis_buy;
    QVBoxLayout *selectlayout;
    QGroupBox * groupDefinition;
    QVBoxLayout *listelayout;
        QRect screenGeometry = QApplication::desktop()->screenGeometry();
};

#endif // INSERT_ANIM_H



QString add_les (QString sans_guillemet);

