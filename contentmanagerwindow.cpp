#include <QStyledItemDelegate>
#include "contentmanagerwindow.h"
#include "ui_contentmanagerwindow.h"
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include "filtersdialog.h"
#include "inifile.h"
#include "glossaryextractordialog.h"
#include "fuzzyoptionsdialog.h"
#include "owngui/conflictswidget.h"

ContentManagerWindow::ContentManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContentManagerWindow)
{
    ui->setupUi(this);
    _crw = 0;
    setWindowTitle(QString("TMs & Glossaries Manager::Content Manager Window"));
}

ContentManagerWindow::ContentManagerWindow(bool fuzzySerach, const QStringList& files, ContentModel::ContentType type, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::ContentManagerWindow)
{
    ui->setupUi(this);
    ui->_filterContent->setEnabled(false);
    _content = new ContentModel(fuzzySerach, type);
    QObject::connect(_content, SIGNAL(conflictsCount(uint,uint)), this, SLOT(onConflictCount(uint,uint)));
    QObject::connect(_content, SIGNAL(totalRecords(uint)), this, SLOT(onTotalRecords(uint)));
    _crw = 0;
    setWindowTitle(QString("TMs & Glossaries Manager::Content Manager Window"));
    QObject::connect(this, SIGNAL(requestFiltration()), _content, SLOT(filterContent()));
    QObject::connect(this, SIGNAL(requestSaveDump(QString)), _content, SLOT(onRequestSaveDump(QString)));
    QObject::connect(this->_content, SIGNAL(corruptedCount(uint)), this, SLOT(onCorrupted(uint)));
    QObject::connect(_content, SIGNAL(fuzzyCount(uint)), this, SLOT(onFuzzyCount(uint)));
//    QObject::connect(this->ui->_resolveConflicts, SIGNAL(clicked()), this, SLOT(on__resolveConflicts_clicked()));
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

void ContentManagerWindow::onConflictCount(unsigned count, unsigned dup)
{
    QString text = QString::number(count, 10);
    text.append("(");
    text.append(QString::number(dup, 10));
    text.append(")");
    this->ui->_conflictsCount->setText(text);
    _conflicts = count;
}

void ContentManagerWindow::onTotalRecords(unsigned count)
{
    this->ui->_totalCount->setText(QString::number(count, 10));
}

void ContentManagerWindow::onCorrupted(unsigned count)
{
    this->ui->_corrupted->setText(QString::number(count, 10));
}

void ContentManagerWindow::onFuzzyCount(unsigned count)
{
    this->ui->_fuzzyConflictsCount->setText(QString::number(count, 10));
    _fuzzy = count;
}

void ContentManagerWindow::on__resolveConflicts_clicked()
{
    if(_conflicts != 0 || _fuzzy != 0)
    {
	ConflictsWidget* cw = new ConflictsWidget(this);
	cw->setupModel(this->_content->conflicts());
	_content->sort();
	_crw = new ConflictResolverWindow(cw, _content, this);
	int w, h, x, y;
	this->geometry().getRect(&x, &y, &w, &h);
	_crw->setGeometry(x+10, y+20, w, h+50);
	_crw->show();
    } else if(_content->dumpSize() == 0) {
	QMessageBox::critical(this, QString("Uwaga!"), QString("Nie ma zadnej tresci lub brak konfliktow!"));
//	this->close();
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
    QString save = QFileDialog::getSaveFileName(this, QString("Zapisz jako"), IniFile::instance()->lastPath(),
                                                "Text files (*.txt)");
    if(save.isEmpty())
        return;
    QFileInfo info(save);
    IniFile::instance()->setLastPath(info.path());
    if(this->_content->saveContent(save) == false)
        QMessageBox::critical(this, QString("Uwaga"), QString("Zapis siê nie powiód³."));
}

void ContentManagerWindow::on__browse_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, QString("Plik do zapisu zawartosci na pozniej"), IniFile::instance()->lastPath(),
                                                "Text files (*.txt)");
    if(file.isEmpty())
        return;
    QFileInfo info(file);
    IniFile::instance()->setLastPath(info.path());
    this->ui->_dumpFile->setText(file);
}

void ContentManagerWindow::on__saveDump_clicked()
{
    emit requestSaveDump(this->ui->_dumpFile->text().isEmpty() ? QString("dump.txt") : this->ui->_dumpFile->text());
}

void ContentManagerWindow::on__confront_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, QString("Plik do konfrontacji."), IniFile::instance()->lastPath(),
                                                "Text files (*.txt)");
    if(file.isEmpty())
        return;
    QFileInfo info(file);
    IniFile::instance()->setLastPath(info.path());
    this->_content->addFile(file);
}

void ContentManagerWindow::on__saveReversed_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, QString("Plik do zapisu odwroconej bazy."), IniFile::instance()->lastPath(),
                                                "Text files (*.txt)");
    if(file.isEmpty())
        return;
    QFileInfo info(file);
    IniFile::instance()->setLastPath(info.path());
    if(this->_content->saveReversedContent(file) == false)
	QMessageBox::critical(this, QString("Uwaga"), QString("Zapis siê nie powiód³."));
}

void ContentManagerWindow::on__saveGloss_clicked()
{
    GlossaryExtractorDialog* ged = new GlossaryExtractorDialog(this);
    //ged->setContent(*(this->_content->conflicts()));
    ged->show();
}

void ContentManagerWindow::on__chooseAntiDict_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, QString("Wybierz antys?ownik."), IniFile::instance()->lastPath(),
                                                "Text files (*.txt)");
    if(file.isEmpty())
        return;
    QFileInfo info(file);
    IniFile::instance()->setLastPath(info.path());
    this->ui->_antiDict->setText(file);
}

void ContentManagerWindow::on__checkDict_clicked()
{
    QString dict = this->ui->_antiDict->text();
    QString dut = QFileDialog::getSaveFileName(this, QString("Wybierz lokalizacje pliku duties.txt"), QString("duties.txt"));
    this->_content->checkWithAntiDict(dict, this->ui->_cSource->isChecked(), this->ui->_cTarget->isChecked(), dut);

}

void ContentManagerWindow::on__find_clicked()
{
    _content->findAgain();
}

void ContentManagerWindow::on__options_clicked()
{
    FuzzyOptionsDialog* fod = new FuzzyOptionsDialog(this);
    fod->setModal(true);
    fod->show();
}
