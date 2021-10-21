#include "Selection_Animal.h"
#include<QStack>


selection_Animal::selection_Animal(QString login , QString password):m_login(login) , m_password(password)
{


     // Groupe : Select type : ( species , race , preis , date of birth , sexe )



    m_db = dbConnection().returnDB() ;










    selectlayout = new QVBoxLayout;
    groupDefinition = new QGroupBox("Select Type : ");
    groupDefinition->setLayout(selectlayout);
    listspecies  = new QComboBox;
    listRace = new QComboBox;






/* this species Liste */

        if(m_db.open())
        {

            qDebug() << "Opened!";
            listspecies->addItem("Select a species of animal");
             QSqlQuery qry("SELECT nom_courant FROM Espece");





             while (qry.next())
             {

                 QString species = qry.value(0).toString();
                listspecies->addItem(species);


             }


             selectlayout->addWidget(listspecies);


             if( !qry.exec() )
                 qDebug() << qry.lastError().text();
             else
                 qDebug( "Inserted!" );
          }


        else
        {

            qDebug() <<"Connection failed liste species" << m_db.lastError().text();
        }



/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

        m_db.close();




/* date of birth layout *****************************************/

        date_of_birth = new QDateEdit;
        date_of_birth->setDate(QDate::currentDate());
        date_of_birth->setDisplayFormat("yyyy-MM-dd");
        preis_date_layout = new QFormLayout;
        preis_date_layout->addRow("Date of Birth" , date_of_birth);
        selectlayout->addLayout(preis_date_layout);

/* sexe layout *****************************************************/


        sexe_groupe = new QGroupBox("Select Animal Sexe");
        sexe_groupe->setCheckable(true);
        sexe_groupe->setChecked(false);
        sexe_layout = new QHBoxLayout;
         male = new QRadioButton("Male");
        female = new QRadioButton("Female");
        sexe_layout->addWidget(male);
        sexe_layout->addWidget(female);
        female->setChecked(true);
        sexe_groupe->setLayout(sexe_layout);
        selectlayout->addWidget(sexe_groupe);






     /*  preis layout **************************************************/

preis_box = new QSpinBox ;
preis_layout = new QVBoxLayout;
preis_label = new QLabel("Enter a Maximal preis until 10000000 ");
preis_box->setSingleStep(10);
preis_box->setValue(100);
preis_box->setPrefix("€");
preis_box->setRange(0,10000000);
preis_layout->addWidget(preis_label);
preis_layout->addWidget(preis_box);
selectlayout->addLayout(preis_layout);


        /* this  Races layout ****************************************/



        listRace->addItem("Select a Race of the selected Species ");
        listRace->addItem("Any Race ");
        selectlayout->addWidget(listRace);
        groupDefinition->setLayout(selectlayout);

QObject::connect(listspecies,SIGNAL(currentIndexChanged(int)) ,this , SLOT(run()));



    /* Groupe : Commentaires ********************************************/


    option_layout = new QVBoxLayout;
    groupCommentaires = new QGroupBox("More Option ");
    groupCommentaires->setCheckable(true);
    groupCommentaires->setChecked(false);
    castration_layout = new QHBoxLayout;
    castrate1 = new QRadioButton("Castrate");
    castrate2 = new QRadioButton("Not Castrate");
    castration_layout->addWidget(castrate1);
    castration_layout->addWidget(castrate2);
    liste_color = new QComboBox;


     liste_color->addItem("Select Color");

     QObject::connect(listspecies , SIGNAL(currentIndexChanged(int)) ,this ,SLOT(run2_list_color()));




    option_layout->addLayout(castration_layout);
    option_layout->addWidget(liste_color);



    groupCommentaires->setLayout(option_layout);




    generer = new QPushButton("&Search");
    quitter = new QPushButton("&Quit");

    QHBoxLayout *boutonsLayout = new QHBoxLayout;
    boutonsLayout->setAlignment(Qt::AlignRight);

    boutonsLayout->addWidget(generer);
    boutonsLayout->addWidget(quitter);


    // D�finition du layout principal, du titre de la fen�tre, etc.





    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(groupDefinition);
    layoutPrincipal->addWidget(groupCommentaires);
    layoutPrincipal->addLayout(boutonsLayout);

    setLayout(layoutPrincipal);
    setWindowTitle("Animal Shop");
    setWindowIcon(QIcon("icone.png"));
    resize(400, 450);


    // Connexions des signaux et des slots
    connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(generer, SIGNAL(clicked()) , this , SLOT(search() ) );
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    move(x, y);


}




   void selection_Animal::search()

   {


       QString qry_search("");


        if (listspecies->currentText() != "Select a species of animal" )



            {




                if (listRace->currentText() != "Select a Race of the selected Species ")


                      {


                          if (sexe_groupe->isChecked() )


                                {


                                   if (groupCommentaires->isChecked())


                                          {

                                                if (liste_color->currentText() != "Select Color")

                                                {

                                                    if ( castrate1->isChecked())

                                                         {

                                                           if ( female->isChecked() )
                                                           {

                                                               qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                                               qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                                               qry_search += " and ( Animal.sexe = \"F\"  ) and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) and (Animal.color =  " +add_les_guillemet( liste_color->currentText()) + " )" ;

                                                          }


                                                           else


                                                           {

                                                               qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                                               qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                                               qry_search += " and ( Animal.sexe = \"M\"  ) and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) and (Animal.color =  " +add_les_guillemet( liste_color->currentText() )+ " )" ;

                                                            }


                                                      }


                                                    else

                                                    {

                                                      if ( female->isChecked() )

                                                      {

                                                          qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                                          qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                                          qry_search += " and ( Animal.sexe = \"F\"  ) and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + ") and (Animal.color =  " +add_les_guillemet( liste_color->currentText()) + " )" ;


                                                      }

                                                      else

                                                      {


                                                          qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                                          qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                                          qry_search += " and ( Animal.sexe = \"M\"  ) and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) and (Animal.color =  " + add_les_guillemet( liste_color->currentText()) + " )" ;

                                                      }







                                                    }

                                                }

                                                    else

                                                    {


                                                      if ( castrate1->isChecked())

                                                      {


                                                       if  ( female->isChecked() )
                                                       {


                                                           qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                                           qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                                           qry_search += " and ( Animal.sexe = \"F\"  ) and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;




                                                        }

                                                       else

                                                       {


                                                           qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                                           qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                                           qry_search += " and ( Animal.sexe = \"M\"  ) and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;




                                                       }

                                                      }

                                                      else


                                                      {

                                                         if  ( female->isChecked() )

                                                         {

                                                             qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                                             qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                                             qry_search += " and ( Animal.sexe = \"F\"  ) and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;


                                                         }

                                                         else

                                                         {


                                                             qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                                             qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                                             qry_search += " and ( Animal.sexe = \"M\"  ) and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;


                                                         }


                                                         }

                                                        }




                                                    }


                                   else

                                   {



                                   if  ( female->isChecked() )


                                   {


                                       qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant = ";
                                       qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                       qry_search += " and ( Animal.sexe = \"F\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;

                                   }

                                   else
                                   {


                                       qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                       qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                       qry_search += " and ( Animal.sexe = \"M\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;



                                   }

                                   }



                                   }

                          else


                          {

                              if (groupCommentaires->isChecked())


                              {




                                  if (liste_color->currentText() != "Select Color")

                                  {

                                      if ( castrate1->isChecked())

                                           {



                                          qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                          qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                          qry_search += "  and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) and (Animal.color =  " + add_les_guillemet( liste_color->currentText()) + " )" ;


                                           }


                                      else


                                      {


                                          qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                          qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                          qry_search += "  and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) and (Animal.color =  " +add_les_guillemet( liste_color->currentText()) + " )" ;




                                      }


                                  }


                                  else
                                  {


                                      if ( castrate1->isChecked())

                                      {


                                          qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                          qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                          qry_search += "  and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " )";




                                      }

                                      else
                                      {


                                          qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                          qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                          qry_search += "  and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " )";





                                      }

                                  }


                              }

                              else
                              {



                                  qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                  qry_search +=add_les_guillemet( listspecies->currentText()) + " ) and ( Race.nom = " + add_les_guillemet( listRace->currentText()) + " )" ;
                                  qry_search += "  and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " )";





                              }


                             }




                            }



                else
                {

                  if (sexe_groupe->isChecked())

                  {


                      if (groupCommentaires->isChecked())

                      {



                          if (liste_color->currentText()!= "Select Color")

                          {


                              if (castrate1->isChecked())

                              {


                                  if (female->isChecked())

                                  {


                                      qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                      qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                                      qry_search += " and ( Animal.sexe = \"F\"  ) and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) and (Animal.color =  " +add_les_guillemet( liste_color->currentText()) + " )" ;



                                  }


                                  else

                                  {


                                      qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                      qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                                      qry_search += " and ( Animal.sexe = \"M\"  ) and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) and (Animal.color =  " +add_les_guillemet( liste_color->currentText()) + " )" ;



                                  }





                              }


                              else



                              {



                                if (female->isChecked())
                                {



                                    qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                    qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                                    qry_search += " and ( Animal.sexe = \"F\"  ) and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) and (Animal.color =  " +add_les_guillemet( liste_color->currentText()) + " )" ;




                                }




                                else



                                {



                                    qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                    qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                                    qry_search += " and ( Animal.sexe = \"M\"  ) and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) and (Animal.color =  " +add_les_guillemet( liste_color->currentText()) + " )" ;




                                }




                              }


                          }



                              else



                             {

                                if (castrate1->isChecked())


                                {

                                    if (female->isChecked())

                                    {

                                        qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                        qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                                        qry_search += " and ( Animal.sexe = \"F\"  ) and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;


                                    }



                                    else

                                    {


                                        qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                        qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                                        qry_search += " and ( Animal.sexe = \"M\"  ) and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;


                                    }



                              }


                                else

                                {

                                 if (female->isChecked())


                                 {


                                     qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                     qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                                     qry_search += " and ( Animal.sexe = \"F\"  ) and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;


                                 }

                                 else

                                 {


                                     qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                     qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                                     qry_search += " and ( Animal.sexe = \"M\"  ) and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;

                                 }




                                }




                          }




                         }



                      else


                      {


                  if (female->isChecked())


                  {



                      qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                      qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                      qry_search += " and ( Animal.sexe = \"F\"  )  and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;



                 }


                  else



                  {

                      qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                      qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                      qry_search += " and ( Animal.sexe = \"F\"  )  and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;


                  }



                 }



                }




                  else


                  {
                      if (groupDefinition->isChecked())


                      {



                          if (liste_color->currentText() != "Select Color")

                          {


                              if (castrate1->isChecked())

                              {



                                  qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                  qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                                  qry_search += "  and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) and (Animal.color =  " +add_les_guillemet( liste_color->currentText()) + " )" ;

                              }


                              else


                              {


                                  qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                  qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                                  qry_search += "  and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) and (Animal.color =  " +add_les_guillemet( liste_color->currentText()) + " )" ;

                              }

                          }



                             else


                                {

                                 if (castrate1->isChecked())


                                 {

                                     qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                     qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                                     qry_search += "  and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) ";


                                 }



                                 else


                                 {

                                     qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                                     qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                                     qry_search += "  and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) ";


                                 }



                              }




                                   }



                      else
                      {




                          qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";
                          qry_search +=add_les_guillemet( listspecies->currentText()) + " ) ";
                          qry_search += " and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) ";




                      }


                      }

                     }

  }



        else


        {





                      if (sexe_groupe->isChecked() )


                            {


                               if (groupCommentaires->isChecked())


                                      {



                                                if ( castrate1->isChecked())

                                                     {

                                                       if ( female->isChecked() )
                                                       {

                                                           qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where  ";
                                                           qry_search += "  ( Animal.sexe = \"F\"  ) and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;

                                                      }


                                                       else


                                                       {

                                                           qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where  ";
                                                           qry_search += "  ( Animal.sexe = \"M\"  ) and ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;


                                                        }


                                                  }


                                                else

                                                {

                                                  if ( female->isChecked() )

                                                  {

                                                      qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where  ";
                                                      qry_search += " ( Animal.sexe = \"F\"  ) and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + ") " ;


                                                  }

                                                  else

                                                  {


                                                      qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where  ";
                                                      qry_search += " ( Animal.sexe = \"M\"  ) and ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;

                                                  }



                                                }








                                                }


                               else

                               {



                               if  ( female->isChecked() )


                               {


                                   qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where  ";

                                   qry_search += " ( Animal.sexe = \"F\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;

                               }

                               else
                               {


                                   qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where  ";

                                   qry_search += "  ( Animal.sexe = \"M\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;



                               }

                               }



                               }

                      else


                      {

                          if (groupCommentaires->isChecked())


                          {





                                  if ( castrate1->isChecked())

                                       {



                                      qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where  ";

                                      qry_search += "   ( Animal.castrate_or_not = \"Y\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;


                                       }


                                  else


                                  {


                                      qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ( Espece.nom_courant  = ";

                                      qry_search += " ( Animal.castrate_or_not = \"N\"  ) and  (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " ) " ;




                                  }


                              }


                              else
                              {





                                      qry_search +="select Animal.id  , Animal.nom as nom , Espece.nom_courant  as espece , Race.nom as race  , Animal.date_naissance  ,   Animal.sexe ,  Animal.castrate_or_not,  Animal.price from Animal inner join Espece on Espece.id=Animal.espece_id inner join Race on Race.id = Animal.race_id where ";

                                      qry_search += "    (Animal.date_naissance >   " + add_les_guillemet(date_of_birth->date().toString("yyyy-MM-dd")  ) + " ) and (Animal.price <= " + add_les_guillemet(preis_box->cleanText()) + " )";




                                  }

                      }


        }



        qDebug()<<qry_search;
        m_db.open();
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(qry_search);
        if (model->rowCount()==0) { QMessageBox::critical(this , "Sorry" , " We Can Not found Any Animal with those option ");}
        else

        {

        searchtable * search = new searchtable(qry_search ,m_login , m_password );
        search->show();
         }

        }




QString add_les_guillemet (QString sans_guillemet)

{

    QString guillemet ("\"");
    QString aftermodif ;

    aftermodif=guillemet;
    aftermodif+= sans_guillemet;
    aftermodif+= guillemet;

    return aftermodif ;




}




void selection_Animal::run()

{


int x = listRace->count();

   while( x > 1 )

                {listRace->removeItem(2);   x-=1;  }



      if(m_db.open())

      {

          qDebug() << "Thread Opened!";


    QString selected_species = listspecies->currentText();
    QString requette_race ("SELECT nom From Race inner join Espece on Espece.id = Race.espece_id where Espece.nom_courant =  ");
    requette_race += add_les_guillemet(selected_species);


      QSqlQuery qry2(requette_race);




    while (qry2.next())
    {

        QString race = qry2.value(0).toString();
        listRace->addItem(race);
    }




     if( !qry2.exec() )
       qDebug() << qry2.lastError().text();
   else
       qDebug( "Inserted Thread!" );

      }


    else
    {
        qDebug() <<"Connection failed Thread" << m_db.lastError().text();
    }





selectlayout->addWidget(listRace);
groupDefinition->setLayout(selectlayout);


m_db.close();


}




void selection_Animal::run2_list_color()

{


int x = liste_color->count();

   while( x > 1 )

                {liste_color->removeItem(1);   x-=1;  }



      if(m_db.open())

      {

          qDebug() << "Thread Opened!";


    QString selected_species = listspecies->currentText();
    QString requette_race ("SELECT color From Animal inner join Espece on Espece.id = Animal.espece_id where Espece.nom_courant =  ");
    requette_race += add_les_guillemet(selected_species);


      QSqlQuery qry2(requette_race);

      QStack<QString> tableau;
      qDebug()<<tableau.size();

    while (qry2.next())
    {

        QString color = qry2.value(0).toString();
         x = 0 ;


        if(tableau.size()==0)
                              {


            tableau.push_back(color);
                               }


        else  if (tableau.size() > 0)

        {

     if (!if_exsist(tableau,color))
        {
        tableau.push_back(color);


         }

}
     }








        for (int z = 0 ; z < tableau.size(); z++) { liste_color->addItem(tableau[z]) ; }














     option_layout->addWidget(liste_color);

     if( !qry2.exec() )
       qDebug() << qry2.lastError().text();
   else
       qDebug( "Inserted Thread!" );

      }


    else
    {
        qDebug() <<"Connection failed Thread" << m_db.lastError().text();
    }




option_layout->addWidget(liste_color);

groupCommentaires->setLayout(option_layout);


m_db.close();


}






bool if_exsist(QStack<QString>  pile , QString word)
{


    int x = 0 ;
    bool la = false;

    do
    {
        if (pile[x] == word){ la =true;}

        x+=1;


    }while(x < pile.size() );

    return la ;



}
