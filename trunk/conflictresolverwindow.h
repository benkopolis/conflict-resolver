#ifndef CONFLICTRESOLVERWINDOW_H
#define CONFLICTRESOLVERWINDOW_H

#include <QMainWindow>
#include "contentmodel.h"
#include "owngui/conflictswidget.h"


namespace Ui {
    class ConflictResolverWindow;
}

class ConflictResolverWindow : public QMainWindow {
    Q_OBJECT
public:
    ConflictResolverWindow(QWidget *parent = 0);
    ConflictResolverWindow(ConflictsWidget* cw, ContentModel* model, QWidget *parent = 0);
    ~ConflictResolverWindow();



signals:


public slots:

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ConflictResolverWindow *ui;

    ContentModel* _model;

private slots:
};

#endif // CONFLICTRESOLVERWINDOW_H
