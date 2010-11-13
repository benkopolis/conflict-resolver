#include "owngui/contentwidget.h"
#include <QGridLayout>
#include "contentrecord.h"

ContentWidget::ContentWidget(QWidget *parent) :
    QWidget(parent)
{
    _sourceEdit = new QTextEdit(this);
    _sourceLabel = new QLabel(this);
    _sourceLabel->setText("Tekst zrodlowy");
    _targetLabel = new QLabel(this);
    _targetLabel->setText("Tekst docelowy");
    _targetEdit = new QTextEdit(this);
    _mapper = 0;
    _model = 0;
    _sourceLabel->setBuddy(_sourceEdit);
    _targetLabel->setBuddy(_targetEdit);
    _nextButton = new QPushButton(this);
    _previousButton = new QPushButton(this);
    _nextButton->setText(">");
    _previousButton->setText("<");
    _previousButton->setEnabled(false);
    _nextButton->setEnabled(false);
    _data = 0;
}

void ContentWidget::setupModel(ConflictRecord* data)
{
    _model = new QStandardItemModel(this);
    _mapper = new QDataWidgetMapper(this);
    _model->setColumnCount(3);
    _model->setHeaderData(0, Qt::Horizontal, "Zrodlo", Qt::ToolTip);
    _model->setHeaderData(1, Qt::Horizontal, "Docelowy", Qt::ToolTip);
    _model->setHeaderData(2, Qt::Horizontal, "Id", Qt::ToolTip);

    _mapper->setModel(_model);
    _mapper->addMapping(_sourceEdit, 0);
    _mapper->addMapping(_targetEdit, 1);

    connect(_previousButton, SIGNAL(clicked()), _mapper, SLOT(toPrevious()));
    connect(_nextButton, SIGNAL(clicked()), _mapper, SLOT(toNext()));
    connect(_mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
    connect(_model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onItemDataChanged(QStandardItem*)));

    QGridLayout * layout = new QGridLayout(this);
    layout->addWidget(_sourceLabel, 0, 0, 1, 1);
    layout->addWidget(_sourceEdit, 0, 1, 1, 1);
    layout->addWidget(_targetLabel, 1, 0, 1, 1);
    layout->addWidget(_targetEdit, 1, 1, 1, 1);
    layout->addWidget(_nextButton, 0, 2, 1, 1);
    layout->addWidget(_nextButton, 1, 2, 1, 1);
    this->setLayout(layout);
    _mapper->toFirst();
    initData(data);
}

void ContentWidget::updateButtons(int row)
{
    if(_model == 0)
	return;
    _previousButton->setEnabled(row > 0);
    _nextButton->setEnabled(row < _model->rowCount() - 1);

}

void ContentWidget::initData(ConflictRecord* data)
{
    QModelIndex index;
    _model->setRowCount(data->conflictedRecords().size());
    int i =0;
    foreach(ContentRecord* cr, data->conflictedRecords())
    {
	index = _model->index(i, 0);
	_model->setData(index, cr->source(), Qt::EditRole);
	index = _model->index(i, 1);
	_model->setData(index, cr->target(), Qt::EditRole);
	index = _model->index(i, 2);
	_model->setData(index, (int)cr, Qt::DisplayRole);
	++i;
    }
    _data = data;
}

void ContentWidget::onItemDataChanged(QStandardItem* item)
{
    QModelIndex index = item->index();
    if(index.column() == 0)
	_data->conflictedRecords().at(index.row())->setSource(qvariant_cast<QString>(item->data()));
    else if(index.column() == 1)
	_data->conflictedRecords().at(index.row())->setTarget(qvariant_cast<QString>(item->data()));
}
