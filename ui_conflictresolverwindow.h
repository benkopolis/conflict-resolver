/********************************************************************************
** Form generated from reading UI file 'conflictresolverwindow.ui'
**
** Created: Wed Dec 15 10:25:29 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFLICTRESOLVERWINDOW_H
#define UI_CONFLICTRESOLVERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConflictResolverWindow
{
public:
    QAction *actionNext;
    QAction *actionPrevious;
    QAction *actionZako_cz;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *ConflictResolverWindow)
    {
        if (ConflictResolverWindow->objectName().isEmpty())
            ConflictResolverWindow->setObjectName(QString::fromUtf8("ConflictResolverWindow"));
        ConflictResolverWindow->resize(553, 421);
        actionNext = new QAction(ConflictResolverWindow);
        actionNext->setObjectName(QString::fromUtf8("actionNext"));
        actionPrevious = new QAction(ConflictResolverWindow);
        actionPrevious->setObjectName(QString::fromUtf8("actionPrevious"));
        actionZako_cz = new QAction(ConflictResolverWindow);
        actionZako_cz->setObjectName(QString::fromUtf8("actionZako_cz"));
        centralwidget = new QWidget(ConflictResolverWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ConflictResolverWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ConflictResolverWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 553, 21));
        ConflictResolverWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ConflictResolverWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ConflictResolverWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(ConflictResolverWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        ConflictResolverWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionPrevious);
        toolBar->addAction(actionNext);
        toolBar->addAction(actionZako_cz);

        retranslateUi(ConflictResolverWindow);

        QMetaObject::connectSlotsByName(ConflictResolverWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ConflictResolverWindow)
    {
        ConflictResolverWindow->setWindowTitle(QApplication::translate("ConflictResolverWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionNext->setText(QApplication::translate("ConflictResolverWindow", "Nast\304\231pny", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNext->setToolTip(QApplication::translate("ConflictResolverWindow", "Przejd\305\272 do nast\304\231pnego", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNext->setShortcut(QApplication::translate("ConflictResolverWindow", "Ctrl+Right", 0, QApplication::UnicodeUTF8));
        actionPrevious->setText(QApplication::translate("ConflictResolverWindow", "Poprzedni", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPrevious->setToolTip(QApplication::translate("ConflictResolverWindow", "Przejd\305\272 do poprzedniego", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPrevious->setShortcut(QApplication::translate("ConflictResolverWindow", "Ctrl+Left", 0, QApplication::UnicodeUTF8));
        actionZako_cz->setText(QApplication::translate("ConflictResolverWindow", "Zako\305\204cz", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionZako_cz->setToolTip(QApplication::translate("ConflictResolverWindow", "Zapisz zmiany i zamknij to okno", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionZako_cz->setShortcut(QApplication::translate("ConflictResolverWindow", "Shift+Return", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("ConflictResolverWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConflictResolverWindow: public Ui_ConflictResolverWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFLICTRESOLVERWINDOW_H
