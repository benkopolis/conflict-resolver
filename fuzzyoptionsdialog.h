#ifndef FUZZYOPTIONSDIALOG_H
#define FUZZYOPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
    class FuzzyOptionsDialog;
}

class FuzzyOptionsDialog : public QDialog {
    Q_OBJECT
public:
    FuzzyOptionsDialog(QWidget *parent = 0);
    ~FuzzyOptionsDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FuzzyOptionsDialog *ui;
};

#endif // FUZZYOPTIONSDIALOG_H
