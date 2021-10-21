#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include<QWidget>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QtSql>
#include<QSqlError>
class dbConnection : public QSqlDatabase
{
public:
    dbConnection();
    QSqlDatabase returnDB();
private:
    QSqlDatabase m_db ;

};

bool checktheexistance (QString m_login);
bool checkthecomptabiliti(QString m_login , QString m_passwd);

#endif // DBCONNECTION_H
