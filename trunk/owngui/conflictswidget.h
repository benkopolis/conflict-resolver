#ifndef CONFLICTSWIDGET_H
#define CONFLICTSWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QCheckBox>
#include <QMultiHash>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include <QGridLayout>

#include "owngui/multiplecontentwidget.h"



class ConflictsWidget : public QWidget
{
Q_OBJECT
public:
    explicit ConflictsWidget(QWidget *parent = 0);

signals:

    void currentIndexChanged(int index);

public slots:

    void setupModel(QMultiHash<FuzzyStrings, ConflictRecord* >* data);
    void updateButtons(int row);

private slots:

    void onCurrentIndexChanged(int index);
    void onNext();
    void onPrev();
    void onDel();
    void onDump();
    void onResolve();

protected:

    void initLayout(QGridLayout* gd);

    int _index;

    QVector<MultipleContentWidget* > _widgets;

    QPushButton* _nextButton;
    QPushButton* _prevButton;

    QPushButton* _delButton;
    QPushButton* _dumpButton;
    QPushButton* _resolveButton;
    QPushButton* _selectAll;
    QPushButton* _deselectAll;

    QMultiHash<FuzzyStrings, ConflictRecord* >* _data;
    QHash<MultipleContentWidget* , ConflictRecord* >* _conflictsWidget;
};

#endif // CONFLICTSWIDGET_H
