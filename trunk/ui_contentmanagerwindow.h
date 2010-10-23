/********************************************************************************
** Form generated from reading UI file 'contentmanagerwindow.ui'
**
** Created: Sat 23. Oct 10:22:53 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTENTMANAGERWINDOW_H
#define UI_CONTENTMANAGERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ContentManagerWindow
{
public:
    QAction *actionUsu_wiersz;
    QAction *actionEdit_row;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *_conflictsCount;
    QPushButton *_find;
    QLabel *label_2;
    QLineEdit *_fuzzyConflictsCount;
    QPushButton *_options;
    QLabel *label_3;
    QLineEdit *_dumpFile;
    QPushButton *_browse;
    QPushButton *_saveDump;
    QLabel *label_5;
    QLineEdit *_totalCount;
    QPushButton *_filterContent;
    QPushButton *_saveContent;
    QPushButton *_resolveConflicts;
    QPushButton *_confront;
    QCheckBox *_autoSeachOnFiltered;
    QLabel *label_4;
    QLineEdit *_corrupted;
    QPushButton *_saveReversed;
    QPushButton *_saveGloss;
    QLabel *label_6;
    QLineEdit *_antiDict;
    QPushButton *_chooseAntiDict;
    QPushButton *_checkDict;
    QCheckBox *_cSource;
    QCheckBox *_cTarget;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *ContentManagerWindow)
    {
        if (ContentManagerWindow->objectName().isEmpty())
            ContentManagerWindow->setObjectName(QString::fromUtf8("ContentManagerWindow"));
        ContentManagerWindow->resize(624, 394);
        actionUsu_wiersz = new QAction(ContentManagerWindow);
        actionUsu_wiersz->setObjectName(QString::fromUtf8("actionUsu_wiersz"));
        actionEdit_row = new QAction(ContentManagerWindow);
        actionEdit_row->setObjectName(QString::fromUtf8("actionEdit_row"));
        centralwidget = new QWidget(ContentManagerWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        _conflictsCount = new QLineEdit(centralwidget);
        _conflictsCount->setObjectName(QString::fromUtf8("_conflictsCount"));
        _conflictsCount->setReadOnly(true);

        gridLayout->addWidget(_conflictsCount, 0, 1, 1, 2);

        _find = new QPushButton(centralwidget);
        _find->setObjectName(QString::fromUtf8("_find"));

        gridLayout->addWidget(_find, 0, 3, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        _fuzzyConflictsCount = new QLineEdit(centralwidget);
        _fuzzyConflictsCount->setObjectName(QString::fromUtf8("_fuzzyConflictsCount"));
        _fuzzyConflictsCount->setReadOnly(true);

        gridLayout->addWidget(_fuzzyConflictsCount, 1, 2, 1, 1);

        _options = new QPushButton(centralwidget);
        _options->setObjectName(QString::fromUtf8("_options"));

        gridLayout->addWidget(_options, 1, 3, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        _dumpFile = new QLineEdit(centralwidget);
        _dumpFile->setObjectName(QString::fromUtf8("_dumpFile"));

        gridLayout->addWidget(_dumpFile, 2, 1, 1, 2);

        _browse = new QPushButton(centralwidget);
        _browse->setObjectName(QString::fromUtf8("_browse"));

        gridLayout->addWidget(_browse, 2, 3, 1, 1);

        _saveDump = new QPushButton(centralwidget);
        _saveDump->setObjectName(QString::fromUtf8("_saveDump"));

        gridLayout->addWidget(_saveDump, 2, 4, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        _totalCount = new QLineEdit(centralwidget);
        _totalCount->setObjectName(QString::fromUtf8("_totalCount"));
        _totalCount->setReadOnly(true);

        gridLayout->addWidget(_totalCount, 3, 1, 1, 2);

        _filterContent = new QPushButton(centralwidget);
        _filterContent->setObjectName(QString::fromUtf8("_filterContent"));

        gridLayout->addWidget(_filterContent, 7, 0, 1, 1);

        _saveContent = new QPushButton(centralwidget);
        _saveContent->setObjectName(QString::fromUtf8("_saveContent"));

        gridLayout->addWidget(_saveContent, 7, 1, 1, 2);

        _resolveConflicts = new QPushButton(centralwidget);
        _resolveConflicts->setObjectName(QString::fromUtf8("_resolveConflicts"));

        gridLayout->addWidget(_resolveConflicts, 7, 3, 1, 1);

        _confront = new QPushButton(centralwidget);
        _confront->setObjectName(QString::fromUtf8("_confront"));

        gridLayout->addWidget(_confront, 7, 4, 1, 1);

        _autoSeachOnFiltered = new QCheckBox(centralwidget);
        _autoSeachOnFiltered->setObjectName(QString::fromUtf8("_autoSeachOnFiltered"));

        gridLayout->addWidget(_autoSeachOnFiltered, 8, 0, 1, 4);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        _corrupted = new QLineEdit(centralwidget);
        _corrupted->setObjectName(QString::fromUtf8("_corrupted"));
        _corrupted->setReadOnly(true);

        gridLayout->addWidget(_corrupted, 4, 1, 1, 1);

        _saveReversed = new QPushButton(centralwidget);
        _saveReversed->setObjectName(QString::fromUtf8("_saveReversed"));

        gridLayout->addWidget(_saveReversed, 3, 3, 1, 2);

        _saveGloss = new QPushButton(centralwidget);
        _saveGloss->setObjectName(QString::fromUtf8("_saveGloss"));

        gridLayout->addWidget(_saveGloss, 4, 3, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        _antiDict = new QLineEdit(centralwidget);
        _antiDict->setObjectName(QString::fromUtf8("_antiDict"));

        gridLayout->addWidget(_antiDict, 5, 1, 1, 2);

        _chooseAntiDict = new QPushButton(centralwidget);
        _chooseAntiDict->setObjectName(QString::fromUtf8("_chooseAntiDict"));

        gridLayout->addWidget(_chooseAntiDict, 5, 3, 1, 1);

        _checkDict = new QPushButton(centralwidget);
        _checkDict->setObjectName(QString::fromUtf8("_checkDict"));

        gridLayout->addWidget(_checkDict, 5, 4, 1, 1);

        _cSource = new QCheckBox(centralwidget);
        _cSource->setObjectName(QString::fromUtf8("_cSource"));
        _cSource->setChecked(true);

        gridLayout->addWidget(_cSource, 6, 0, 1, 1);

        _cTarget = new QCheckBox(centralwidget);
        _cTarget->setObjectName(QString::fromUtf8("_cTarget"));

        gridLayout->addWidget(_cTarget, 6, 3, 1, 1);

        ContentManagerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ContentManagerWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 624, 25));
        ContentManagerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ContentManagerWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ContentManagerWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(ContentManagerWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        ContentManagerWindow->addToolBar(Qt::TopToolBarArea, toolBar);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(_conflictsCount);
        label_2->setBuddy(_fuzzyConflictsCount);
        label_3->setBuddy(_dumpFile);
        label_5->setBuddy(_totalCount);
        label_4->setBuddy(_corrupted);
#endif // QT_NO_SHORTCUT

        retranslateUi(ContentManagerWindow);

        QMetaObject::connectSlotsByName(ContentManagerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ContentManagerWindow)
    {
        ContentManagerWindow->setWindowTitle(QApplication::translate("ContentManagerWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionUsu_wiersz->setText(QApplication::translate("ContentManagerWindow", "Usu\305\204 wiersz", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionUsu_wiersz->setToolTip(QApplication::translate("ContentManagerWindow", "Delete selected row.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionUsu_wiersz->setShortcut(QApplication::translate("ContentManagerWindow", "Del", 0, QApplication::UnicodeUTF8));
        actionEdit_row->setText(QApplication::translate("ContentManagerWindow", "Edytuj wiersz", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionEdit_row->setToolTip(QApplication::translate("ContentManagerWindow", "Edit selected row.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionEdit_row->setShortcut(QApplication::translate("ContentManagerWindow", "Return", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ContentManagerWindow", "Znaleziono konflikt\303\263w:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        _conflictsCount->setToolTip(QApplication::translate("ContentManagerWindow", "Ilo\305\233\304\207 znalezionych konflikt\303\263w.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        _find->setToolTip(QApplication::translate("ContentManagerWindow", "Ponownie przeszukuje wybrane wcze\305\233nie pliki pod k\304\205tem konflitk\303\263w mi\304\231dzy wpisami.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        _find->setText(QApplication::translate("ContentManagerWindow", "Szukaj ponownie", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ContentManagerWindow", "Znaleziono rozmytych konflikt\303\263w:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        _fuzzyConflictsCount->setToolTip(QApplication::translate("ContentManagerWindow", "Ilo\305\233\304\207 znalezionych rozmytych konflikt\303\263w.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        _options->setToolTip(QApplication::translate("ContentManagerWindow", "Pozwala ustawi\304\207 opcje wyszukiwania konflikt\303\263w oraz konflikt\303\263w rozmytych [w trkacie tworzenia].", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        _options->setText(QApplication::translate("ContentManagerWindow", "Opcje ...", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ContentManagerWindow", "Plik \"na p\303\263\305\272niej\":", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        _dumpFile->setToolTip(QApplication::translate("ContentManagerWindow", "Pozwala wybra\304\207 plik, kt\303\263ry b\304\231dzie pe\305\202ni\305\202 funkcj\304\231 sk\305\202adowiska rekord\303\263w, co do kt\303\263rych jako\305\233ci nie jestesmy pewni.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        _browse->setToolTip(QApplication::translate("ContentManagerWindow", "Pozwala wybra\304\207 plik, kt\303\263ry b\304\231dzie pe\305\202ni\305\202 funkcj\304\231 sk\305\202adowiska rekord\303\263w, co do kt\303\263rych jako\305\233ci nie jestesmy pewni.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        _browse->setText(QApplication::translate("ContentManagerWindow", "Przegl\304\205daj ...", 0, QApplication::UnicodeUTF8));
        _saveDump->setText(QApplication::translate("ContentManagerWindow", "Zapisz", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ContentManagerWindow", "Rekordy bezkonfliktowe:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        _filterContent->setToolTip(QApplication::translate("ContentManagerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Wybierz spos\303\263b filtrowania zawarto\305\233ci</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        _filterContent->setText(QApplication::translate("ContentManagerWindow", "Filtruj zawarto\305\233\304\207 ...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        _saveContent->setToolTip(QApplication::translate("ContentManagerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Zapisz zawarto\305\233\304\207 jako nowy plik, lub doklej do istniej\304\205cego.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        _saveContent->setText(QApplication::translate("ContentManagerWindow", "Zapisz zawarto\305\233\304\207 jako ...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        _resolveConflicts->setToolTip(QApplication::translate("ContentManagerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Otw\303\263rz okno rozwi\304\205zywania konflikt\303\263w</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        _resolveConflicts->setText(QApplication::translate("ContentManagerWindow", "Rozwi\304\205\305\274 konflikty ...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        _confront->setToolTip(QApplication::translate("ContentManagerWindow", "Otwiera dodatkowy plik, kt\303\263rego zawarto\305\233\304\207 jest przegl\304\205dana z ju\305\274 otawrt\304\205 zawarto\305\233ci\304\205, wyszukiwana s\304\205 konflikty wed\305\202ug wybranych opcji,\n"
"a nast\304\231pnie mo\305\274na zapisa\304\207 wyniki pracy do tego dodatkowego pliku.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        _confront->setText(QApplication::translate("ContentManagerWindow", "Konfrontuj ...", 0, QApplication::UnicodeUTF8));
        _autoSeachOnFiltered->setText(QApplication::translate("ContentManagerWindow", "Po odfiltrowaniu automatycznie wyszukaj konflikty od nowa.", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ContentManagerWindow", "Uszkodzone rekordy:", 0, QApplication::UnicodeUTF8));
        _saveReversed->setText(QApplication::translate("ContentManagerWindow", "Zapisz odwr\303\263con\304\205 baz\304\231", 0, QApplication::UnicodeUTF8));
        _saveGloss->setText(QApplication::translate("ContentManagerWindow", "Zapisz glosariusz ...", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ContentManagerWindow", "Antys\305\202ownik:", 0, QApplication::UnicodeUTF8));
        _chooseAntiDict->setText(QApplication::translate("ContentManagerWindow", "Wybierz ...", 0, QApplication::UnicodeUTF8));
        _checkDict->setText(QApplication::translate("ContentManagerWindow", "Sprawd\305\272", 0, QApplication::UnicodeUTF8));
        _cSource->setText(QApplication::translate("ContentManagerWindow", "Sprawdzaj \305\272r\303\263d\305\202owe", 0, QApplication::UnicodeUTF8));
        _cTarget->setText(QApplication::translate("ContentManagerWindow", "Sprawdzaj docelowe", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("ContentManagerWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ContentManagerWindow: public Ui_ContentManagerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTENTMANAGERWINDOW_H
