#ifndef CONFLICTSWIDGET_H
#define CONFLICTSWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QCheckBox>
#include <QMultiHash>
#include <QStandardItemModel>
#include <QDataWidgetMapper>

#include "owngui/contentwidget.h"
#include "conflictrecord.h"



class ConflictsWidget : public QWidget
{
Q_OBJECT
public:
    explicit ConflictsWidget(QWidget *parent = 0);

signals:

public slots:

    void setupModel(QMultiHash<FuzzyStrings, ConflictRecord* >* data);
    void updateButtons(int row);

private slots:

    void onCurrentIndexChanged(int index);

protected:

    QVector<ContentWidget* > _widgets;
    QVector<QCheckBox* > _checks;
    QPushButton _nextButton;
    QPushButton _prevBottun;
    QPushButton _delButton;
    QPushButton _dumpButton;
    QPushButton _resolveButton;

    QMultiHash<FuzzyStrings, ConflictRecord* >* _data;
};

#endif // CONFLICTSWIDGET_H
