#ifndef CONFLICTRESOLVERWINDOW_H
#define CONFLICTRESOLVERWINDOW_H

#include <QMainWindow>
#include "contentmodel.h"
#include "contentdelegate.h"



namespace Ui {
    class ConflictResolverWindow;
}

class ConflictResolverWindow : public QMainWindow {
    Q_OBJECT
public:
    ConflictResolverWindow(QWidget *parent = 0);
    ConflictResolverWindow(ContentModel* model, QWidget *parent = 0);
    ~ConflictResolverWindow();

    QListView* conflictsView();

signals:

    void resized(const QRect& rect);
    void workEnded();
    void prev();
    void next();
    void requestBegin();
    void defClicked(const QModelIndex& index);
    void requestRowDeletion(const QModelIndex& index);
    void requestAllDeletion();
    void requestDump();
    void requestDuplicatedDeletion();

public slots:

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ConflictResolverWindow *ui;

    ContentModel* _model;
    ContentDelegate* _delegate;

private slots:
    void on_ConflictResolverWindow_destroyed();
    void on_close_clicked();
    void on__putToDump_clicked();
    void on_deleteRow_clicked();
    void on_deleteAll_clicked();
    void on_putToDump_clicked();
    void on_removeDup_clicked();
    void on_editRow_clicked();
    void on_prev_clicked();
    void on_next_clicked();
};

#endif // CONFLICTRESOLVERWINDOW_H
