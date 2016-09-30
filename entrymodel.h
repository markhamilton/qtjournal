#ifndef ENTRYMODEL_H
#define ENTRYMODEL_H

#include <QObject>
#include <qabstractitemmodel.h>

#include "localapi.h"

class EntryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    EntryModel(LocalApi *api);

public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    LocalApi *l_api;
};

#endif // ENTRYMODEL_H
