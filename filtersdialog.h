#ifndef FILTERSDIALOG_H
#define FILTERSDIALOG_H

#include <QDialog>
#include <QDateTime>
#include "contentmodel.h"

namespace Ui {
    class FiltersDialog;
}

class FiltersDialog : public QDialog {
    Q_OBJECT
public:
    FiltersDialog(ContentModel* c, QWidget *parent = 0);
    ~FiltersDialog();

    inline bool isOkClicked() const {return _ok; }
    inline QDateTime dateTime() const { return _dateTime; }
    inline bool isAscending() const { return _ascending; }
    inline bool isDontFilterConflicts() const { return _dontFilterConf; };

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FiltersDialog *ui;

    ContentModel* _model;
    bool _ok;
    QDateTime _dateTime;
    bool _ascending;
    bool _dontFilterConf;

private slots:
    void on__cancel_clicked();
    void on__ok_clicked();
};

#endif // FILTERSDIALOG_H
