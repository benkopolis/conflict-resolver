#include <QDebug>
#include "conflictresolverwindow.h"
#include "ui_conflictresolverwindow.h"
#include "editdialog.h"

ConflictResolverWindow::ConflictResolverWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConflictResolverWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("TMs & Glossaries Manager::Conflict Resolver Window"));
    _model = 0;
    _delegate = 0;
}

ConflictResolverWindow::ConflictResolverWindow(ContentModel* model, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::ConflictResolverWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("TMs & Glossaries Manager::Conflict Resolver Window"));
    _model = model;
    _delegate = new ContentDelegate(this);
    this->ui->removeDup->setEnabled(false);
    this->ui->_conflictsList->setModel(_model);
    this->ui->_conflictsList->setItemDelegate(_delegate);
    QObject::connect(this, SIGNAL(next()), this->_model, SLOT(onNext()));
    QObject::connect(this, SIGNAL(prev()), this->_model, SLOT(onPrev()));
    QObject::connect(this->ui->_conflictsList, SIGNAL(clicked(QModelIndex)), this->_delegate, SLOT(setSelected(QModelIndex)));
    QObject::connect(this->ui->_conflictsList, SIGNAL(clicked(QModelIndex)), this->_model, SLOT(selectOnClick(QModelIndex)));
    QObject::connect(this, SIGNAL(defClicked(QModelIndex)), this->_model, SLOT(selectOnClick(QModelIndex)));
    QObject::connect(this, SIGNAL(defClicked(QModelIndex)), this->_delegate, SLOT(setSelected(QModelIndex)));
    QObject::connect(this->ui->actionNext, SIGNAL(triggered()), this, SLOT(on_next_clicked()));
    QObject::connect(this->ui->actionPrevious, SIGNAL(triggered()), this, SLOT(on_prev_clicked()));
    QObject::connect(this, SIGNAL(requestBegin()), _model, SLOT(forceBegin()));
    QObject::connect(this, SIGNAL(requestAllDeletion()), _model, SLOT(onRequestAllDeletion()));
    QObject::connect(this, SIGNAL(requestRowDeletion(QModelIndex)), _model, SLOT(onRequestRowDeletion(QModelIndex)));
    QObject::connect(this, SIGNAL(requestDump()), _model, SLOT(onRequestDump()));
    QObject::connect(this, SIGNAL(requestDuplicatedDeletion()), _model, SLOT(onRequestDuplicatedDeletion()));
    QObject::connect(this, SIGNAL(workEnded()), this->_model, SLOT(unsort()));
//    QObject::connect(this, SIGNAL(resized(QRect)), this->_model, SLOT(onRequestItemToCountRects(QRect)));
    emit requestBegin();
//    emit resized(this->ui->_conflictsList->geometry());
}

ConflictResolverWindow::~ConflictResolverWindow()
{
    delete ui;
}

QListView* ConflictResolverWindow::conflictsView() {
    return this->ui->_conflictsList;
}

void ConflictResolverWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    case QEvent::Resize:
	qDebug() << "w: " << this->ui->_conflictsList->geometry().width() << "h: " << this->ui->_conflictsList->geometry().height() << endl;
	emit resized(this->ui->_conflictsList->geometry());
	break;
    default:
        break;
    }
}

void ConflictResolverWindow::on_next_clicked()
{
    emit defClicked(QModelIndex());
    emit next();
}

void ConflictResolverWindow::on_prev_clicked()
{
    emit defClicked(QModelIndex());
    emit prev();
}

void ConflictResolverWindow::on_editRow_clicked()
{
    if(_model->selected() != QModelIndex()) {
	EditDialog *ed = new EditDialog(_model->type(), _model->realData(_model->selected()));
	ed->exec();
    }
}

void ConflictResolverWindow::on_removeDup_clicked()
{
    emit requestDuplicatedDeletion();
}

void ConflictResolverWindow::on_putToDump_clicked()
{
    emit requestDump();
}

void ConflictResolverWindow::on_deleteAll_clicked()
{
    emit requestAllDeletion();
}

void ConflictResolverWindow::on_deleteRow_clicked()
{
    emit requestRowDeletion(_model->selected());
    emit defClicked(QModelIndex());
}

void ConflictResolverWindow::on__putToDump_clicked()
{
    emit requestDump();
}

void ConflictResolverWindow::on_close_clicked()
{
    emit workEnded();
    this->close();
}

void ConflictResolverWindow::on_ConflictResolverWindow_destroyed()
{
    emit workEnded();
}
