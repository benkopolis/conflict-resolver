#include "conflictswidget.h"

ConflictsWidget::ConflictsWidget(QWidget *parent) :
    QWidget(parent)
{
}

void ConflictsWidget::setupModel(QMultiHash<FuzzyStrings, ConflictRecord* >* data)
{
    _data = data;
}

void ConflictsWidget::updateButtons(int row)
{

}

void ConflictsWidget::onCurrentIndexChanged(int index)
{

}
