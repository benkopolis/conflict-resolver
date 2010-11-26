#include "glossaryextractordialog.h"
#include "ui_glossaryextractordialog.h"
#include <QFileDialog>
#include "inifile.h"
#include "tmsaver.h"
#include "contentmodel.h"

GlossaryExtractorDialog::GlossaryExtractorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlossaryExtractorDialog)
{
    ui->setupUi(this);
    _ok = false;
    _maxWordCount = 0;
    _maxOccurence = 0;
    _minOccurence = 0;
    _minWordCount = 0;
}

GlossaryExtractorDialog::~GlossaryExtractorDialog()
{
    delete ui;
}

void GlossaryExtractorDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void GlossaryExtractorDialog::on__save_clicked()
{
    QString f = QFileDialog::getSaveFileName(this, QString("Plik do zapisu:"), IniFile::instance()->lastPath(),
                                             "Text files (*.txt);;XML files (*.tmx)");
    if(f.isEmpty())
        return;
    QFileInfo info(f);
    IniFile::instance()->setLastPath(info.path());
    TMSaver tms;
    TMHeader tmh;
    tms.saveContent(f, tmh, _found, (unsigned)_found.size());

}

void GlossaryExtractorDialog::on__find_clicked()
{
    QRegExp rexp(QString("\\s"));
    foreach(FuzzyStrings fs, this->_content.keys()) {
	unsigned wc = fs.base().count(rexp) + 1;
	if(wc <= this->_minWordCount) {
	    QStringList sl = fs.base().split(rexp);
	    for(unsigned m=0; m < fs.base().length() - wc; ++m) {
		QString pattern;
		for(unsigned n=0; n<wc; ++n) {
		    pattern = pattern.append(sl.at(m+n));
		    pattern = pattern.append(" ");
		}
		unsigned occ = 0;
		foreach(FuzzyStrings crawler, this->_content.keys()) {
		    if(crawler.base().contains(fs.base()))
			++occ;
		}
		if(occ >= ui->_minOccurence->value() && (ui->_maxOccurence->value() == 0 || ui->_maxOccurence->value() >= occ)) {
		    ContentRecord* cr = new ContentRecord();
                    cr->setSource(this->_content.value(fs)->source());
                    cr->setTarget(this->_content.value(fs)->target());
                    _found.insertMulti(fs, cr);
		}
	    }
	} else if(wc >= this->_maxWordCount && this->_maxWordCount)
	    continue;
	else if(this->_found.contains(fs))
	    continue;
	else {
	    unsigned occ = 0;
	    foreach(FuzzyStrings crawler, this->_content.keys()) {
		if(crawler.base().contains(fs.base()))
		    ++occ;
	    }
	    if(occ >= ui->_minOccurence->value() && (ui->_maxOccurence->value() == 0 || ui->_maxOccurence->value() >= occ)) {
		ContentRecord* cr = new ContentRecord();
                cr->setSource(this->_content.value(fs)->source());
                cr->setTarget(this->_content.value(fs)->target());
                _found.insertMulti(fs, cr);
	    }
	}
    }
    _ok = true;
}

void GlossaryExtractorDialog::on__close_clicked()
{

}
