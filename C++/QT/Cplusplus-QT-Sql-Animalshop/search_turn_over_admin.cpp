#include "search_turn_over_admin.h"
#include<QStack>

search_turn_over_admin::search_turn_over_admin(QString qry ,QString price_buy_req , QString price_req , QString best_race_seller_req , QString best_species_seller_req , QString date ) :   m_price_buy_req(price_buy_req), m_price_req(price_req)  ,best_sel_race_req(best_race_seller_req) , best_sel_specie_req(best_species_seller_req)
{


QVBoxLayout *principallayout = new QVBoxLayout ;
QHBoxLayout *les_prixlayout  = new QHBoxLayout;
QHBoxLayout *best_seller_layout =new QHBoxLayout;

view= new QTableView;
model= new QSqlTableModel;
model->setQuery(qry);
view->setModel(model);
principallayout->addWidget(view);

QFormLayout *formlayout_price_buy =  new QFormLayout;
QFormLayout *formlayout_price_sell = new QFormLayout;
QFormLayout *formlayout_profits = new QFormLayout;
QFormLayout *bestseler_race_layout= new QFormLayout;
QFormLayout *bestseler_specie_layout= new QFormLayout;

price_buy = new QLineEdit;
price_sel = new QLineEdit;
profitss = new QLineEdit ;
best_race_sell= new QLineEdit;
best_specie_sell= new QLineEdit;




formlayout_price_buy->addRow("Total Buy Price" , price_buy);
formlayout_price_sell->addRow("Total Sell Price" , price_sel);
formlayout_profits->addRow("Total Profits From " + date , profitss);
bestseler_race_layout->addRow(" Best Seller Race From " + date , best_race_sell);
bestseler_specie_layout->addRow("Best Seller Spiece From " + date , best_specie_sell);



les_prixlayout->addLayout(formlayout_price_buy);
les_prixlayout->addLayout(formlayout_price_sell);
les_prixlayout->addLayout(formlayout_profits);
principallayout->addLayout(les_prixlayout);


best_seller_layout->addLayout(bestseler_specie_layout);
best_seller_layout->addLayout(bestseler_race_layout);
principallayout->addLayout(best_seller_layout);

setLayout(principallayout);
setWindowTitle("Diagramme");

int x = ((screenGeometry.width() - this->width()) / 2);
int y = ((screenGeometry.height() - this->height()) / 2);
move(x, y);

}




void search_turn_over_admin::insertions()

{


    QSqlQuery qry_price_buy;
    if (qry_price_buy.exec(m_price_buy_req))
    {
    int price_buyy= 0 ;
    while ( qry_price_buy.next()) {price_buyy += qry_price_buy.value(0).toInt();}

     QSqlQuery qry_price_sell;
     if (qry_price_sell.exec(m_price_req))
     {
     int price_selll = 0 ;
      while (qry_price_sell.next()) { price_selll +=qry_price_sell.value(0).toInt();}

      int profits = price_selll - price_buyy ;


    QString pricebuy=QString::number(price_buyy);
    QString pricesell= QString::number(price_selll);
    QString profit = QString::number(profits);

    price_buy->setText("€ " + pricebuy);
    price_sel->setText("€ " + pricesell);
    profitss->setText("€ "+ profit);



    QStack<QString> *listSpecie = new QStack<QString>;
    QStack<QString> *listRace = new QStack<QString>;

    QSqlQuery qry_list_specie;
    QSqlQuery qry_list_race;



    if ( qry_list_specie.exec(best_sel_specie_req))

    {

qDebug()<<"1";

    while (qry_list_specie.next())

    {
     QString species  = qry_list_specie.value(0).toString();
     listSpecie->push_front(species);

    }
    qDebug()<<best_sel_race_req;

    if (qry_list_race.exec(best_sel_race_req))

    {
        qDebug()<<"2";
        while(qry_list_race.next())

        {

            QString race = qry_list_race.value(0).toString();
            listRace->push_front(race);

        }

    QString bestrace = returnbestrace(*listRace);
    QString bestspeci = returnbestspecie(*listSpecie);


    qDebug()<<listRace->size();
    qDebug()<<bestrace;


    best_race_sell->setText(bestrace);
    best_specie_sell->setText(bestspeci);

    }
    else  { qDebug()<<qry_list_race.lastError();}



     }

    else  {qDebug()<<qry_list_specie.lastError();}

}
     else

     {
         qDebug() << qry_price_sell.lastError();
     }
  }

    else { qDebug()<<qry_price_buy.lastError();}




}





QString search_turn_over_admin::returnbestrace(QStack<QString> listrace)

{


    int index_race= 0  ;
    int number_racelast= 0;
    int number_race = 0;

    for ( int i = 0 ; i < listrace.size() ; i++)

    {

          number_race=0;

          for ( int  j = 0 ; j < listrace.size(); j++)

        {


            if (listrace[i]==listrace[j])

            {
               number_race +=1;
            }

        }


                                            if ( number_racelast < number_race)
                                                                     {
                                                   number_racelast = number_race;
                                                       index_race = i ;}

    }


      qDebug()<<listrace[index_race];
    return listrace[index_race];



}









QString search_turn_over_admin::returnbestspecie(QStack<QString> listspecie)

{


    int index_race= 0  ;
    int number_racelast= 0;
    int number_race = 0;

    for ( int i = 0 ; i < listspecie.size() ; i++)

    {

          number_race=0;

          for ( int  j = 0 ; j < listspecie.size(); j++)

        {


            if (listspecie[i]==listspecie[j])

            {
               number_race +=1;
            }

        }


                                            if ( number_racelast < number_race)
                                                                     {
                                                   number_racelast = number_race;
                                                       index_race = i ;}

    }


      qDebug()<<listspecie[index_race];
    return listspecie[index_race];



}


















