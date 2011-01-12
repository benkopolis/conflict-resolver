/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed 12. Jan 07:17:19 2011
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionWczytaj_konfiguracj;
    QAction *actionZapisz_konfiguracj;
    QAction *actionOpenFile;
    QAction *actionAnalizuj_plik;
    QAction *actionCloseFile;
    QAction *actionWyj_cie_z_programu;
    QAction *actionStart;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QListView *_files;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QRadioButton *_tm;
    QRadioButton *_tmx;
    QRadioButton *_gloss;
    QPushButton *_openFile;
    QPushButton *startAnalyseing;
    QPushButton *_closeFile;
    QCheckBox *_fuzzySearch;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(575, 366);
        actionWczytaj_konfiguracj = new QAction(MainWindow);
        actionWczytaj_konfiguracj->setObjectName(QString::fromUtf8("actionWczytaj_konfiguracj"));
        actionZapisz_konfiguracj = new QAction(MainWindow);
        actionZapisz_konfiguracj->setObjectName(QString::fromUtf8("actionZapisz_konfiguracj"));
        actionOpenFile = new QAction(MainWindow);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        actionAnalizuj_plik = new QAction(MainWindow);
        actionAnalizuj_plik->setObjectName(QString::fromUtf8("actionAnalizuj_plik"));
        actionCloseFile = new QAction(MainWindow);
        actionCloseFile->setObjectName(QString::fromUtf8("actionCloseFile"));
        actionWyj_cie_z_programu = new QAction(MainWindow);
        actionWyj_cie_z_programu->setObjectName(QString::fromUtf8("actionWyj_cie_z_programu"));
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        _files = new QListView(centralWidget);
        _files->setObjectName(QString::fromUtf8("_files"));
        _files->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        _files->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        _files->setTabKeyNavigation(true);
        _files->setAlternatingRowColors(false);
        _files->setSelectionMode(QAbstractItemView::NoSelection);
        _files->setSelectionBehavior(QAbstractItemView::SelectItems);
        _files->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        _files->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        _files->setSelectionRectVisible(false);

        gridLayout->addWidget(_files, 1, 0, 2, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(100, 80));
        formLayout = new QFormLayout(groupBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        _tm = new QRadioButton(groupBox);
        _tm->setObjectName(QString::fromUtf8("_tm"));

        formLayout->setWidget(0, QFormLayout::LabelRole, _tm);

        _tmx = new QRadioButton(groupBox);
        _tmx->setObjectName(QString::fromUtf8("_tmx"));

        formLayout->setWidget(1, QFormLayout::LabelRole, _tmx);

        _gloss = new QRadioButton(groupBox);
        _gloss->setObjectName(QString::fromUtf8("_gloss"));

        formLayout->setWidget(2, QFormLayout::LabelRole, _gloss);


        gridLayout_2->addWidget(groupBox, 0, 0, 2, 1);

        _openFile = new QPushButton(centralWidget);
        _openFile->setObjectName(QString::fromUtf8("_openFile"));

        gridLayout_2->addWidget(_openFile, 0, 1, 1, 1);

        startAnalyseing = new QPushButton(centralWidget);
        startAnalyseing->setObjectName(QString::fromUtf8("startAnalyseing"));

        gridLayout_2->addWidget(startAnalyseing, 0, 2, 1, 1);

        _closeFile = new QPushButton(centralWidget);
        _closeFile->setObjectName(QString::fromUtf8("_closeFile"));

        gridLayout_2->addWidget(_closeFile, 1, 1, 1, 1);

        _fuzzySearch = new QCheckBox(centralWidget);
        _fuzzySearch->setObjectName(QString::fromUtf8("_fuzzySearch"));

        gridLayout_2->addWidget(_fuzzySearch, 1, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 575, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionWczytaj_konfiguracj);
        menuFile->addAction(actionZapisz_konfiguracj);
        menuFile->addAction(actionOpenFile);
        menuFile->addAction(actionCloseFile);
        menuFile->addAction(actionWyj_cie_z_programu);
        mainToolBar->addAction(actionOpenFile);
        mainToolBar->addAction(actionCloseFile);
        mainToolBar->addAction(actionStart);

        retranslateUi(MainWindow);
        QObject::connect(actionOpenFile, SIGNAL(triggered()), _openFile, SLOT(click()));
        QObject::connect(actionCloseFile, SIGNAL(triggered()), _closeFile, SLOT(click()));
        QObject::connect(actionStart, SIGNAL(triggered()), startAnalyseing, SLOT(click()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionWczytaj_konfiguracj->setText(QApplication::translate("MainWindow", "Wczytaj konfiguracj\304\231", 0, QApplication::UnicodeUTF8));
        actionWczytaj_konfiguracj->setShortcut(QApplication::translate("MainWindow", "Ctrl+L", 0, QApplication::UnicodeUTF8));
        actionZapisz_konfiguracj->setText(QApplication::translate("MainWindow", "Zapisz konfiguracj\304\231", 0, QApplication::UnicodeUTF8));
        actionZapisz_konfiguracj->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionOpenFile->setText(QApplication::translate("MainWindow", "Otw\303\263rz plik", 0, QApplication::UnicodeUTF8));
        actionOpenFile->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionAnalizuj_plik->setText(QApplication::translate("MainWindow", "Analizuj plik", 0, QApplication::UnicodeUTF8));
        actionAnalizuj_plik->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+A", 0, QApplication::UnicodeUTF8));
        actionCloseFile->setText(QApplication::translate("MainWindow", "Zamknij plik", 0, QApplication::UnicodeUTF8));
        actionCloseFile->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", 0, QApplication::UnicodeUTF8));
        actionWyj_cie_z_programu->setText(QApplication::translate("MainWindow", "Wyj\305\233cie z programu", 0, QApplication::UnicodeUTF8));
        actionWyj_cie_z_programu->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionStart->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        actionStart->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Otwarte pliki:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        _files->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Lista otwartych plik\303\263w. Dwuklik na pliku spowoduje jego przeniesienie z tej listy na list\304\231 plik\303\263w wybranych do analizy.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("MainWindow", "Typy plik\303\263w", 0, QApplication::UnicodeUTF8));
        _tm->setText(QApplication::translate("MainWindow", "TM", 0, QApplication::UnicodeUTF8));
        _tmx->setText(QApplication::translate("MainWindow", "TMX", 0, QApplication::UnicodeUTF8));
        _gloss->setText(QApplication::translate("MainWindow", "Glossary", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        _openFile->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Otw\303\263rz kolejny plik, lub kilka plik\303\263w.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        _openFile->setText(QApplication::translate("MainWindow", "Otw\303\263rz plik (pliki)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        startAnalyseing->setToolTip(QApplication::translate("MainWindow", "Otwiera okno analizy, dla plik\303\263w znajduj\304\205cych si\304\231 na li\305\233cie powy\305\274ej.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        startAnalyseing->setText(QApplication::translate("MainWindow", "Rozpocznij analiz\304\231", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        _closeFile->setToolTip(QApplication::translate("MainWindow", "Zamknij wybrany plik.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        _closeFile->setText(QApplication::translate("MainWindow", "Zamknij zaznaczony plik", 0, QApplication::UnicodeUTF8));
        _fuzzySearch->setText(QApplication::translate("MainWindow", "Sprawdzaj rozmyte konflitkty", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
