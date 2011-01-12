#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "contentmanagerwindow.h"
#include "filesset.h"
#include "filessetdelegate.h"
#include "tmxwindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QListView* files();
    QListView* filesChoosen();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    ContentManagerWindow* _cmw;
    TMXWindow* _tmxWindow;

private slots:
    void on__filesChoosen_doubleClicked(QModelIndex index);
    void on__files_doubleClicked(QModelIndex index);
    void on__files_clicked(QModelIndex index);
    void on__closeFile_clicked();
    void on__openFile_clicked();
    void on_startAnalyseing_clicked();

private:

    FilesSet* _filesOpened;
    QModelIndex _indexOfSelectedItem;
};

#endif // MAINWINDOW_H
