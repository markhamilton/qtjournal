#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localapi.h"

#include <QDebug>
#include <QSqlQueryModel>
#include "journalmodel.h"
#include "entrymodel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupModels();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupModels()
{
    // set up JOURNAL model + view
    JournalModel *jm = new JournalModel(&l_api);
    ui->lstJournals->setModel(jm);
    ui->lstJournals->setModelColumn(1);

    connect(ui->lstJournals->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(journalSelectionChanged(QItemSelection)));

    // set up ENTRY model + view
    EntryModel *em = new EntryModel(&l_api);
    ui->lstEntries->setModel(em);
    ui->lstEntries->setModelColumn(1);

    connect(ui->lstEntries->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(entrySelectionChanged(QItemSelection)));

    // set default selection (skip over "all journals")
    // there must always be at least one journal
    ui->lstJournals->setCurrentIndex(ui->lstJournals->model()->index(1,0));
}

void MainWindow::journalSelectionChanged(const QItemSelection& selection)
{
    if( selection.indexes().isEmpty() ) {
        qDebug() << "Journal: Cleared selection";
        // Set default selection
        ui->lstJournals->setCurrentIndex(ui->lstJournals->model()->index(1,0));
    } else {
        qDebug() << "Journal: Selection changed";
        // TODO: Update entries list with new filter
    }
}


void MainWindow::entrySelectionChanged(const QItemSelection& selection)
{
    if( selection.indexes().isEmpty() ) {
        qDebug() << "Entry: Cleared selection";
        // Shouldn't get to this point
    } else {
        qDebug() << "Entry: Selection changed";
        // TODO: Update editor with content from selected entry.
        // TODO: If multiple entries are selected, show a blurb from each one.
    }
}
