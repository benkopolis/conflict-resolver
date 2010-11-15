#ifndef FUZZYOPTIONSDIALOG_H
#define FUZZYOPTIONSDIALOG_H

#include <QDialog>

#include <QDataWidgetMapper>
#include <QStandardItemModel>

namespace Ui {
    class FuzzyOptionsDialog;
}

class FuzzyOptionsDialog : public QDialog {
    Q_OBJECT
public:
    FuzzyOptionsDialog(QWidget *parent = 0);
    ~FuzzyOptionsDialog();

public slots:
    void onValueChanged(QStandardItem* item);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FuzzyOptionsDialog *ui;

    QDataWidgetMapper* dmw;
    QStandardItemModel* sim;
};

#endif // FUZZYOPTIONSDIALOG_H
