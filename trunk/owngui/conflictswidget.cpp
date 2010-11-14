#include "conflictswidget.h"
#include <QScrollArea>

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
    QScrollArea* sa = new QScrollArea(this);
    QGridLayout* gd = new QGridLayout(this);
    gd->addWidget(sa, 0, 0, 7, 4);
    initLayout(gd);
    _index = 0;
    setWindowTitle("Konflikty");
    //------------------- connections --------------------
    connect(_prevButton, SIGNAL(clicked()), this, SLOT(onPrev()));
    connect(_nextButton, SIGNAL(clicked()), this, SLOT(onNext()));
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
    connect(_delButton, SIGNAL(clicked()), this, SLOT(onDel()));
    connect(_dumpButton, SIGNAL(clicked()), this, SLOT(onDump()));
    connect(_resolveButton, SIGNAL(clicked()), this, SLOT(onResolve()));
}

void ConflictsWidget::setupModel(QMultiHash<FuzzyStrings, ConflictRecord* >* data)
{

    _data = data;
    foreach(ConflictRecord* cr, _data->values())
    {
	MultipleContentWidget* mcw = new MultipleContentWidget(this);
	_conflictsWidget->insert(mcw, cr);
    }
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

}

void ConflictsWidget::onNext()
{
    ++_index;
    emit currentIndexChanged(_index);

}

void ConflictsWidget::onPrev()
{
    --_index;
    emit currentIndexChanged(_index);
}

void ConflictsWidget::onDel()
{

}

void ConflictsWidget::onDump()
{

}

void ConflictsWidget::onResolve()
{

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
