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
    if(ui->lstJournals->selectionModel()->selectedRows().count() == 0) {
        // Set first journal -- can't deselect all journals
        ui->lstJournals->setCurrentIndex(ui->lstJournals->model()->index(1,0));
    } else {
        qDebug() << "Journal: Selection changed";
        // TODO: Update entries list with new filter
    }
}


void MainWindow::entrySelectionChanged(const QItemSelection& selection)
{
    Q_UNUSED(selection);

    qDebug() << "Entry: Selection changed";

    int sel_count = ui->lstEntries->selectionModel()->selectedRows().count();
    qDebug() << sel_count;

    if(sel_count == 0)
    {
        // TODO: show no entries selected/default screen
    }
    else if(sel_count == 1)
    {
        ui->txtEntry->setText(
                    ui->lstEntries->selectionModel()->selectedRows(1).first().data(Qt::EditRole).toString() );
    }
    else
    {
        // TODO: If multiple entries are selected, show a blurb from each one.
        qDebug() << "Multiple selections: Feature coming soon." << sel_count;
    }
}
