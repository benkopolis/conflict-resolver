#include "multiplecontentwidget.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>

Proxy::Proxy(QObject *parent = 0):
	QObject(parent)
{

}

void Proxy::onItemChanged(QStandardItem* item)
{
    emit itemChanged(this);
}

MultipleContentWidget::MultipleContentWidget(QWidget *parent) :
    QWidget(parent)
{
    _data = 0;
}

MultipleContentWidget::~MultipleContentWidget()
{
    this->destroy(true, true);
    for(int i =0; i < _sourceEdits.size(); ++i)
    {
	Proxy* p = _proxy.key(i);
//	disconnect(_models.at(i), SIGNAL(itemChanged(QStandardItem*)), p, SLOT(onItemChanged(QStandardItem*)));
//	disconnect()
//	disconnect(p, SIGNAL(itemChanged(Proxy*)), this, SLOT(onItemDataChanged(Proxy*)));
//	disconnect(_def.at(i), SIGNAL(clicked()), _data->, SLOT(delayInConflict()));
//	disconnect(_del.at(i), SIGNAL(clicked()), cr, SLOT(denyInConflict()));
//	disconnect(_ok.at(i), SIGNAL(clicked()), cr, SLOT(confirmInConflict()));
	delete _sourceEdits.at(i);
	delete _targetEdits.at(i);
	delete _del.at(i);
	delete _def.at(i);
	delete _ok.at(i);
	delete _radios.at(i);
	delete _models.at(i);
	delete _mappers.at(i);
	delete p;
    }
}

void MultipleContentWidget::setupModel(ConflictRecord* data)
{
    Q_ASSERT(data != 0);
    _data = data;
    QGridLayout* lay = new QGridLayout;
    this->setLayout(lay);
    int rows = 0;
    foreach(ContentRecord* cr, data->conflictedRecords())
    {
	QTextEdit* e = new QTextEdit(this);
	QGroupBox* c = new QGroupBox("Akcja", this);
	c->setMinimumHeight(50);
	QRadioButton *r1, *r2, *r3;
	r1 = new QRadioButton("Zaakceptuj", this);
	r1->setMinimumHeight(10);
	r2 = new QRadioButton("Skasuj", this);
	r2->setMinimumHeight(10);
	r3 = new QRadioButton("Na potem", this);
	r3->setMinimumHeight(10);
	_def.push_back(r3);
	_del.push_back(r2);
	_ok.push_back(r1);
	r3->setChecked(true);
	QVBoxLayout* vbox = new QVBoxLayout;
	vbox->addWidget(r1);
	vbox->addWidget(r2);
	vbox->addWidget(r3);
	vbox->addStretch(1);
	c->setLayout(vbox);
	c->setChecked(false);
	lay->addWidget(c, rows, 0, 1, 1);
	lay->addWidget(e, rows, 1, 1, 1);
	_sourceEdits.push_back(e);
	_radios.push_back(c);
	e = new QTextEdit(this);
	lay->addWidget(e, rows, 2, 1, 1);
	_targetEdits.push_back(e);
	initData(rows, cr);
	++rows;
    }
    this->setMinimumHeight(70*rows);
}

void MultipleContentWidget::updateButtons(int row)
{

}

void MultipleContentWidget::onItemDataChanged(Proxy* item)
{
    int row = _proxy.value(item);
    QString tmp = (qvariant_cast<QString>(_models.at(row)->data(_models.at(row)->index(row, 1))));
    if(tmp.length() > 0)
	_data->conflictedRecords().at(row)->setTarget(qvariant_cast<QString>(_models.at(row)->data(_models.at(row)->index(row, 1))));
    tmp = (qvariant_cast<QString>(_models.at(row)->data(_models.at(row)->index(row, 0))));
    if(tmp.length() > 0)
	_data->conflictedRecords().at(row)->setSource(qvariant_cast<QString>(_models.at(row)->data(_models.at(row)->index(row, 0))));
}

void MultipleContentWidget::initData(int row, ContentRecord* cr)
{
    QStandardItemModel* model = new QStandardItemModel(this);
    QDataWidgetMapper* mapper = new QDataWidgetMapper(this);
    _mappers.push_back(mapper);
    _models.push_back(model);
    _mappers.at(row)->setOrientation(Qt::Horizontal);
    _models.at(row)->setColumnCount(3);
    _models.at(row)->setHeaderData(0, Qt::Horizontal, "Zrodlo", Qt::ToolTip);
    _models.at(row)->setHeaderData(1, Qt::Horizontal, "Docelowy", Qt::ToolTip);
    _models.at(row)->setHeaderData(2, Qt::Horizontal, "Id", Qt::ToolTip);

    _mappers.at(row)->setModel(_models.at(row));
    _mappers.at(row)->addMapping(_sourceEdits.at(row), 0);
    _mappers.at(row)->addMapping(_targetEdits.at(row), 1);

    Proxy* p = new Proxy(this);
    _proxy.insert(p, row);
    connect(_models.at(row), SIGNAL(itemChanged(QStandardItem*)), p, SLOT(onItemChanged(QStandardItem*)));
    connect(p, SIGNAL(itemChanged(Proxy*)), this, SLOT(onItemDataChanged(Proxy*)));
    connect(_def.at(row), SIGNAL(clicked()), cr, SLOT(delayInConflict()));
    connect(_del.at(row), SIGNAL(clicked()), cr, SLOT(denyInConflict()));
    connect(_ok.at(row), SIGNAL(clicked()), cr, SLOT(confirmInConflict()));

    QModelIndex index;
    _models.at(row)->setRowCount(1);
    index = _models.at(row)->index(0, 0);
    _models.at(row)->setData(index, cr->source(), Qt::EditRole);
    qDebug() << "zrodlo: " << cr->source();
    index = _models.at(row)->index(0, 1);
    _models.at(row)->setData(index, cr->target(), Qt::EditRole);
    qDebug() << "cel: " << cr->target();
    index = _models.at(row)->index(0, 2);
    _models.at(row)->setData(index, (int)cr, Qt::DisplayRole);
    _mappers.at(row)->toFirst();
}
