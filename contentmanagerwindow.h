#ifndef CONTENTMANAGERWINDOW_H
#define CONTENTMANAGERWINDOW_H

#include <QMainWindow>
#include "conflictresolverwindow.h"
#include "contentmodel.h"

namespace Ui {
    class ContentManagerWindow;
}

class ContentManagerWindow : public QMainWindow {
    Q_OBJECT
public:

    ContentManagerWindow(QWidget *parent = 0);
    ContentManagerWindow(bool fuzzySerach, const QStringList& files, ContentModel::ContentType type, QWidget *parent = 0);
    ~ContentManagerWindow();

    void setRH(int row, int height);

    ContentModel* content() { return _content; };

signals:

    void requestFiltration();
    void requestSaveDump(QString dumFile);

public slots:

    void onConflictCount(unsigned count, unsigned dup);
    void onTotalRecords(unsigned count);
    void onCorrupted(unsigned count);
    void onFuzzyCount(unsigned count);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ContentManagerWindow *ui;
    ConflictResolverWindow* _crw;
    ContentModel* _content;
    unsigned _conflicts;
    unsigned _fuzzy;

private slots:
    void on__options_clicked();
    void on__find_clicked();
    void on__checkDict_clicked();
    void on__chooseAntiDict_clicked();
    void on__saveGloss_clicked();
    void on__saveReversed_clicked();
    void on__confront_clicked();
    void on__saveDump_clicked();
    void on__browse_clicked();
    void on__saveContent_clicked();
    void on__filterContent_clicked();
    void on__resolveConflicts_clicked();
};

#endif // CONTENTMANAGERWINDOW_H
