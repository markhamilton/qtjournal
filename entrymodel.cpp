#include "entrymodel.h"

#include <QSqlQuery>


EntryModel::EntryModel(LocalApi *api)
{
    l_api = api;
}

int EntryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    QSqlQuery q;
    q.exec("select count(*) from entry");

    if(q.next()) return q.value(0).toInt();

    return 0;
}

int EntryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant EntryModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole)
    {
        QSqlQuery q;
        q.exec("select id,trim(replace(content, ltrim(content, replace(content, '\n', '' ) ), '')),published from entry limit " + QString::number(row) + ",1");
        if(q.next()) return QString(q.value(col).toString());
    }
    return QVariant();
}
