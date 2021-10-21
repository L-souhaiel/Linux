#include "turnover_class.h"

turnOver_class::turnOver_class()
{   
    QVBoxLayout * layout = new QVBoxLayout;
    QPushButton *search = new QPushButton("Search");
    QPushButton *quit = new QPushButton("Quit");
    QFormLayout *layoutdate = new QFormLayout;
    date= new QDateEdit;
    date->setDate(QDate::currentDate());
    date->setDisplayFormat("yyyy-MM-dd");
    layoutdate->addRow("Enter From which Date To Calculate the Turn " , date );
    layout->addLayout(layoutdate);
    layout->addWidget(search);
    layout->addWidget(quit);
    setLayout(layout);
    setWindowTitle("Turnover Search");
    connect(search , SIGNAL(clicked()) , this , SLOT(searching()));
    connect(quit,SIGNAL(cliecked()) , qApp , SLOT(quit()));
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    move(x, y);

}




QString add_les_guillemet3 (QString sans_guillemet)

{
    QString guillemet ("\"");
    QString aftermodif ;
    aftermodif=guillemet;
    aftermodif+= sans_guillemet;
    aftermodif+= guillemet;
    return aftermodif ;

}

void turnOver_class::searching()

{

QString search_req (" select Animal_gebaught.nom as Animal_Name , Animal_gebaught.espece as Animal_specie , Animal_gebaught.race as Animal_race , who_baught.price as Price , who_baught.date_of_sell  as Date_of_sell , who_baught.price_buy as Price_buy    ,Custmer.user_name as Buyer  from  ");
search_req += " who_baught inner join Animal_gebaught on who_baught.Animal_id = Animal_gebaught.id  ";
search_req += " inner join Custmer on Custmer.id =who_baught.user_id  where who_baught.date_of_sell >=  ";
search_req += add_les_guillemet3( date->date().toString("yyyy-MM-dd"));
qDebug()<< search_req;

QString price_buy_req("select price_buy  from who_baught  where date_of_sell >= ");
        price_buy_req+=add_les_guillemet3(date->date().toString("yyyy-MM-dd"));

 QString price_req("select price  from who_baught where date_of_sell >= ");
                price_req+=add_les_guillemet3(date->date().toString("yyyy-MM-dd"));


 QString best_seller_species_req("select  Animal_gebaught.espece from Animal_gebaught inner join who_baught on Animal_gebaught.id = who_baught.Animal_id where who_baught.date_of_sell >=  ");
                         best_seller_species_req+= add_les_guillemet3(date->date().toString("yyyy-MM-dd"));


QString best_seller_race_req("select  Animal_gebaught.race from Animal_gebaught inner join who_baught on Animal_gebaught.id = who_baught.Animal_id where who_baught.date_of_sell >=  ");
        best_seller_race_req+= add_les_guillemet3(date->date().toString("yyyy-MM-dd"));



        search_turn_over_admin *searching_turn = new search_turn_over_admin(search_req , price_buy_req , price_req , best_seller_race_req , best_seller_species_req , date->date().toString("yyyy-MM-dd") ) ;
        searching_turn->insertions();
        searching_turn->show();



}
