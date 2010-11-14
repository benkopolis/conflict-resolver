#ifndef MULTIPLECONTENTWIDGET_H
#define MULTIPLECONTENTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include <QPushButton>
#include <QVector>

#include "conflictrecord.h"


class Proxy : public QObject
{
    Q_OBJECT
public:
    explicit Proxy(QObject *parent);

public slots:

    void onItemChanged(QStandardItem* item);

signals:

    void itemChanged(Proxy* p);
};

class MultipleContentWidget : public QWidget
{
Q_OBJECT
public:
    explicit MultipleContentWidget(QWidget *parent = 0);

    inline QVector<QCheckBox* >& checks() { return _checks; }

public slots:

    void setupModel(ConflictRecord* data);
    void updateButtons(int row);

private slots:

    void onItemDataChanged(Proxy* p);

protected:

    virtual void initData(int row, ContentRecord* cr);


    QVector<QLabel* > _sourceLabels;
    QVector<QLabel* > _targetLabels;
    QVector<QTextEdit* > _sourceEdits;
    QVector<QTextEdit* > _targetEdits;
    QVector<QCheckBox* > _checks;

    QVector<QStandardItemModel* > _models;
    QVector<QDataWidgetMapper* > _mappers;
    QHash<Proxy*, int> _proxy;
    ConflictRecord* _data;

};

#endif // MULTIPLECONTENTWIDGET_H
