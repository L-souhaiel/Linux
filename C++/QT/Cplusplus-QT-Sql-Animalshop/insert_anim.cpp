#include "insert_anim.h"

Insert_Anim::Insert_Anim()
{
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    move(x, y);

    dbConnection db;

    selectlayout = new QVBoxLayout;
    listRace = new QComboBox;
    listspecies = new QComboBox ;
    groupDefinition = new QGroupBox("Select Specie and Race ");
    listelayout = new QVBoxLayout;


   if (db.returnDB().open())
   {

   QSqlQuery qry("SELECT nom_courant FROM Espece");


    while (qry.next())
    {

        QString species = qry.value(0).toString();
       listspecies->addItem(species);


    }

     listelayout->addWidget(listspecies);


   listelayout->addWidget(listRace);





   }


   else  {qDebug()<<db.lastError();}




   groupDefinition->setLayout(listelayout);


QObject::connect(listspecies,SIGNAL(currentIndexChanged(int)) ,this , SLOT(runrace()));



   QGroupBox *sexe_castration_box = new QGroupBox("Select the Castration ");
   castrate= new QRadioButton("Castrate");
   notCastrate= new QRadioButton("Not Castrate");
   castrate->setChecked(true);
   QHBoxLayout *layout_cast = new QHBoxLayout;
   layout_cast->addWidget(castrate);
   layout_cast->addWidget(notCastrate);
   sexe_castration_box->setLayout(layout_cast);


   QGroupBox *sexe_box = new QGroupBox("Select the Sexe ");
   QHBoxLayout *layoutsexe = new QHBoxLayout;
   male= new QRadioButton("Male");
   female= new QRadioButton("Female");
   male->setChecked(true);
   layoutsexe->addWidget(male);
   layoutsexe->addWidget(female);
   sexe_box->setLayout(layoutsexe);


   QGroupBox *layout_nom_color_date_box = new QGroupBox("information about The Animal ");
   QVBoxLayout *layout_color_priece_date = new QVBoxLayout;
   layoutnom = new QFormLayout;
   layout_preis_buy = new QFormLayout;
   layoutcolor = new QFormLayout;
   layoutprice = new QFormLayout;
   color = new  QLineEdit;
   nom= new  QLineEdit;
   date = new QDateEdit;
   preis_box = new QSpinBox;
   pries_buy_box= new QSpinBox;
   pries_buy_box->setValue(10);
   pries_buy_box->setRange(0 , 999999999);
   pries_buy_box->setPrefix("€");
   pries_buy_box->setSingleStep(10);
   preis_box->setValue(100);
   preis_box->setRange(0 , 999999999);
   preis_box->setPrefix("€");
   preis_box->setSingleStep(10);
   QFormLayout * layout_date = new QFormLayout;
   date->setDate(QDate::currentDate());
   date->setDisplayFormat("yyyy-MM-dd");
   layout_date->addRow("Enter Date of Birth " , date );
   layoutnom->addRow("Enter The Name  " ,nom );
   layoutcolor->addRow("Enter The Color  " , color);
   layoutprice->addRow("Enter The Price to sell " , preis_box);
   layout_preis_buy->addRow("Enter th buy preis" , pries_buy_box);
   layout_color_priece_date->addLayout(layoutnom);
   layout_color_priece_date->addLayout(layoutcolor);
   layout_color_priece_date->addLayout(layout_date);
   layout_color_priece_date->addLayout(layoutprice);
   layout_color_priece_date->addLayout(layout_preis_buy);
   layout_nom_color_date_box->setLayout(layout_color_priece_date);







   QPushButton *insert= new QPushButton("Insert");
   QPushButton *quit= new QPushButton("Quit");
   QHBoxLayout *layout_boutton = new QHBoxLayout;
   layout_boutton->addWidget(insert);
   layout_boutton->addWidget(quit);
   QGroupBox *boutton_box = new QGroupBox;
   boutton_box->setLayout(layout_boutton);


   selectlayout->addWidget(groupDefinition);
   selectlayout->addWidget(sexe_castration_box);
   selectlayout->addWidget(sexe_box);
   selectlayout->addWidget(layout_nom_color_date_box);
   selectlayout->addWidget(boutton_box);

   setLayout(selectlayout);
   setWindowTitle("Insertion");
   setFixedSize(450 , 600);

 connect(insert , SIGNAL(clicked()) , this , SLOT(insert_slot()));

 connect(quit , SIGNAL(clicked()) ,qApp, SLOT(quit()) );
}





void Insert_Anim::insert_slot()

{


    if ( nom->text() != ""  && color->text() != "")


    {

    if (listRace->currentText() !="")

    {

  QString espece_id_req("select id from Espece  where  nom_courant = ");
  espece_id_req += add_les(listspecies->currentText());
  QSqlQuery qry_espece_id(espece_id_req);
  qry_espece_id.next();
  QString espece_id = qry_espece_id.value(0).toString();



  QString race_id_req("select id from Race where nom = " );
  race_id_req +=add_les(listRace->currentText());
  QSqlQuery qry_race_id(race_id_req);
  qry_race_id.next();
  QString race_id =qry_race_id.value(0).toString();


  QString insert_req("insert into Animal (sexe , date_naissance , nom ,espece_id , race_id , color ,  castrate_or_not, price , price_buy  ) values (  ") ;

  if (male->isChecked())


  {


    insert_req+=add_les("M") + " , " +add_les( date->date().toString("yyyy-MM-dd")) + " , " + add_les( nom->text()) + " , " + add_les(espece_id) + " , " + add_les(race_id) + " , " +add_les( color->text()) + " , "  ;

    if ( castrate ->isChecked())

    {



   insert_req+=  add_les("Y") + " , " + add_les(preis_box->cleanText())+ " , " + add_les(pries_buy_box->cleanText())     + " )" ;

    }

    else  {insert_req+=  add_les("N") + " , " + add_les(preis_box->cleanText()) + " , " + add_les(pries_buy_box->cleanText())   + " )" ;}

  }


  else

  {

    insert_req+=add_les("F") + " , " +add_les( date->date().toString("yyyy-MM-dd")) + " , " + add_les( nom->text()) + " , " + add_les(espece_id) + " , " + add_les(race_id) + " , " +add_les( color->text()) + " , "  ;


    if ( castrate->isChecked())

    {

      insert_req+=  add_les("Y") + " , " + add_les(preis_box->cleanText()) + " , " + add_les(pries_buy_box->cleanText())    + " )" ;

    }

    else {insert_req+=  add_les("N") + " , " + add_les(preis_box->cleanText()) + " , " + add_les(pries_buy_box->cleanText())   + " )" ; }

  }


QSqlQuery qry_insert;

qDebug()<<insert_req;

if ( qry_insert.exec(insert_req))

{
    qDebug()<<" past !!";

  QString select_id_req(" select id from Animal where nom = ");
           select_id_req += add_les(nom->text()) + "and espece_id = " + add_les(espece_id) ;
           QSqlQuery qry_id_animal;

           if (qry_id_animal.exec(select_id_req))
           {
            qry_id_animal.next();
            QString id_Animal =  qry_id_animal.value(0).toString();

           QMessageBox::information(this , " Inscreption " , " Succefusl Inscreption of " + nom->text() + " . Herr id is : " + id_Animal);

           }

           else{ qDebug() << qry_id_animal.lastError() ;}


}

else { qDebug() << qry_insert.lastError();  QMessageBox::critical(this , "Error" ," the Name is Already taken by this species "  );}




}


    else  { QMessageBox::critical(this , "Error" , " Race is empty ") ;}



}
    else { QMessageBox::critical(this , "Error" , " Enter a Name and a Color" ) ; }


}




QString add_les (QString sans_guillemet)

{

    QString guillemet ("\"");
    QString aftermodif ;

    aftermodif=guillemet;
    aftermodif+= sans_guillemet;
    aftermodif+= guillemet;

    return aftermodif ;




}





void Insert_Anim::runrace()

{


int x = listRace->count();


   while( x > 0 )

                {listRace->removeItem(0);   x-=1; }





    QString selected_species = listspecies->currentText();
    QString requette_race ("SELECT nom From Race inner join Espece on Espece.id = Race.espece_id where Espece.nom_courant =  ");
    requette_race += add_les(selected_species);


      QSqlQuery qry2(requette_race);




    while (qry2.next())
    {

        QString race = qry2.value(0).toString();
        listRace->addItem(race);
    }




    listelayout->addWidget(listRace);
    groupDefinition->setLayout(listelayout);


}
