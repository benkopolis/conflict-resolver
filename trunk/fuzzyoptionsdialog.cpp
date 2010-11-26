#include "fuzzyoptionsdialog.h"
#include "ui_fuzzyoptionsdialog.h"
#include "inifile.h"


FuzzyOptionsDialog::FuzzyOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FuzzyOptionsDialog)
{
    ui->setupUi(this);
    if(IniFile::instance()->fval() == 0)
        IniFile::instance()->setFval(75);
    dmw = new QDataWidgetMapper(this);
    sim = new QStandardItemModel(this);
    sim->setColumnCount(1);
    sim->setRowCount(1);
    QModelIndex ind = sim->index(0,0);
    sim->setData(ind, IniFile::instance()->fval(), Qt::EditRole);
    dmw->setModel(sim);
    dmw->addMapping(this->ui->_fuzzyValue, 0);
    connect(sim, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onValueChanged(QStandardItem*)));
}

FuzzyOptionsDialog::~FuzzyOptionsDialog()
{
    delete dmw;
    dmw = 0;
    delete sim;
    sim = 0;
    delete ui;
}

void FuzzyOptionsDialog::onValueChanged(QStandardItem* item)
{
    IniFile::instance()->setFval(qvariant_cast<unsigned>(item->data()));
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
