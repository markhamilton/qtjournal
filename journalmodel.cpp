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

    // +1 so I can prepent "All Journals" to beginning of list.
    if(q.next()) return q.value(0).toInt() + 1;

    return 0;
}

int JournalModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant JournalModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole)
    {
//        qDebug() << QString("row %1, col%2, role %3")
//                    .arg(row).arg(col).arg(role);

        // first row is always "All Journals"
        if(row == 0)
        {
            if(col == 0) return -1;
            return QString("All Journals");
        }
        else
        {
            QSqlQuery q;
            q.exec("select id,title,color from journal limit " + QString::number(row - 1) + ",1");
            if(q.next()) {
//                qDebug() << "select * from journal limit " + QString::number(row) + ",1";
//                qDebug() << "id:" + q.value(0).toString();
                return QString(q.value(col).toString());
            }
        }

    }
    return QVariant();
}
