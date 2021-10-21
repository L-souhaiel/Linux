#ifndef SEARCHTABLE_H
#define SEARCHTABLE_H
#include<QWidget>
#include<QtSql>
#include<QtWidgets>
#include"dbconnection.h"


class searchtable : public QWidget
{
       Q_OBJECT
public:


    searchtable(QString querry_sql, QString login , QString password );

public slots :

    void buy_selection();


private :
    QString m_login ;
    QString m_password;
    QTableView *view;
    QSqlQueryModel *model;
     QSqlDatabase db;
         QRect screenGeometry = QApplication::desktop()->screenGeometry();
};

#endif // SEARCHTABLE_H
