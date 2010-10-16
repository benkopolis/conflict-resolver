#include "fuzzyoptionsdialog.h"
#include "ui_fuzzyoptionsdialog.h"

FuzzyOptionsDialog::FuzzyOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FuzzyOptionsDialog)
{
    ui->setupUi(this);
}

FuzzyOptionsDialog::~FuzzyOptionsDialog()
{
    delete ui;
}

void FuzzyOptionsDialog::changeEvent(QEvent *e)
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
