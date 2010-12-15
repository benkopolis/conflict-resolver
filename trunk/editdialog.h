#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include "contentmodel.h"
#include "records/contentrecord.h"
#include "records/tmrecord.h"

namespace Ui {
    class EditDialog;
}

class EditDialog : public QDialog {
    Q_OBJECT
public:
    EditDialog(QWidget *parent = 0);
    EditDialog(ContentModel::ContentType type, ContentRecord* record, QWidget *parent = 0);
    ~EditDialog();

protected:
    void changeEvent(QEvent *e);

    TMRecord* _tmRecord;
    ContentRecord* _cRecord;

private:
    Ui::EditDialog *ui;

private slots:
    void on__cancelButton_clicked();
    void on__okButton_clicked();
};

#endif // EDITDIALOG_H
