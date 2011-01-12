#include <QFileDialog>
#include <QItemSelection>
#include <QMessageBox>
#include <QScrollBar>
#include <QTextStream>
#include <QFileInfo>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filessetdelegate.h"
#include "inifile.h"
#include "commons/error.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->_tm->click();
    ui->_files->setModel((QAbstractItemModel*)(new FilesSet(this)));
    _filesOpened = (FilesSet*)ui->_files->model();
    ui->_files->setItemDelegate(new FilesSetDelegate(this));
//
//    QObject::connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(on__openFile_clicked()));
//    QObject::connect(ui->actionCloseFile, SIGNAL(triggered()), this, SLOT(on__closeFile_clicked()));
    this->ui->_files->horizontalScrollBar()->setTracking(true);
    this->ui->_files->verticalScrollBar()->setTracking(true);
    QObject::connect(this->ui->_files->horizontalScrollBar(), SIGNAL(valueChanged(int)), (FilesSetDelegate*)ui->_files->itemDelegate(), SLOT(onHorizontalOffset(int)));
    QObject::connect(this->ui->_files->verticalScrollBar(), SIGNAL(valueChanged(int)),(FilesSetDelegate*)ui->_files->itemDelegate(), SLOT(onVerticalOffset(int)));
    _cmw = 0;
    _tmxWindow = 0;
    setWindowTitle(QString("TMs & Glossaries Manager::Main Window"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


QListView* MainWindow::files() {
    return this->ui->_files;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_startAnalyseing_clicked()
{
    Error err;
    int w, h, x, y;
    this->geometry().getRect(&x, &y, &w, &h);
    if(_filesOpened->filesList().size() == 0) {
	QMessageBox::critical(this, QString(tr("Uwaga")), QString(tr("Nie wybrano plików do analizy.")));
	return;
    }
    if(ui->_tmx->isChecked())
    {
	if(_tmxWindow != 0) {
	    delete _tmxWindow;
	    _tmxWindow = 0;
	}
	_tmxWindow = new TMXWindow(this);
	for(QStringList::const_iterator ii = _filesOpened->filesList().begin(); ii != _filesOpened->filesList().end(); ++ii)
	{
	    if((err = _tmxWindow->addFile(*ii)) == false)
	    {
		QString errmsg; // ("Nie uda³o siê otworzyæ pliku. ");
		QTextStream stream(&errmsg);
		stream << "Nie uda³o siê otworzyæ pliku " << *ii << endl;
		stream << "Komunikat o bledzie: " << err.errorMessage() << endl;
		QJson::Serializer s;
		if(err.errorAttribs().size()!=0)
		    stream << "Szczegoly: " << s.serialize(err.errorAttribs()) << endl;
		else
		    stream << "Szczegoly: " << "Brak szczegolow" << endl;
		QMessageBox::critical(this, QString("Otwieranie pliku"), errmsg);
	    }
	}
	_tmxWindow->setGeometry(x+10, y+20, w, h+50);
	_tmxWindow->show();
    }
    else
    {
	if(_cmw != 0) {
	    delete _cmw;
	    _cmw = 0;
	}
	if(ui->_tm->isChecked()) {
	    _cmw = new ContentManagerWindow(this->ui->_fuzzySearch->isChecked(), _filesOpened->filesList(), ContentModel::TM, this);
	}
	else if(ui->_gloss->isChecked()) {
	    _cmw = new ContentManagerWindow(this->ui->_fuzzySearch->isChecked(), _filesOpened->filesList(), ContentModel::GLOSSARY, this);
	}
	for(QStringList::const_iterator ii = _filesOpened->filesList().begin(); ii != _filesOpened->filesList().end(); ++ii) {
	    //QMessageBox::about(this, QString("Test"), QString("Dodano plik"));
	    if((err = _cmw->content()->addFile(*ii)) == false)
	    {
		QString errmsg; // ("Nie uda³o siê otworzyæ pliku. ");
		QTextStream stream(&errmsg);
		stream << "Nie uda³o siê otworzyæ pliku " << *ii << endl;
		stream << "Komunikat o bledzie: " << err.errorMessage() << endl;
		QJson::Serializer s;
		if(err.errorAttribs().size()!=0)
		    stream << "Szczegoly: " << s.serialize(err.errorAttribs()) << endl;
		else
		    stream << "Szczegoly: " << "Brak szczegolow" << endl;
		QMessageBox::critical(this, QString("Otwieranie pliku"), errmsg);
	    }
	}
	_cmw->setGeometry(x+10, y+20, w, h+50);
	_cmw->show();
    }
}

void MainWindow::on__openFile_clicked()
{
    if(ui->_tmx->isChecked())
    {
	QString filter("XML files (*.tmx)");
	QStringList files(QFileDialog::getOpenFileNames(this, QString(tr("Choose files.")), IniFile::instance()->lastPath(),
							filter));
	if(files.isEmpty() == false) {
	    QString example = files.at(0);
	    QFileInfo info(example);
	    IniFile::instance()->setLastPath(info.path());
	}
	for(QStringList::iterator ii = files.begin(); ii != files.end(); ++ii)
	    _filesOpened->setData(QModelIndex(), QVariant(*ii));
    }
    else
    {
	QString filter("Text files (*.txt)");
	QStringList files(QFileDialog::getOpenFileNames(this, QString(tr("Choose files.")), IniFile::instance()->lastPath(),
							filter));
	if(files.isEmpty() == false) {
	    QString example = files.at(0);
	    QFileInfo info(example);
	    IniFile::instance()->setLastPath(info.path());
	}
	for(QStringList::iterator ii = files.begin(); ii != files.end(); ++ii)
	    _filesOpened->setData(QModelIndex(), QVariant(*ii));
    }
}

void MainWindow::on__closeFile_clicked()
{
    if(_indexOfSelectedItem != QModelIndex()) {
	_indexOfSelectedItem = _filesOpened->deleteItem(_indexOfSelectedItem);
    }
}

void MainWindow::on__files_clicked(QModelIndex index)
{
    if(index != _indexOfSelectedItem) {
	FilesSetDelegate* del = (FilesSetDelegate*)ui->_files->itemDelegate(index);
	del->setSelected(index);
	_filesOpened->updateOnCommand(index);
	_indexOfSelectedItem = index;
    }
}

void MainWindow::on__files_doubleClicked(QModelIndex index)
{/*
    QString s = qvariant_cast<QString>(index.data());
    if(index != QModelIndex()) {
	if(index == _indexOfSelectedItem)
	index = _filesOpened->deleteItem(index);
    }
    _filesChoosen->setData(QModelIndex(), QVariant(s));*/
}

void MainWindow::on__filesChoosen_doubleClicked(QModelIndex index)
{/*
    QString s = qvariant_cast<QString>(index.data());
    if(index != QModelIndex()) {
	index = _filesChoosen->deleteItem(index);
    }
    _filesOpened->setData(QModelIndex(), QVariant(s));*/
}
