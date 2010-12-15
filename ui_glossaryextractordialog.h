/********************************************************************************
** Form generated from reading UI file 'glossaryextractordialog.ui'
**
** Created: Wed Dec 15 10:25:29 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLOSSARYEXTRACTORDIALOG_H
#define UI_GLOSSARYEXTRACTORDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_GlossaryExtractorDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *_minWordCount;
    QLabel *label_2;
    QSpinBox *_maxWordCount;
    QLabel *label_3;
    QSpinBox *_minOccurence;
    QLabel *label_4;
    QSpinBox *_maxOccurence;
    QLabel *label_5;
    QLineEdit *_foundCount;
    QPushButton *_close;
    QPushButton *_find;
    QPushButton *_save;
    QLabel *label_6;

    void setupUi(QDialog *GlossaryExtractorDialog)
    {
        if (GlossaryExtractorDialog->objectName().isEmpty())
            GlossaryExtractorDialog->setObjectName(QString::fromUtf8("GlossaryExtractorDialog"));
        GlossaryExtractorDialog->resize(400, 300);
        gridLayout = new QGridLayout(GlossaryExtractorDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(GlossaryExtractorDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        _minWordCount = new QSpinBox(GlossaryExtractorDialog);
        _minWordCount->setObjectName(QString::fromUtf8("_minWordCount"));

        gridLayout->addWidget(_minWordCount, 0, 3, 1, 2);

        label_2 = new QLabel(GlossaryExtractorDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 3);

        _maxWordCount = new QSpinBox(GlossaryExtractorDialog);
        _maxWordCount->setObjectName(QString::fromUtf8("_maxWordCount"));

        gridLayout->addWidget(_maxWordCount, 1, 3, 1, 2);

        label_3 = new QLabel(GlossaryExtractorDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 3);

        _minOccurence = new QSpinBox(GlossaryExtractorDialog);
        _minOccurence->setObjectName(QString::fromUtf8("_minOccurence"));

        gridLayout->addWidget(_minOccurence, 2, 3, 1, 2);

        label_4 = new QLabel(GlossaryExtractorDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 4);

        _maxOccurence = new QSpinBox(GlossaryExtractorDialog);
        _maxOccurence->setObjectName(QString::fromUtf8("_maxOccurence"));

        gridLayout->addWidget(_maxOccurence, 3, 4, 1, 1);

        label_5 = new QLabel(GlossaryExtractorDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        _foundCount = new QLineEdit(GlossaryExtractorDialog);
        _foundCount->setObjectName(QString::fromUtf8("_foundCount"));

        gridLayout->addWidget(_foundCount, 4, 1, 1, 4);

        _close = new QPushButton(GlossaryExtractorDialog);
        _close->setObjectName(QString::fromUtf8("_close"));

        gridLayout->addWidget(_close, 5, 0, 1, 1);

        _find = new QPushButton(GlossaryExtractorDialog);
        _find->setObjectName(QString::fromUtf8("_find"));

        gridLayout->addWidget(_find, 5, 1, 1, 2);

        _save = new QPushButton(GlossaryExtractorDialog);
        _save->setObjectName(QString::fromUtf8("_save"));

        gridLayout->addWidget(_save, 5, 3, 1, 2);

        label_6 = new QLabel(GlossaryExtractorDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setMaximumSize(QSize(200, 25));

        gridLayout->addWidget(label_6, 6, 0, 1, 2);


        retranslateUi(GlossaryExtractorDialog);

        QMetaObject::connectSlotsByName(GlossaryExtractorDialog);
    } // setupUi

    void retranslateUi(QDialog *GlossaryExtractorDialog)
    {
        GlossaryExtractorDialog->setWindowTitle(QApplication::translate("GlossaryExtractorDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GlossaryExtractorDialog", "Minimalna liczba s\305\202\303\263w we frazie:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GlossaryExtractorDialog", "Maksymalna liczba s\305\202\303\263w we frazie:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GlossaryExtractorDialog", "Minimalna liczba powt\303\263rze\305\204 frazy:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("GlossaryExtractorDialog", "Maksymalna liczba powt\303\263rze\305\204 frazy:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("GlossaryExtractorDialog", "Znaleziono fraz:", 0, QApplication::UnicodeUTF8));
        _close->setText(QApplication::translate("GlossaryExtractorDialog", "Zako\305\204cz", 0, QApplication::UnicodeUTF8));
        _find->setText(QApplication::translate("GlossaryExtractorDialog", "Wyszukaj", 0, QApplication::UnicodeUTF8));
        _save->setText(QApplication::translate("GlossaryExtractorDialog", "Zapisz", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("GlossaryExtractorDialog", "Zero oznacza brak limitu.", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GlossaryExtractorDialog: public Ui_GlossaryExtractorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLOSSARYEXTRACTORDIALOG_H
