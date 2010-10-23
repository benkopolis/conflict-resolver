/********************************************************************************
** Form generated from reading UI file 'conflictresolverwindow.ui'
**
** Created: Sat 23. Oct 10:22:53 2010
**      by: Qt User Interface Compiler version 4.6.0
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
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
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
    QPushButton *prev;
    QPushButton *next;
    QListView *_conflictsList;
    QPushButton *removeDup;
    QPushButton *_putToDump;
    QPushButton *deleteAll;
    QPushButton *editRow;
    QPushButton *deleteRow;
    QPushButton *about;
    QPushButton *close;
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
        prev = new QPushButton(centralwidget);
        prev->setObjectName(QString::fromUtf8("prev"));

        gridLayout->addWidget(prev, 0, 0, 1, 1);

        next = new QPushButton(centralwidget);
        next->setObjectName(QString::fromUtf8("next"));

        gridLayout->addWidget(next, 0, 1, 1, 1);

        _conflictsList = new QListView(centralwidget);
        _conflictsList->setObjectName(QString::fromUtf8("_conflictsList"));
        _conflictsList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        _conflictsList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        _conflictsList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        _conflictsList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

        gridLayout->addWidget(_conflictsList, 1, 0, 5, 2);

        removeDup = new QPushButton(centralwidget);
        removeDup->setObjectName(QString::fromUtf8("removeDup"));

        gridLayout->addWidget(removeDup, 1, 2, 1, 1);

        _putToDump = new QPushButton(centralwidget);
        _putToDump->setObjectName(QString::fromUtf8("_putToDump"));

        gridLayout->addWidget(_putToDump, 2, 2, 1, 1);

        deleteAll = new QPushButton(centralwidget);
        deleteAll->setObjectName(QString::fromUtf8("deleteAll"));

        gridLayout->addWidget(deleteAll, 3, 2, 1, 1);

        editRow = new QPushButton(centralwidget);
        editRow->setObjectName(QString::fromUtf8("editRow"));

        gridLayout->addWidget(editRow, 4, 2, 1, 1);

        deleteRow = new QPushButton(centralwidget);
        deleteRow->setObjectName(QString::fromUtf8("deleteRow"));

        gridLayout->addWidget(deleteRow, 5, 2, 1, 1);

        about = new QPushButton(centralwidget);
        about->setObjectName(QString::fromUtf8("about"));

        gridLayout->addWidget(about, 6, 0, 1, 1);

        close = new QPushButton(centralwidget);
        close->setObjectName(QString::fromUtf8("close"));

        gridLayout->addWidget(close, 6, 1, 1, 1);

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
#ifndef QT_NO_TOOLTIP
        prev->setToolTip(QApplication::translate("ConflictResolverWindow", "Go to previous conflict.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        prev->setText(QApplication::translate("ConflictResolverWindow", "Poprzedni konflikt", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        next->setToolTip(QApplication::translate("ConflictResolverWindow", "Go to next conflict", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        next->setText(QApplication::translate("ConflictResolverWindow", "Nast\304\231pny konflikt", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        removeDup->setToolTip(QApplication::translate("ConflictResolverWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Usuwa identyczne (ze wzgl\304\231du na tre\305\233ci tekst\303\263w \305\272r\303\263d\305\202owych i docelowych) wiersze, pozostawiaj\304\205c jeden.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        removeDup->setText(QApplication::translate("ConflictResolverWindow", "Usu\305\204 identyczne", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        _putToDump->setToolTip(QApplication::translate("ConflictResolverWindow", "Powoduje przeniesienie wierszy do pliku \"na p\303\263\305\272niej\".", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        _putToDump->setText(QApplication::translate("ConflictResolverWindow", "Od\305\202\303\263\305\274 \"na p\303\263\305\272niej\"", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        deleteAll->setToolTip(QApplication::translate("ConflictResolverWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Usuwa wszystkie wy\305\233wietlanie wiersze.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        deleteAll->setText(QApplication::translate("ConflictResolverWindow", "Usu\305\204 wszystkie", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editRow->setToolTip(QApplication::translate("ConflictResolverWindow", "Pozwala edytowa\304\207 aktualnie zaznaczony wiersz.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editRow->setText(QApplication::translate("ConflictResolverWindow", "Edytuj wiersz", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        deleteRow->setToolTip(QApplication::translate("ConflictResolverWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Usuwa aktualnie zaznaczony wiersz.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        deleteRow->setText(QApplication::translate("ConflictResolverWindow", "Usu\305\204 wiersz", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        about->setToolTip(QApplication::translate("ConflictResolverWindow", "Few words about resolving conflicts.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        about->setText(QApplication::translate("ConflictResolverWindow", "Pomoc", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        close->setToolTip(QApplication::translate("ConflictResolverWindow", "Changes content of files previously choosen for analysis.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        close->setText(QApplication::translate("ConflictResolverWindow", "Zako\305\204cz", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("ConflictResolverWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConflictResolverWindow: public Ui_ConflictResolverWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFLICTRESOLVERWINDOW_H
