/********************************************************************************
** Form generated from reading UI file 'editdialog.ui'
**
** Created: Wed Dec 15 10:25:29 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDIALOG_H
#define UI_EDITDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QPlainTextEdit *_source;
    QLabel *label_2;
    QPlainTextEdit *_target;
    QPushButton *_okButton;
    QPushButton *_cancelButton;

    void setupUi(QDialog *EditDialog)
    {
        if (EditDialog->objectName().isEmpty())
            EditDialog->setObjectName(QString::fromUtf8("EditDialog"));
        EditDialog->resize(400, 300);
        gridLayout = new QGridLayout(EditDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(EditDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        _source = new QPlainTextEdit(EditDialog);
        _source->setObjectName(QString::fromUtf8("_source"));

        gridLayout->addWidget(_source, 1, 0, 1, 1);

        label_2 = new QLabel(EditDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        _target = new QPlainTextEdit(EditDialog);
        _target->setObjectName(QString::fromUtf8("_target"));

        gridLayout->addWidget(_target, 3, 0, 1, 1);

        _okButton = new QPushButton(EditDialog);
        _okButton->setObjectName(QString::fromUtf8("_okButton"));

        gridLayout->addWidget(_okButton, 4, 0, 1, 1);

        _cancelButton = new QPushButton(EditDialog);
        _cancelButton->setObjectName(QString::fromUtf8("_cancelButton"));

        gridLayout->addWidget(_cancelButton, 4, 1, 1, 1);


        retranslateUi(EditDialog);

        QMetaObject::connectSlotsByName(EditDialog);
    } // setupUi

    void retranslateUi(QDialog *EditDialog)
    {
        EditDialog->setWindowTitle(QApplication::translate("EditDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EditDialog", "Tekst \305\274r\303\263d\305\202owy:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EditDialog", "Tekst Docelowy:", 0, QApplication::UnicodeUTF8));
        _okButton->setText(QApplication::translate("EditDialog", "OK", 0, QApplication::UnicodeUTF8));
        _cancelButton->setText(QApplication::translate("EditDialog", "Anuluj", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditDialog: public Ui_EditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDIALOG_H
