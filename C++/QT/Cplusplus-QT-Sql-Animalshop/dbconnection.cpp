#include "dbconnection.h"
#include"Selection_Animal.h"

dbConnection::dbConnection()
{

    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("...");
    m_db.setUserName("...");
    m_db.setPassword("....");
    m_db.setDatabaseName(".....");
    m_db.open();

}





QSqlDatabase dbConnection::returnDB() { return m_db ; }





bool checktheexistance (QString m_login)
{

    bool x = true ;
    dbConnection db;
    if (db.returnDB().open())
    {
        QString qry_string("select * from Custmer where user_name =  ");
                 qry_string +=add_les_guillemet(m_login);
         QSqlQuery qry(qry_string);
         qDebug()<<qry.size();
         if (qry.size()> 0 ) { x = true; }
         else  {x = false ; }
    }

    else  { qDebug()<<db.lastError(); }
    return x ;
}




bool checkthecomptabiliti(QString m_login , QString m_passwd)
{

    bool x = false ;
    dbConnection db;
    if (db.returnDB().open())
    {
        QString qry_string("select password from Custmer where user_name =  ");
                 qry_string +=add_les_guillemet(m_login);
                  qDebug()<<qry_string;
         QSqlQuery qry;
         qry.exec(qry_string);
         qry.next();
         QString password = qry.value(0).toString();
         if (password == m_passwd){x = true;}
         else  { x = false ;}
      }

    else  {qDebug()<<db.lastError();}

         return x ;

}



