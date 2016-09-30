#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localapi.h"

#include <QSqlQueryModel>
#include "journalmodel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    JournalModel *jm = new JournalModel(&l_api);
    ui->lstJournals->setModel(jm);
    ui->lstJournals->setModelColumn(1);

//    ui->lstEntries->setModel(em);
}

MainWindow::~MainWindow()
{
    delete ui;
}
