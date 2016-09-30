#ifndef ENTRYMODEL_H
#define ENTRYMODEL_H

#include <QObject>
#include <qabstractitemmodel.h>

class EntryModel : public QAbstractListModel
{
    Q_OBJECT


public:
    EntryModel();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // ENTRYMODEL_H
