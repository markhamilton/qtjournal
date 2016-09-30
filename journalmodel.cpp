#include "journalmodel.h"

#include <QDebug>
#include <QSqlQuery>

JournalModel::JournalModel(LocalApi *api)
{
    l_api = api;

}

int JournalModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    QSqlQuery q;
    q.exec("select count(*) from journal");

    if(q.next()) return q.value(0).toInt();

    return 0;
}

QVariant JournalModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole)
    {
        qDebug() << QString("row %1, col%2, role %3")
                    .arg(row).arg(col).arg(role);

        QSqlQuery q;
//        q.exec("select * from journal where id=" + QString::number(row));
        q.exec("select * from journal limit " + QString::number(row) + ",1");
        if(q.next()) {
            qDebug() << "select * from journal limit " + QString::number(row) + ",1";
            qDebug() << "id:" + q.value(0).toString();
            return QString(q.value(1).toString());
        }
    }
    return QVariant();
}
