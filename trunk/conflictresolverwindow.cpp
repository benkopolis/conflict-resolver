#include <QDebug>
#include "conflictresolverwindow.h"
#include "ui_conflictresolverwindow.h"


ConflictResolverWindow::ConflictResolverWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConflictResolverWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("TMs & Glossaries Manager::Conflict Resolver Window"));
    _conflictsWidget = 0;
    if(parent!=0)
	this->setMaximumSize(parent->maximumSize());
}

ConflictResolverWindow::ConflictResolverWindow(ConflictsWidget* cw, ContentModel* model, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::ConflictResolverWindow)
{
    ui->setupUi(this);
    ui->centralwidget->layout()->addWidget(cw);
    setWindowTitle(QString("TMs & Glossaries Manager::Conflict Resolver Window"));
//    wdg->setupModel(model->conflicts()->value());
    connect(ui->actionNext, SIGNAL(triggered()), cw, SLOT(onNext()));
    connect(ui->actionPrevious, SIGNAL(triggered()), cw, SLOT(onPrev()));
    connect(ui->actionZako_cz, SIGNAL(triggered()), this, SLOT(close()));
    connect(cw, SIGNAL(nextStatus(bool)), this->ui->actionNext, SLOT(setEnabled(bool)));
    connect(cw, SIGNAL(prevStatus(bool)), this->ui->actionNext, SLOT(setEnabled(bool)));
    _conflictsWidget = cw;
    ui->actionNext->setEnabled(cw->nextStatus());
    ui->actionPrevious->setEnabled(cw->prevStatus());
    if(parent!=0)
	this->setMaximumSize(parent->maximumSize());
}

ConflictResolverWindow::~ConflictResolverWindow()
{
    delete ui;
    delete _conflictsWidget;
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

