/********************************************************************************
** Form generated from reading UI file 'fuzzyoptionsdialog.ui'
**
** Created: Mon 15. Nov 23:22:45 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUZZYOPTIONSDIALOG_H
#define UI_FUZZYOPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_FuzzyOptionsDialog
{
public:
    QGridLayout *gridLayout;
    QCheckBox *_generate;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *_raport;
    QPushButton *_browse;
    QPushButton *_ok;
    QPushButton *_cancel;
    QSpinBox *_fuzzyValue;

    void setupUi(QDialog *FuzzyOptionsDialog)
    {
        if (FuzzyOptionsDialog->objectName().isEmpty())
            FuzzyOptionsDialog->setObjectName(QString::fromUtf8("FuzzyOptionsDialog"));
        FuzzyOptionsDialog->resize(400, 300);
        gridLayout = new QGridLayout(FuzzyOptionsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        _generate = new QCheckBox(FuzzyOptionsDialog);
        _generate->setObjectName(QString::fromUtf8("_generate"));
        _generate->setEnabled(false);

        gridLayout->addWidget(_generate, 0, 0, 1, 1);

        label = new QLabel(FuzzyOptionsDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_2 = new QLabel(FuzzyOptionsDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        _raport = new QLineEdit(FuzzyOptionsDialog);
        _raport->setObjectName(QString::fromUtf8("_raport"));

        gridLayout->addWidget(_raport, 2, 0, 1, 1);

        _browse = new QPushButton(FuzzyOptionsDialog);
        _browse->setObjectName(QString::fromUtf8("_browse"));

        gridLayout->addWidget(_browse, 2, 1, 1, 1);

        _ok = new QPushButton(FuzzyOptionsDialog);
        _ok->setObjectName(QString::fromUtf8("_ok"));

        gridLayout->addWidget(_ok, 4, 0, 1, 1);

        _cancel = new QPushButton(FuzzyOptionsDialog);
        _cancel->setObjectName(QString::fromUtf8("_cancel"));

        gridLayout->addWidget(_cancel, 4, 1, 1, 1);

        _fuzzyValue = new QSpinBox(FuzzyOptionsDialog);
        _fuzzyValue->setObjectName(QString::fromUtf8("_fuzzyValue"));
        _fuzzyValue->setMaximum(100);

        gridLayout->addWidget(_fuzzyValue, 3, 1, 1, 1);


        retranslateUi(FuzzyOptionsDialog);

        QMetaObject::connectSlotsByName(FuzzyOptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *FuzzyOptionsDialog)
    {
        FuzzyOptionsDialog->setWindowTitle(QApplication::translate("FuzzyOptionsDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        _generate->setText(QApplication::translate("FuzzyOptionsDialog", "Generuj raporty.", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FuzzyOptionsDialog", "Plik do zapisu raport\303\263w:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FuzzyOptionsDialog", "Warto\305\233\304\207 graniczna podobie\305\204stwa w %:", 0, QApplication::UnicodeUTF8));
        _browse->setText(QApplication::translate("FuzzyOptionsDialog", "Przegl\304\205daj...", 0, QApplication::UnicodeUTF8));
        _ok->setText(QApplication::translate("FuzzyOptionsDialog", "OK", 0, QApplication::UnicodeUTF8));
        _cancel->setText(QApplication::translate("FuzzyOptionsDialog", "Anuluj", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FuzzyOptionsDialog: public Ui_FuzzyOptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUZZYOPTIONSDIALOG_H
