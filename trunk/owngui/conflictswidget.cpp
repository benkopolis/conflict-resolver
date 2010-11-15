#include "conflictswidget.h"


ConflictsWidget::ConflictsWidget(QWidget *parent) :
    QWidget(parent)
{
    _conflictsWidget = new QHash<MultipleContentWidget* , ConflictRecord* >();
    _prevButton = new QPushButton(this);
    _prevButton->setText("Poprzedni");
    _nextButton = new QPushButton(this);
    _nextButton->setText("Nastepny");
    _dumpButton = new QPushButton(this);
    _dumpButton->setText("Na pozniej");
    _resolveButton = new QPushButton(this);
    _resolveButton->setText("Zaakceptuj");
    _delButton = new QPushButton(this);
    _delButton->setText("Skasuj");
    _selectAll = new QPushButton(this);
    _selectAll->setText("Zaznacz wszystko");
    _deselectAll = new QPushButton(this);
    _deselectAll->setText("Odznacz wszystko");
    sa = new QScrollArea(this);
    QGridLayout* gd = new QGridLayout(this);
    gd->addWidget(sa, 0, 0, 7, 4);
    initLayout(gd);
    _index = 0;
    setWindowTitle("Konflikty");
    //------------------- connections --------------------
    connect(_prevButton, SIGNAL(clicked()), this, SLOT(onPrev()));
    connect(_nextButton, SIGNAL(clicked()), this, SLOT(onNext()));
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
    connect(_delButton, SIGNAL(clicked()), this, SLOT(onDel()));
    connect(_dumpButton, SIGNAL(clicked()), this, SLOT(onDump()));
    connect(_resolveButton, SIGNAL(clicked()), this, SLOT(onResolve()));
    connect(_selectAll, SIGNAL(clicked()), this, SLOT(onSelectAll()));
    connect(_deselectAll, SIGNAL(clicked()), this, SLOT(onDeselectAll()));
}

void ConflictsWidget::setupModel(QMultiHash<FuzzyStrings, ConflictRecord* >* data)
{
    _data = data;
    foreach(ConflictRecord* cr, _data->values())
    {
	MultipleContentWidget* mcw = new MultipleContentWidget(this);
	mcw->setupModel(cr);
	_conflictsWidget->insert(mcw, cr);
    }
    sa->setLayout(new QGridLayout(sa));
    sa->layout()->addWidget(_conflictsWidget->keys().at(_index));
    this->updateButtons(0);
}

void ConflictsWidget::updateButtons(int row)
{
    if(_data == 0)
	return;
    _prevButton->setEnabled(row > 0);
    _nextButton->setEnabled(row < _data->values().size() - 1);
}

void ConflictsWidget::onCurrentIndexChanged(int index)
{
    sa = new QScrollArea(this);
    QGridLayout* gd = qobject_cast<QGridLayout*>(this->layout());
    gd->addWidget(sa, 0, 0, 7, 4);
    sa->setLayout(new QGridLayout(sa));
    Q_ASSERT(_conflictsWidget->keys().at(index) != 0);
    sa->layout()->addWidget(_conflictsWidget->keys().at(index));
}

void ConflictsWidget::onNext()
{
    sa->layout()->removeWidget(_conflictsWidget->keys().at(_index));;
    this->layout()->removeWidget(sa);
    ++_index;
    emit currentIndexChanged(_index);
}

void ConflictsWidget::onPrev()
{
    sa->layout()->removeWidget(_conflictsWidget->keys().at(_index));
    this->layout()->removeWidget(sa);
    --_index;
    emit currentIndexChanged(_index);
}

void ConflictsWidget::onDel()
{
    QVector<QCheckBox*>& cblist = _conflictsWidget->keys().at(_index)->checks();
    int i =0;
    for(i=0; i<cblist.size(); ++i)
    {
	if(cblist.at(i)->isChecked())
	{
	    this->_conflictsWidget->value( _conflictsWidget->keys().at(_index))->conflictedRecords().at(i)->denyInConflict();
	}
    }
}

void ConflictsWidget::onDump()
{
    QVector<QCheckBox*>& cblist = _conflictsWidget->keys().at(_index)->checks();
    int i =0;
    for(i=0; i<cblist.size(); ++i)
    {
	if(cblist.at(i)->isChecked())
	{
	    this->_conflictsWidget->value( _conflictsWidget->keys().at(_index))->conflictedRecords().at(i)->delayInConflict();;
	}
    }
}

void ConflictsWidget::onResolve()
{
    QVector<QCheckBox*>& cblist = _conflictsWidget->keys().at(_index)->checks();
    int i =0;
    for(i=0; i<cblist.size(); ++i)
    {
	if(cblist.at(i)->isChecked())
	{
	    this->_conflictsWidget->value( _conflictsWidget->keys().at(_index))->conflictedRecords().at(i)->confirmInConflict();
	}
    }
}

void ConflictsWidget::onSelectAll()
{
    QVector<QCheckBox*>& cblist = _conflictsWidget->keys().at(_index)->checks();
    int i =0;
    for(i=0; i<cblist.size(); ++i)
    {
	cblist.at(i)->setChecked(true);
    }
}

void ConflictsWidget::onDeselectAll()
{
    QVector<QCheckBox*>& cblist = _conflictsWidget->keys().at(_index)->checks();
    int i =0;
    for(i=0; i<cblist.size(); ++i)
    {
	cblist.at(i)->setChecked(false);
    }
}

void ConflictsWidget::initLayout(QGridLayout* gd)
{
    gd->addWidget(_selectAll, 0, 4, 1, 1);
    gd->addWidget(_deselectAll, 1, 4, 1, 1);
    gd->addWidget(_prevButton, 2, 4, 1, 1);
    gd->addWidget(_nextButton, 3, 4, 1, 1);
    gd->addWidget(_delButton, 4, 4, 1, 1);
    gd->addWidget(_dumpButton, 5, 4, 1, 1);
    gd->addWidget(_resolveButton, 6, 4, 1, 1);
}
