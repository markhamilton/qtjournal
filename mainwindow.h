#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "localapi.h"

#include <QMainWindow>
#include <QItemSelection>

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

private:
    Ui::MainWindow *ui;

    LocalApi l_api;
};

#endif // MAINWINDOW_H
