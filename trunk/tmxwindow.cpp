#include "tmxwindow.h"
#include "ui_tmxwindow.h"
#include <QStringList>
#include <QFileDialog>
#include <QTextStream>

TMXWindow::TMXWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TMXWindow)
{
    ui->setupUi(this);
}

TMXWindow::~TMXWindow()
{
    delete ui;
}

void TMXWindow::changeEvent(QEvent *e)
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

Error TMXWindow::addFile(QString filename)
{
    TMXFile* tmx = new TMXFile(this);
    QFile file(filename);
    Error res;
    QString newtxt = ui->_status->toPlainText();
    QTextStream txt(&newtxt);
    res.addAttribute("file_name", filename);
    //qDebug() << "adding new file!" << endl;
    if(file.open(QIODevice::ReadWrite | QIODevice::Text) == false) {
	//qDebug() << "Nie udalo sie otworzyc pliku" << endl;
	res.setErrorMessage("Nie udalo sie otworzyc pliku.");
	txt << "Nie udalo sie otworzyc pliku: " << filename << endl;
	return res;
    }
    res = tmx->processWithTabs(file);
    if(res.isError() == true)
	return res;
    _files.append(tmx);
    txt << "Dodano z sukcesem plik: " << filename << endl;
    ui->_status->setPlainText(newtxt);
    return res;
}

bool TMXWindow::saveFiles(QString base)
{
    foreach(TMXFile* f, this->_files)
    {
	bool r = f->saveContent(base);
	if(r == false)
	    return false;
    }
    return true;
}



void TMXWindow::on__chooseDir_clicked()
{
    QString save_file = QFileDialog::getSaveFileName(this, QString(tr("Choose file.")), IniFile::instance()->lastPath(),
						    "Text files (*.txt)");
    ui->_dir->setText(save_file);
}

void TMXWindow::on__save_clicked()
{
    this->saveFiles(ui->_dir->text());
}
