#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
}

EditDialog::EditDialog(ContentModel::ContentType type, ContentRecord* record, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
    ui->_source->setPlainText(record->source());
    ui->_target->setPlainText(record->target());
    if(type == ContentModel::TM) {
	_tmRecord = qobject_cast<TMRecord* >(record);
	_cRecord = 0;
    } else {
	_tmRecord = 0;
	_cRecord = record;
    }
}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::changeEvent(QEvent *e)
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

void EditDialog::on__okButton_clicked()
{
    if(_tmRecord != 0) {
	_tmRecord->setSource(ui->_source->toPlainText());
	_tmRecord->setTarget(ui->_target->toPlainText());
    } else if(_cRecord != 0) {
	_cRecord->setSource(ui->_source->toPlainText());
	_cRecord->setTarget(ui->_target->toPlainText());
    }
    this->close();
}

void EditDialog::on__cancelButton_clicked()
{
    this->close();
}
