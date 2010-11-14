#include <QDebug>
#include "conflictresolverwindow.h"
#include "ui_conflictresolverwindow.h"
#include "owngui/contentwidget.h"

ConflictResolverWindow::ConflictResolverWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConflictResolverWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("TMs & Glossaries Manager::Conflict Resolver Window"));
}

ConflictResolverWindow::ConflictResolverWindow(ContentModel* model, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::ConflictResolverWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("TMs & Glossaries Manager::Conflict Resolver Window"));
    ContentWidget* wdg = new ContentWidget(this);
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

