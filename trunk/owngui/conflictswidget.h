#ifndef CONFLICTSWIDGET_H
#define CONFLICTSWIDGET_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QMultiHash>
#include <QStandardItemModel>
#include <QDataWidgetMapper>

#include "conflictrecord.h"



class ConflictsWidget : public QWidget
{
Q_OBJECT
public:
    explicit ConflictsWidget(QWidget *parent = 0);

signals:

public slots:

    void setupModel(ConflictRecord* data);
    void updateButtons(int row);

private slots:

    void onItemDataChanged(QStandardItem* item);

protected:

    QVector<QLabel* > _labels;
    QVector<QTextEdit* > _edits;
    QPushButton _nextButton;
    QPushButton _prevBottun;
    QPushButton _delButton;
    QPushButton _dumpButton;
    QPushButton _resolveButton;
};

#endif // CONFLICTSWIDGET_H
