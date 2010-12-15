#ifndef MULTIPLECONTENTWIDGET_H
#define MULTIPLECONTENTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include <QPushButton>
#include <QRadioButton>
#include <QVector>
#include <QGroupBox>

#include "records/conflictrecord.h"


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

/**
  * Klasa odpowiadajaca za wyswietlanie jednego konfliktu, zlozonego z wielu rekordow.
  */
class MultipleContentWidget : public QWidget
{
Q_OBJECT
public:
    explicit MultipleContentWidget(QWidget *parent = 0);
    virtual ~MultipleContentWidget();

    inline QVector<QGroupBox* >& radios() { return _radios; }

public slots:

    void setupModel(ConflictRecord* data);
    void updateButtons(int row);

private slots:

    void onItemDataChanged(Proxy* p);

protected:

    virtual void initData(int row, ContentRecord* cr);


    QVector<QTextEdit* > _sourceEdits;
    QVector<QTextEdit* > _targetEdits;
    QVector<QGroupBox* > _radios;
    QVector<QRadioButton* > _del;
    QVector<QRadioButton* > _ok;
    QVector<QRadioButton* > _def;

    QVector<QStandardItemModel* > _models;
    QVector<QDataWidgetMapper* > _mappers;
    QHash<Proxy*, int> _proxy;
    ConflictRecord* _data;

};

#endif // MULTIPLECONTENTWIDGET_H
