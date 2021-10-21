#ifndef BASES_MENU_HBASES_MENU_H
#define BASES_MENU_HBASES_MENU_H


#include <QtGui>
#include <QtWidgets>
#include<QtSql>
#include<QSqlDatabase>
#include <QSqlQuery>
#include "dbconnection.h"
#include "searchtable.h"



class selection_Animal: public QWidget
{
    Q_OBJECT


    public:
        selection_Animal(QString login , QString password);



public slots : void run( );
               void run2_list_color();
               void search();




    private:


        QVBoxLayout* selectlayout;
        QComboBox *listspecies ;
        QComboBox *listRace ;
        QGroupBox *groupDefinition;
        QDateEdit *date_of_birth;
        QFormLayout *preis_date_layout;
        QGroupBox *sexe_groupe ;
        QHBoxLayout *sexe_layout;
        QRadioButton* male ;
        QRadioButton* female;
        QSpinBox *preis_box;
        QVBoxLayout *preis_layout ;
        QLabel *preis_label;
        QComboBox *liste_color;
        QVBoxLayout *option_layout;
        QHBoxLayout *castration_layout;
        QRadioButton *castrate1;
        QRadioButton *castrate2;
        QGroupBox *groupCommentaires;
        QPushButton *generer;
        QPushButton *quitter;
        QSqlDatabase m_db ;


        QString m_login;
        QString m_password;

            QRect screenGeometry = QApplication::desktop()->screenGeometry();

};

#endif
 bool if_exsist(QStack<QString>  pile , QString word);

QString add_les_guillemet (QString);
