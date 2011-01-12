#include "conflictswidget.h"
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>

ConflictsWidget::ConflictsWidget(QWidget *parent) :
    QWidget(parent)
{
    _conflictsWidget = new QHash<MultipleContentWidget* , ConflictRecord* >();
    _prevButton = new QPushButton(this);
    _prevButton->setText("Poprzedni");
    _nextButton = new QPushButton(this);
    _nextButton->setText("Nastepny");
    sa = new QScrollArea(this);
    sa->setMaximumSize(QApplication::desktop()->screenGeometry().size().width()-200,
                       QApplication::desktop()->screenGeometry().size().height()-200);
    _gd = new QGridLayout(this);
    _gd->addWidget(sa, 1, 0, 7, 4);
    sa->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
    sa->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
    initLayout(_gd);
    _index = 0;
    setWindowTitle("Konflikty");
    //------------------- connections --------------------
    connect(_prevButton, SIGNAL(clicked()), this, SLOT(onPrev()));
    connect(_nextButton, SIGNAL(clicked()), this, SLOT(onNext()));
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));;
    if(parent!=0)
	this->setMaximumSize(parent->maximumSize());
}

ConflictsWidget::~ConflictsWidget()
{
    this->destroy(true, true);
    delete _prevButton;
    delete _nextButton;
    delete sa;
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
    sa->setMinimumHeight(_conflictsWidget->keys().at(_index)->minimumHeight()+10);
    sa->layout()->addWidget(_conflictsWidget->keys().at(_index));
    this->updateButtons(0);
}

void ConflictsWidget::updateButtons(int row)
{
    if(_data == 0)
	return;
    _prevButton->setEnabled(row > 0);
    _nextButton->setEnabled(row < _data->values().size() - 1);
    emit prevStatus(_prevButton->isEnabled());
    emit nextStatus(_nextButton->isEnabled());
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
    sa->layout()->removeWidget(_conflictsWidget->keys().at(_index));
    _conflictsWidget->keys().at(_index);
    this->layout()->removeWidget(sa);
    ++_index;
    emit currentIndexChanged(_index);
}

void ConflictsWidget::onPrev()
{
    sa->layout()->removeWidget(_conflictsWidget->keys().at(_index));
    _conflictsWidget->keys().at(_index);
    this->layout()->removeWidget(sa);
    --_index;
    emit currentIndexChanged(_index);
}

void ConflictsWidget::initLayout(QGridLayout* gd)
{
    gd->addWidget(_prevButton, 1, 4, 1, 1);
    gd->addWidget(_nextButton, 2, 4, 1, 1);
    QLabel* src = new QLabel(QString("Tekst poczatkowy:"), this);
    QLabel* dst = new QLabel(QString("Tekst docelowy:"), this);
    QLabel* act = new QLabel(QString("Akcje"), this);
    gd->addWidget(act, 0,0,1,1);
    gd->addWidget(src, 0, 1, 1, 1);
    gd->addWidget(dst, 0,2, 1,1);
}
