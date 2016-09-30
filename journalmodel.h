#ifndef JOURNALMODEL_H
#define JOURNALMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "localapi.h"

class JournalModel : public QAbstractListModel
{
    Q_OBJECT

public:
    JournalModel(LocalApi *api);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    LocalApi *l_api;
};

#endif // JOURNALMODEL_H
