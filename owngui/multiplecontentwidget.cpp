#include "multiplecontentwidget.h"
#include <QGridLayout>

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

void MultipleContentWidget::setupModel(ConflictRecord* data)
{
    Q_ASSERT(data != 0);
    _data = data;
    QGridLayout* lay = new QGridLayout(this);
    this->setLayout(lay);
    int rows = 0;
    foreach(ContentRecord* cr, data->conflictedRecords())
    {
	QTextEdit* e = new QTextEdit(this);
	QLabel* l = new QLabel(this);
	QCheckBox* c = new QCheckBox(this);
	l->setBuddy(e);
	l->setText("Tekst poczatkowy:");
	c->setChecked(false);
	lay->addWidget(c, rows, 0, 1, 1);
	lay->addWidget(l, rows, 1, 1, 1);
	lay->addWidget(e, rows, 2, 1, 1);
	_sourceLabels.push_back(l);
	_sourceEdits.push_back(e);
	_checks.push_back(c);
	e = new QTextEdit(this);
	l = new QLabel(this);
	l->setBuddy(e);
	l->setText("Tekst koncowy:");
	lay->addWidget(l, rows, 3, 1, 1);
	lay->addWidget(e, rows, 4, 1, 1);
	_targetEdits.push_back(e);
	_targetLabels.push_back(l);
	initData(rows, cr);
	++rows;
    }
}

void MultipleContentWidget::updateButtons(int row)
{

}

void MultipleContentWidget::onItemDataChanged(Proxy* item)
{
    int row = _proxy.value(item);
    _data->conflictedRecords().at(row)->setTarget(qvariant_cast<QString>(_models.at(row)->data(_models.at(row)->index(row, 1))));
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

    QModelIndex index;
    _models.at(row)->setRowCount(1);
    int i =0;
    index = _models.at(row)->index(i, 0);
    _models.at(row)->setData(index, cr->source(), Qt::EditRole);
    index = _models.at(row)->index(i, 1);
    _models.at(row)->setData(index, cr->target(), Qt::EditRole);
    index = _models.at(row)->index(i, 2);
    _models.at(row)->setData(index, (int)cr, Qt::DisplayRole);
}
