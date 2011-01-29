/********************************************************************************
** Form generated from reading UI file 'tmxwindow.ui'
**
** Created: Wed 12. Jan 07:17:20 2011
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TMXWINDOW_H
#define UI_TMXWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TMXWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QPlainTextEdit *_status;
    QLabel *label_2;
    QLineEdit *_dir;
    QPushButton *_chooseDir;
    QPushButton *_save;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TMXWindow)
    {
        if (TMXWindow->objectName().isEmpty())
            TMXWindow->setObjectName(QString::fromUtf8("TMXWindow"));
        TMXWindow->resize(403, 305);
        centralwidget = new QWidget(TMXWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        _status = new QPlainTextEdit(centralwidget);
        _status->setObjectName(QString::fromUtf8("_status"));
        _status->setReadOnly(true);

        gridLayout->addWidget(_status, 0, 1, 1, 2);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        _dir = new QLineEdit(centralwidget);
        _dir->setObjectName(QString::fromUtf8("_dir"));

        gridLayout->addWidget(_dir, 1, 2, 1, 2);

        _chooseDir = new QPushButton(centralwidget);
        _chooseDir->setObjectName(QString::fromUtf8("_chooseDir"));

        gridLayout->addWidget(_chooseDir, 2, 0, 1, 2);

        _save = new QPushButton(centralwidget);
        _save->setObjectName(QString::fromUtf8("_save"));

        gridLayout->addWidget(_save, 2, 3, 1, 1);

        TMXWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TMXWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 403, 21));
        TMXWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(TMXWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TMXWindow->setStatusBar(statusbar);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(_status);
        label_2->setBuddy(_dir);
#endif // QT_NO_SHORTCUT

        retranslateUi(TMXWindow);

        QMetaObject::connectSlotsByName(TMXWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TMXWindow)
    {
        TMXWindow->setWindowTitle(QApplication::translate("TMXWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TMXWindow", "Status:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TMXWindow", "Katalog do zapisu pami\304\231ci:", 0, QApplication::UnicodeUTF8));
        _chooseDir->setText(QApplication::translate("TMXWindow", "Wybierz katalog", 0, QApplication::UnicodeUTF8));
        _save->setText(QApplication::translate("TMXWindow", "Zapisz", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TMXWindow: public Ui_TMXWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TMXWINDOW_H
