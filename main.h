#ifndef MAIN_H
#define MAIN_H

#include "localapi.h"

#include <QMainWindow>
#include <QItemSelection>

#include <QHBoxLayout>
#include <QListView>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setupModels();

public slots:
    void journalSelectionChanged(const QItemSelection& selection);
    void entrySelectionChanged(const QItemSelection& selection);
//    void entryTextChanged(const )

private:

    // qt controls
    QHBoxLayout *qhbThreePanel;
    QListView *lstJournals;
    QListView *lstEntries;
    QTextEdit *txtEntry;


    LocalApi l_api;
};

#endif // MAIN_H
