/********************************************************************************
** Form generated from reading UI file 'filtersdialog.ui'
**
** Created: Fri Nov 26 15:44:37 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERSDIALOG_H
#define UI_FILTERSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_FiltersDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QDateTimeEdit *_dateTimeEdit;
    QGroupBox *groupBox;
    QRadioButton *_desc;
    QRadioButton *_asc;
    QCheckBox *_dontFilterConf;
    QPushButton *_ok;
    QPushButton *_cancel;

    void setupUi(QDialog *FiltersDialog)
    {
        if (FiltersDialog->objectName().isEmpty())
            FiltersDialog->setObjectName(QString::fromUtf8("FiltersDialog"));
        FiltersDialog->resize(400, 300);
        gridLayout = new QGridLayout(FiltersDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(FiltersDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        _dateTimeEdit = new QDateTimeEdit(FiltersDialog);
        _dateTimeEdit->setObjectName(QString::fromUtf8("_dateTimeEdit"));
        _dateTimeEdit->setDateTime(QDateTime(QDate(2010, 4, 23), QTime(0, 0, 0)));

        gridLayout->addWidget(_dateTimeEdit, 1, 0, 1, 1);

        groupBox = new QGroupBox(FiltersDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        _desc = new QRadioButton(groupBox);
        _desc->setObjectName(QString::fromUtf8("_desc"));
        _desc->setGeometry(QRect(10, 50, 91, 17));
        _asc = new QRadioButton(groupBox);
        _asc->setObjectName(QString::fromUtf8("_asc"));
        _asc->setGeometry(QRect(10, 20, 82, 17));

        gridLayout->addWidget(groupBox, 2, 0, 1, 2);

        _dontFilterConf = new QCheckBox(FiltersDialog);
        _dontFilterConf->setObjectName(QString::fromUtf8("_dontFilterConf"));

        gridLayout->addWidget(_dontFilterConf, 3, 0, 1, 2);

        _ok = new QPushButton(FiltersDialog);
        _ok->setObjectName(QString::fromUtf8("_ok"));

        gridLayout->addWidget(_ok, 4, 0, 1, 1);

        _cancel = new QPushButton(FiltersDialog);
        _cancel->setObjectName(QString::fromUtf8("_cancel"));

        gridLayout->addWidget(_cancel, 4, 1, 1, 1);


        retranslateUi(FiltersDialog);

        QMetaObject::connectSlotsByName(FiltersDialog);
    } // setupUi

    void retranslateUi(QDialog *FiltersDialog)
    {
        FiltersDialog->setWindowTitle(QApplication::translate("FiltersDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FiltersDialog", "Wybierz czas i dat\304\231:", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("FiltersDialog", "Spos\303\263b filtrowania", 0, QApplication::UnicodeUTF8));
        _desc->setText(QApplication::translate("FiltersDialog", "Wcze\305\233niejsze", 0, QApplication::UnicodeUTF8));
        _asc->setText(QApplication::translate("FiltersDialog", "P\303\263\305\272niejsze", 0, QApplication::UnicodeUTF8));
        _dontFilterConf->setText(QApplication::translate("FiltersDialog", "Nie filtruj rekord\303\263w konfliktowych", 0, QApplication::UnicodeUTF8));
        _ok->setText(QApplication::translate("FiltersDialog", "Zastosuj", 0, QApplication::UnicodeUTF8));
        _cancel->setText(QApplication::translate("FiltersDialog", "Anuluj", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FiltersDialog: public Ui_FiltersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERSDIALOG_H
