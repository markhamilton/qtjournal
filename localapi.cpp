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

    if(! setupTables()) return false;
    demoData();

    qDebug() << "Showing tables..." << db.tables();

    return true;
}

bool LocalApi::setupTables()
{
    QSqlQuery query(db);

    qDebug() << "Creating tables in memory...";

    try
    {
        // TODO: constraints for meta
        query.exec("create table if not exists journal (id int primary key, title text, color text)");
        query.exec("create table if not exists entry (id int primary key, content text, published datetime key)");
        query.exec("create table if not exists entry_meta (k text primary key, v text)");
        query.exec("create table if not exists tag(id int primary key, title text key, color text)");
        query.exec("create table if not exists entry_tag (tag_id int primary key, entry_id int key)");
        query.exec("create table if not exists photo (id int primary key, title text, data blob)");
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

    for(int i = 1; i < 3; ++i) {
        query.exec("insert into journal (id, title) values (" + QString::number(i) + ", \"Test Journal " + QString::number(i) + "\")");
    }

    for(int i = 1; i < 1000; ++i) {
        query.exec("insert into entry (id,content) VALUES (" + QString::number(i) + ", \"Test Entry " + QString::number(i) + "\n\nTest content\")");
    }

    return true;
}
