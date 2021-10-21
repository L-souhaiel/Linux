#ifndef SEARCH_TURN_OVER_ADMIN_H
#define SEARCH_TURN_OVER_ADMIN_H
#include<QtWidgets>
#include"dbconnection.h"
#include<QtSql>
#include"dbconnection.h"
#include "Selection_Animal.h"


class search_turn_over_admin : public QWidget
{
    Q_OBJECT
public:
    search_turn_over_admin(QString qry ,QString price_buy_req , QString price_req , QString best_race_seller_req , QString best_species_seller_req , QString date);
    void insertions();
    QString returnbestrace(QStack<QString> listrace);
    QString returnbestspecie(QStack<QString> listspeci);

private :

    QTableView *view;
    QSqlQueryModel *model;
    QSqlDatabase db;
    QString m_price_buy_req;
    QString m_price_req ;
    QString best_sel_race_req;
    QString best_sel_specie_req;

    QLineEdit *price_buy ;
    QLineEdit *price_sel;
    QLineEdit *profitss ;
    QLineEdit *best_race_sell;
    QLineEdit *best_specie_sell;
        QRect screenGeometry = QApplication::desktop()->screenGeometry();


};

#endif // SEARCH_TURN_OVER_ADMIN_H
