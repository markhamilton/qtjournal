// This is a blocking, synchronous API; I'm not worried about performance
// It's a journaling app, and it's using a local DB

#ifndef LOCALAPI_H
#define LOCALAPI_H

#include <QString>
#include <QDateTime>
#include <QHash>
#include <QColor>

#include <QSqlDatabase>

class LocalApi
{
public:
    LocalApi();

    qint32 newJournal(QString name, QColor color);

    qint32 newEntry(qint32 journal_id, QString content = "", QDateTime datetime = QDateTime::currentDateTime());
    bool delEntry(qint32 entry_id);
    bool updateEntryContent(qint32 entry_id, QString text = "");
    bool updateEntryDate(qint32 entry_id, QDateTime datetime);
    bool updateEntryMeta(qint32 entry_id, QHash<QString, QString> kvp);

    qint32 newTag(QString title, QColor color);
    bool delTag(qint32 tag_id);
    bool updateTagTitle(qint32 tag_id, QString title);
    bool updateTagColor(qint32 tag_id, QColor color);

private:
    bool createConnection();
    bool setupTables();
    bool demoData();

    QSqlDatabase db;

};

#endif // LOCALAPI_H
