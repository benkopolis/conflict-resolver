#include "filtersdialog.h"
#include "ui_filtersdialog.h"

FiltersDialog::FiltersDialog(ContentModel* c, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FiltersDialog)
{
    ui->setupUi(this);
    _ok = false;
    _model = c;
    _ascending = false;
    ui->_asc->setChecked(true);
    this->setWindowTitle(QString("Okno filtrowania"));
}

FiltersDialog::~FiltersDialog()
{
    delete ui;
}

void FiltersDialog::changeEvent(QEvent *e)
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

void FiltersDialog::on__ok_clicked()
{
    _ok = true;
    _dateTime = ui->_dateTimeEdit->dateTime();
    if(ui->_asc->isChecked())
	_ascending = true;
    else if(ui->_desc->isChecked())
	_ascending = false;
    _dontFilterConf = ui->_dontFilterConf->isChecked();
    _model->setDateTime(_dateTime);
    _model->setAscending(_ascending);
    _model->setDontFilterConflicts(_dontFilterConf);
    this->close();
}

void FiltersDialog::on__cancel_clicked()
{
    _ok = false;
    this->close();
}
