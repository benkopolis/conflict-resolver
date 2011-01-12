# -------------------------------------------------
# Project created by QtCreator 2010-04-15T20:56:14
# -------------------------------------------------
QT += gui
QT += testlib
QT += xml
QT += xmlpatterns
message($$QMAKESPEC)
QMAKESPEC = /usr/share/qt4/mkspecs/linux-g++
linux-g++:message(Linux)
unix:LIBS += -lqjson
win32:LIBS += -L./qjson/lib/ \
    -lqjson0
INCLUDEPATH += "./qjson/src"
TARGET = ConflictResolver
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    contentmanagerwindow.cpp \
    conflictresolverwindow.cpp \
    filesset.cpp \
    filessetdelegate.cpp \
    contentmodel.cpp \
    records/contentrecord.cpp \
    records/tmrecord.cpp \
    filtersdialog.cpp \
    fuzzystrings.cpp \
    editdialog.cpp \
    contentdelegate.cpp \
    inifile.cpp \
    tmheader.cpp \
    saver.cpp \
    tmsaver.cpp \
    glossaryextractordialog.cpp \
    fuzzyoptionsdialog.cpp \
    files/glossaryfile.cpp \
    files/tmfile.cpp \
    filemerger.cpp \
    conflictscontainer.cpp \
    records/conflictrecord.cpp \
    tests/filemergertests.cpp \
    tests/glossaryfiletests.cpp \
    files/tmxfile.cpp \
    records/tmxrecord.cpp \
    tests/tmfiletests.cpp \
    owngui/contentwidget.cpp \
    owngui/conflictswidget.cpp \
    commons/error.cpp \
    commons/errormanager.cpp \
    owngui/multiplecontentwidget.cpp \
    engine/fuzzyenginethread.cpp \
    engine/simplehandler.cpp \
    tmxwindow.cpp
HEADERS += mainwindow.h \
    contentmanagerwindow.h \
    conflictresolverwindow.h \
    filesset.h \
    filessetdelegate.h \
    contentmodel.h \
    records/contentrecord.h \
    records/tmrecord.h \
    filtersdialog.h \
    fuzzystrings.h \
    editdialog.h \
    contentdelegate.h \
    inifile.h \
    tmheader.h \
    saver.h \
    tmsaver.h \
    glossaryextractordialog.h \
    fuzzyoptionsdialog.h \
    files/glossaryfile.h \
    files/tmfile.h \
    filemerger.h \
    conflictscontainer.h \
    records/conflictrecord.h \
    tests/filemergertests.h \
    tests/glossaryfiletests.h \
    tests/Tests.h \
    files/tmxfile.h \
    records/tmxrecord.h \
    tests/tmfiletests.h \
    owngui/contentwidget.h \
    owngui/conflictswidget.h \
    commons/error.h \
    commons/errormanager.h \
    owngui/multiplecontentwidget.h \
    engine/fuzzyenginethread.h \
    engine/simplehandler.h \
    tmxwindow.h
FORMS += mainwindow.ui \
    contentmanagerwindow.ui \
    conflictresolverwindow.ui \
    filtersdialog.ui \
    editdialog.ui \
    glossaryextractordialog.ui \
    fuzzyoptionsdialog.ui \
    tmxwindow.ui
RESOURCES += dtds.qrc
