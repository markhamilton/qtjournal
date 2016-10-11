#include "main.h"
#include <QApplication>

#include "ui_mainwindow.h"
#include "localapi.h"

#include <QDebug>
#include <QSqlQueryModel>
#include "journalmodel.h"
#include "entrymodel.h"

#include <QToolBar>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->resize(640, 400);

    // formality
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    qhbThreePanel = new QHBoxLayout(central);


    // set up controls
    lstJournals = new QListView(this);
    qhbThreePanel->addWidget(lstJournals);
    lstJournals->setFrameShape(QFrame::NoFrame);
    lstJournals->setSelectionBehavior(QAbstractItemView::SelectRows);
    lstJournals->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    lstEntries = new QListView(this);
    qhbThreePanel->addWidget(lstEntries);
    lstEntries->setFrameShape(QFrame::NoFrame);
    lstEntries->setDragEnabled(true);
    lstEntries->setDragDropMode(QAbstractItemView::DragDrop);
    lstEntries->setAlternatingRowColors(true);
    lstEntries->setSelectionMode(QAbstractItemView::ExtendedSelection);
    lstEntries->setSelectionBehavior(QAbstractItemView::SelectRows);
    lstEntries->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    lstEntries->setLayoutMode(QListView::Batched);

    txtEntry = new QTextEdit(this);
    qhbThreePanel->addWidget(txtEntry);
    txtEntry->setFrameShape(QFrame::NoFrame);

    QToolBar *tbar = new QToolBar(this);
    tbar->addWidget(new QPushButton("New Entry"));
    addToolBar(tbar);
    setUnifiedTitleAndToolBarOnMac(true);

    setupModels();
}

MainWindow::~MainWindow()
{
}


void MainWindow::setupModels()
{
    // set up JOURNAL model + view
    JournalModel *jm = new JournalModel(&l_api);
    lstJournals->setModel(jm);
    lstJournals->setModelColumn(1);

    connect(lstJournals->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(journalSelectionChanged(QItemSelection)));

    // set up ENTRY model + view
    EntryModel *em = new EntryModel(&l_api);
    lstEntries->setModel(em);
    lstEntries->setModelColumn(1);

    connect(lstEntries->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(entrySelectionChanged(QItemSelection)));

    // set default selection (skip over "all journals")
    // there must always be at least one journal
    lstJournals->setCurrentIndex(lstJournals->model()->index(1,0));
}

void MainWindow::journalSelectionChanged(const QItemSelection& selection)
{
    if(lstJournals->selectionModel()->selectedRows().count() == 0) {
        // Set first journal -- can't deselect all journals
        lstJournals->setCurrentIndex(lstJournals->model()->index(1,0));
    } else {
        qDebug() << "Journal: Selection changed";
        // TODO: Update entries list with new filter
    }
}


void MainWindow::entrySelectionChanged(const QItemSelection& selection)
{
    Q_UNUSED(selection);

    qDebug() << "Entry: Selection changed";

    int sel_count = lstEntries->selectionModel()->selectedRows().count();
    qDebug() << sel_count;

    if(sel_count == 0)
    {
        // TODO: show no entries selected/default screen
    }
    else if(sel_count == 1)
    {
        txtEntry->setText(
                    lstEntries->selectionModel()->selectedRows(1).first().data(Qt::EditRole).toString() );
    }
    else
    {
        // TODO: If multiple entries are selected, show a blurb from each one.
        qDebug() << "Multiple selections: Feature coming soon." << sel_count;
    }
}

