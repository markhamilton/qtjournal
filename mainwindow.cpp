#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localapi.h"

#include <QSqlQueryModel>
#include "journalmodel.h"
#include "entrymodel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    JournalModel *jm = new JournalModel(&l_api);
    ui->lstJournals->setModel(jm);
    ui->lstJournals->setModelColumn(1);

    EntryModel *em = new EntryModel(&l_api);
    ui->lstEntries->setModel(em);
    ui->lstEntries->setModelColumn(1);

//    ui->lstEntries->setModel(em);
}

MainWindow::~MainWindow()
{
    delete ui;
}
