#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include "conflictrecord.h"

class ContentWidget : public QWidget
{
Q_OBJECT
public:
    explicit ContentWidget(QWidget *parent = 0);

signals:

    void currentIndexChanged(int index);

public slots:

    void setupModel(ConflictRecord* data);
    void updateButtons(int row);
    void moveFwd();
    void moveRev();

private slots:

    void onItemDataChanged(QStandardItem* item);

protected:

    virtual void initData(ConflictRecord* data);

    QTextEdit *_sourceEdit;
    QTextEdit *_targetEdit;
    QPushButton *_nextButton;
    QPushButton *_previousButton;

    QStandardItemModel *_model;
    QDataWidgetMapper *_mapper;
    ConflictRecord* _data;

};

#endif // CONTENTWIDGET_H
