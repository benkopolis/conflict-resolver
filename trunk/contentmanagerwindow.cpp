#include <QStyledItemDelegate>
#include "contentmanagerwindow.h"
#include "ui_contentmanagerwindow.h"
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include "filtersdialog.h"
#include "inifile.h"
#include "glossaryextractordialog.h"

ContentManagerWindow::ContentManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContentManagerWindow)
{
    ui->setupUi(this);
    _crw = 0;
    setWindowTitle(QString("TMs & Glossaries Manager::Content Manager Window"));
}

ContentManagerWindow::ContentManagerWindow(const QStringList& files, ContentModel::ContentType type, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::ContentManagerWindow)
{
    ui->setupUi(this);
    ui->_filterContent->setEnabled(false);
    _content = new ContentModel(type);
    QObject::connect(_content, SIGNAL(conflictsCount(uint)), this, SLOT(onConflictCount(uint)));
    QObject::connect(_content, SIGNAL(totalRecords(uint)), this, SLOT(onTotalRecords(uint)));
    _crw = 0;
    setWindowTitle(QString("TMs & Glossaries Manager::Content Manager Window"));
    QObject::connect(this, SIGNAL(requestFiltration()), _content, SLOT(filterContent()));
    QObject::connect(this, SIGNAL(requestSaveDump(QString)), _content, SLOT(onRequestSaveDump(QString)));
    QObject::connect(this->_content, SIGNAL(corruptedCount(uint)), this, SLOT(onCorrupted(uint)));
}

void ContentManagerWindow::setRH(int row, int height) {
    //
}

ContentManagerWindow::~ContentManagerWindow()
{
    delete ui;
}

void ContentManagerWindow::changeEvent(QEvent *e)
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

void ContentManagerWindow::onConflictCount(unsigned count) {
    this->ui->_conflictsCount->setText(QString::number(count, 10));
}

void ContentManagerWindow::onTotalRecords(unsigned count) {
    this->ui->_totalCount->setText(QString::number(count, 10));
}

void ContentManagerWindow::onCorrupted(unsigned count) {
    this->ui->_corrupted->setText(QString::number(count, 10));
}

void ContentManagerWindow::on__resolveConflicts_clicked()
{
    if(_content->contentSize() != 0 ) {
	_content->sort();
	_crw = new ConflictResolverWindow(_content, this);
	int w, h, x, y;
	this->geometry().getRect(&x, &y, &w, &h);
	_crw->setGeometry(x+10, y+20, w, h+50);
	_crw->show();
    } else if(_content->dumpSize() == 0) {
	QMessageBox::critical(this, QString("Uwaga!"), QString("Nie ma zadnej tresci!"));
	this->close();
    } else {
	QMessageBox::critical(this, QString("Uwaga!"), QString("Rekordy odlozone na pozniej zostana zapisane.\n"
							       "Innej tresci nie ma - okno zostanie zamkniete"));
	emit requestSaveDump(this->ui->_dumpFile->text().isEmpty() ? QString("dump.txt") : this->ui->_dumpFile->text() );
	this->close();
    }
}

void ContentManagerWindow::on__filterContent_clicked()
{
//    FiltersDialog* fd = new FiltersDialog( this->_content, this);
//    int w, h, x, y;
//    this->geometry().getRect(&x, &y, &w, &h);
//    fd->setGeometry(x+10, y+20, w/2, h/2);
//    fd->show();
//    if(fd->isOkClicked()) {
//	_content->setDateTime(fd->dateTime());
//	_content->setAscending(fd->isAscending());
//    }
//    emit requestFiltration();
}

void ContentManagerWindow::on__saveContent_clicked()
{
    QString save = QFileDialog::getSaveFileName(this, QString("Zapisz jako"), IniFile::instance()->m_dir);
    IniFile::instance()->m_dir = save.mid(0, save.lastIndexOf(QString("\\"), 0, Qt::CaseInsensitive));
    if(this->_content->saveContent(save) == false)
	QMessageBox::critical(this, QString("Uwaga"), QString("Zapis siê nie powiód³."));
}

void ContentManagerWindow::on__browse_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, QString("Plik do zapisu zawartosci na pozniej"), IniFile::instance()->m_dir);
    IniFile::instance()->m_dir = file.mid(0, file.lastIndexOf(QString("\\"), 0, Qt::CaseInsensitive));
    this->ui->_dumpFile->setText(file);
}

void ContentManagerWindow::on__saveDump_clicked()
{
    emit requestSaveDump(this->ui->_dumpFile->text().isEmpty() ? QString("dump.txt") : this->ui->_dumpFile->text());
}

void ContentManagerWindow::on__confront_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, QString("Plik do konfrontacji."), IniFile::instance()->m_dir);
    IniFile::instance()->m_dir = file.mid(0, file.lastIndexOf(QString("\\"), 0, Qt::CaseInsensitive));
    this->_content->addFile(file);
}

void ContentManagerWindow::on__saveReversed_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, QString("Plik do zapisu odwroconej bazy."), IniFile::instance()->m_dir);
    IniFile::instance()->m_dir = file.mid(0, file.lastIndexOf(QString("\\"), 0, Qt::CaseInsensitive));
    if(this->_content->saveReversedContent(file) == false)
	QMessageBox::critical(this, QString("Uwaga"), QString("Zapis siê nie powiód³."));
}

void ContentManagerWindow::on__saveGloss_clicked()
{
    GlossaryExtractorDialog* ged = new GlossaryExtractorDialog(this);
    //ged->setContent(*(this->_content->conflicts()));
    ged->show();
}
