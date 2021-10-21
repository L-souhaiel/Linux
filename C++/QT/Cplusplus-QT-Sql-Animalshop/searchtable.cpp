#include "searchtable.h"
#include<QItemSelection>

searchtable::searchtable(QString querry_sql , QString login , QString password ) : m_login(login) , m_password(password)
{

   QVBoxLayout *layout = new QVBoxLayout;
   QPushButton *buy = new QPushButton("Buy");
   QPushButton *quitter = new QPushButton("Quit");
   view = new QTableView;
   db = dbConnection().returnDB();
   model = new QSqlQueryModel;
   model->setQuery(querry_sql);
   view->setModel(model);
   layout->addWidget(view);
   layout->addWidget(buy);
   layout->addWidget(quitter);
   setLayout(layout);
   setWindowTitle("Search Results ");
   resize(600, 600);
   QMessageBox::information(this, "choose id ", " select the id of the animal you want to buy and press buy");
   connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
   connect(buy , SIGNAL(clicked()) , this,SLOT(buy_selection()));
   int x = ((screenGeometry.width() - this->width()) / 2);
   int y = ((screenGeometry.height() - this->height()) / 2);
   move(x, y);

}




QString add_les_guillemet2 (QString sans_guillemet)

{

    QString guillemet ("\"");
    QString aftermodif ;

    aftermodif=guillemet;
    aftermodif+= sans_guillemet;
    aftermodif+= guillemet;

    return aftermodif ;

}










void searchtable::buy_selection()

{

   QItemSelectionModel *selection =  view->selectionModel();
   QModelIndex indexElementSelectionne = selection->currentIndex();
   QVariant elementSelectionne = model->data(indexElementSelectionne, Qt::DisplayRole);


   if ( indexElementSelectionne.column() == 0)

   {

      QString price_req (" select price from Animal where  id = ");
       price_req +=elementSelectionne.toString();
       QSqlQuery qry_price(price_req);
       qry_price.next();
       QString price = qry_price.value(0).toString();






       QString price_buy_req (" select price_buy from Animal where id = ");
       price_buy_req += elementSelectionne.toString();
       QSqlQuery qry_price_buy(price_buy_req);
       qry_price_buy.next();
       QString price_buy= qry_price_buy.value(0).toString();





       QString user_id_req ("select id  from Custmer where user_name =  ");
          user_id_req +=add_les_guillemet2( m_login);
          QSqlQuery user_id_qry(user_id_req);
          user_id_qry.next();
          QString user_id = user_id_qry.value(0).toString();

          QDateEdit *date = new QDateEdit;
          date->setDisplayFormat("yyyy-MM-dd");
          date->setDate(QDate::currentDate());

          QString date_sal = date->date().toString("yyyy-MM-dd");

          qDebug()<<date_sal;


           QString nom (" select nom from Animal where  id = ");
           nom +=elementSelectionne.toString();
           QSqlQuery qry_nom(nom);
           qry_nom.next();
           QString name = qry_nom.value(0).toString();



           QString race_req("select nom from Race where id = (select race_id from Animal where id =  ") ;
           race_req+=elementSelectionne.toString() + " )";
           QSqlQuery qry_race(race_req);
           qry_race.next();
           QString race = qry_race.value(0).toString();



           QString espece_req(" select nom_courant from Espece where id = (select espece_id from Animal where id = ");
           espece_req+=elementSelectionne.toString() + ") ";
           QSqlQuery qry_espece(espece_req);
           qry_espece.next();
           QString espece = qry_espece.value(0).toString();



           QString delete_req("delete from Animal where id = ");
           delete_req+=elementSelectionne.toString();
           QSqlQuery qry_delte(delete_req);


           qry_delte.exec();


               qDebug()<<delete_req;
               QString insertion_Animal_gebaught("insert into Animal_gebaught values ( ");
               insertion_Animal_gebaught+= elementSelectionne.toString() + " , " +add_les_guillemet2( race) + " , " +add_les_guillemet2( espece) + " , " + add_les_guillemet2( name) + " )" ;
               QSqlQuery qry_insert;


               qDebug()<<insertion_Animal_gebaught;
               if (qry_insert.exec(insertion_Animal_gebaught))

               {
                  qDebug()<<insertion_Animal_gebaught;
                  QString insertion_who_gebaught (" insert into who_baught values ( ");
                  insertion_who_gebaught+= user_id + " , " + elementSelectionne.toString() + " , " +  price + " , " + add_les_guillemet2(date_sal) + " , " +   price_buy   +  ") ";
                  QSqlQuery qry_insert2;


                  if (qry_insert2.exec(insertion_who_gebaught))

                  {




                      QMessageBox::information(this , " Good " , " Successful Sale of "+ name );

                  }

                  else
                  {

                   qDebug()<<qry_insert2.lastError() ;
                  QMessageBox::critical(this , " Error " , " Animal is already saled ");
                  }


               }


               else

               {


                qDebug()<<qry_insert.lastError() ;

               }





         }
   else

   {
       QMessageBox::critical(this , " Error " , " please select the id of the Animal ");
   }
}


