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
#include <QScrollArea>

#include "owngui/multiplecontentwidget.h"



class ConflictsWidget : public QWidget
{
Q_OBJECT
public:
    explicit ConflictsWidget(QWidget *parent = 0);
    virtual ~ConflictsWidget();

    inline bool prevStatus() const { return _prevButton->isEnabled(); }
    inline bool nextStatus() const { return _nextButton->isEnabled(); }

signals:

    void currentIndexChanged(int index);
    void nextStatus(bool en);
    void prevStatus(bool en);

public slots:

    void setupModel(QMultiHash<FuzzyStrings, ConflictRecord* >* data);
    void updateButtons(int row);

private slots:

    void onCurrentIndexChanged(int index);
    void onNext();
    void onPrev();

protected:

    void initLayout(QGridLayout* gd);

    int _index;

    QVector<MultipleContentWidget* > _widgets;

    QPushButton* _nextButton;
    QPushButton* _prevButton;

    QScrollArea* sa;
    QGridLayout* _gd;

    QMultiHash<FuzzyStrings, ConflictRecord* >* _data;
    QHash<MultipleContentWidget* , ConflictRecord* >* _conflictsWidget;
};

#endif // CONFLICTSWIDGET_H
