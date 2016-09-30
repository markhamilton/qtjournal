#include "localapi.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

LocalApi::LocalApi()
{
    createConnection();
}

bool LocalApi::createConnection()
{
    // open default database
    // there's no real reason to make this flexible at the moment
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");

    if(!db.open())
    {
        QMessageBox::critical(0, "Cannot open database",
            "Unable to establish a database connection.\n"
            "This program needs SQLite support. Please read "
            "the Qt SQL driver documentation for information how "
            "to build it.\n\n"
            "Click Cancel to exit.", QMessageBox::Cancel);
        return false;
    }

    setupTables();
    demoData();

    qDebug() << "Showing tables...";
    qDebug() << db.tables();

    return true;
}

bool LocalApi::setupTables()
{
    QSqlQuery query(db);

    qDebug() << "Creating tables in memory";

    // TODO: constraints for meta
    try
    {
        query.exec("create table if not exists journal (id int primary key, title text, color text)");
        query.exec("create table if not exists entry (id int primary key, content text, datetime)");
        query.exec("create table if not exists entry_meta (k text primary key, v text)");
    }
    catch(...)
    {
        return false;
    }

    return true;
}

bool LocalApi::demoData()
{
    QSqlQuery query(db);

    for(int i = 1; i < 1000; ++i)
        query.exec("insert into journal (id, title) values (" + QString::number(i) + ", \"Test Journal " + QString::number(i) + "\")");

    return true;
}
