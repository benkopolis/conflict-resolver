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
    ContentManagerWindow(const QStringList& files, ContentModel::ContentType type, QWidget *parent = 0);
    ~ContentManagerWindow();

    void setRH(int row, int height);

    ContentModel* content() { return _content; };

signals:

    void requestFiltration();
    void requestSaveDump(QString dumFile);

public slots:

    void onConflictCount(unsigned count);
    void onTotalRecords(unsigned count);
    void onCorrupted(unsigned count);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ContentManagerWindow *ui;
    ConflictResolverWindow* _crw;
    ContentModel* _content;

private slots:
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
