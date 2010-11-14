#ifndef MULTIPLECONTENTWIDGET_H
#define MULTIPLECONTENTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include "conflictrecord.h"
#include <QVector>

class MultipleContentWidget : public QWidget
{
Q_OBJECT
public:
    explicit MultipleContentWidget(QWidget *parent = 0);

public slots:

    void setupModel(ConflictRecord* data);
    void updateButtons(int row);

private slots:

    void onItemDataChanged(QStandardItem* item);

protected:

    virtual void initData(ConflictRecord* data);


    QVector<QLabel* > _sourceLabels;
    QVector<QLabel* > _targetLabels;
    QVector<QTextEdit* > _sourceEdits;
    QVector<QTextEdit* > _targetEdits;
    QVector<QCheckBox* > _checks;

    QVector<QStandardItemModel* > _models;
    QVector<QDataWidgetMapper* > _mapper;
    ConflictRecord* _data;

};

#endif // MULTIPLECONTENTWIDGET_H
