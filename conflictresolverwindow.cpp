#include <QDebug>
#include "conflictresolverwindow.h"
#include "ui_conflictresolverwindow.h"


ConflictResolverWindow::ConflictResolverWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConflictResolverWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("TMs & Glossaries Manager::Conflict Resolver Window"));
}

ConflictResolverWindow::ConflictResolverWindow(ConflictsWidget* cw, ContentModel* model, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::ConflictResolverWindow)
{
    ui->setupUi(this);
    ui->centralwidget->layout()->addWidget(cw);
    setWindowTitle(QString("TMs & Glossaries Manager::Conflict Resolver Window"));
//    wdg->setupModel(model->conflicts()->value());
}

ConflictResolverWindow::~ConflictResolverWindow()
{
    delete ui;
}


void ConflictResolverWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    case QEvent::Resize:

	break;
    default:
        break;
    }
}

